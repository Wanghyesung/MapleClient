#include "WEventManager.h"
#include "WSceneManger.h"
#include "WTransform.h"
#include "..\Engine\WPlayerAttackObject.h"
#include "..\Engine\WMonsterAttackObject.h"
#include "..\Engine\WPlayer.h"
#include "WGameObject.h"
#include "WLayer.h"
#include "WGameObjectManager.h"
#include "..\Engine_Source\WAnimator.h"
#include "..\Engine_Source\WTransform.h"
#include "..\Engine\WObjectPoolManager.h"
namespace W
{
	std::function<void(DWORD_PTR, DWORD_PTR, LONG_PTR)> EventManager::m_arrFunction[(UINT)EVENT_TYPE::END] = {};
	std::vector<tEvent> EventManager::m_vecEvent[2] = {};
	atomic<int> EventManager::m_iActiveIdx = 1;
	
	RWLock EventManager::m_lock = {};
	

	UINT EventManager::m_iNextScene = 0;
#define ObjectPoolPosition 2000.f

	void EventManager::Update()
	{
		//더블버퍼링
		{
			WLock lock_guard(m_lock);
			m_iActiveIdx = 1 - m_iActiveIdx;
		}

		std::vector<tEvent>& vecActiveEvent = m_vecEvent[m_iActiveIdx];
		for (int i = 0; i < vecActiveEvent.size(); ++i)
		{
			excute(vecActiveEvent[i]);
		}

		vecActiveEvent.clear();
	}

	
	void EventManager::Initialize()
	{		
	
		m_arrFunction[(UINT)EVENT_TYPE::UPDATE_STATE] = update_state;
	
		m_arrFunction[(UINT)EVENT_TYPE::UPDATE_TRANSFORM] = update_trasnform;
		m_arrFunction[(UINT)EVENT_TYPE::CREATE_PLAYER] = add_player;
		m_arrFunction[(UINT)EVENT_TYPE::CREATE_OTHER_PLAYER] = add_other_player;
		m_arrFunction[(UINT)EVENT_TYPE::DELETE_PLAYER] = delete_player;
		
		m_arrFunction[(UINT)EVENT_TYPE::CREATE_OBJECT] = create_object;
		m_arrFunction[(UINT)EVENT_TYPE::DELET_OBJECT] = delete_object;
		m_arrFunction[(UINT)EVENT_TYPE::CREATE_OBJECT_ID] = create_object_id;
		m_arrFunction[(UINT)EVENT_TYPE::DELET_OBJECT_ID] = delete_object_id;
		m_arrFunction[(UINT)EVENT_TYPE::SCENE_CHANGE] = change_scene;
		
	}

	void EventManager::AddEvent(const tEvent& _tEve)
	{
		WLock lock_guard(m_lock);
		
		m_vecEvent[1 - m_iActiveIdx].push_back(_tEve);
	}
	
	void EventManager::excute(const tEvent& _tEve)
	{
		m_arrFunction[(UINT)_tEve.eEventType](_tEve.lParm, _tEve.wParm, _tEve.accParm);
	}
	void EventManager::DeleteObject(GameObject* _pObj, Scene* _pScene)
	{
		tEvent eve = {};
		eve.lParm = (DWORD_PTR)_pObj;
		eve.wParm = (DWORD_PTR)_pScene;

		eve.eEventType = EVENT_TYPE::DELET_OBJECT;
		AddEvent(eve);
	}

	void EventManager::DeleteObjectID(UINT _ID, eLayerType _eType, UINT _iSceneID)
	{
		tEvent eve = {};
		eve.lParm = (DWORD_PTR)_ID;
		eve.wParm = (DWORD_PTR)_eType;
		eve.accParm = (LONG_PTR)_iSceneID;

		eve.eEventType = EVENT_TYPE::DELET_OBJECT_ID;
		AddEvent(eve);
	}


	void EventManager::ChangeScene(const std::wstring& _strNextScene)
	{
		tEvent eve = {};
		eve.eEventType = EVENT_TYPE::SCENE_CHANGE;
		eve.lParm = (DWORD_PTR)PLAYER_ID;

		Scene* pScene = SceneManger::FindScene(_strNextScene);
		if (pScene)
			m_iNextScene = pScene->GetSceneID();

		AddEvent(eve);
	}
	void EventManager::AddPlayer(UINT _iPlayerID, vector<UINT> _vecPlayerID)
	{
		tEvent eve = {};
		eve.eEventType = EVENT_TYPE::CREATE_PLAYER;
		eve.lParm = (DWORD_PTR)_iPlayerID;
		AddEvent(eve);

		for (int i = 0; i < _vecPlayerID.size(); ++i)
			AddOtherPlayer(_vecPlayerID[i]);
	}
	void EventManager::AddOtherPlayer(UINT _iPlayerID)
	{
		tEvent eve = {};
		eve.eEventType = EVENT_TYPE::CREATE_OTHER_PLAYER;

		eve.lParm = (DWORD_PTR)_iPlayerID;
	
		AddEvent(eve);
	}

	void EventManager::UpdateTransform(UINT _ID, eLayerType _eType, const tTransformInfo& _tTransformInfo)
	{
		tEvent eve = {};
		eve.eEventType = EVENT_TYPE::UPDATE_TRANSFORM;

		eve.lParm = (DWORD_PTR)_ID;
		eve.wParm = (DWORD_PTR)_eType;
		eve.accParm = (DWORD_PTR)new tTransformInfo(_tTransformInfo);

		AddEvent(eve);
	}

	void EventManager::UpdateState(UINT _iLayerID, int _iState, const wstring& _strState)
	{
		tEvent eve = {};
		eve.eEventType = EVENT_TYPE::UPDATE_STATE;

		eve.lParm = (DWORD_PTR)_iLayerID;
		eve.wParm = (DWORD_PTR)_iState;
		eve.accParm = (DWORD_PTR)new wstring(_strState);

		AddEvent(eve);
	}


	void EventManager::create_object(DWORD_PTR _lParm, DWORD_PTR _wParm, LONG_PTR _accParm)
	{
		GameObject* pObj = (GameObject*)_lParm;
		eLayerType eLyaer = (eLayerType)_wParm;
		
		SceneManger::AddGameObject(eLyaer, pObj);

		pObj->Initialize();
	}

	void EventManager::delete_object(DWORD_PTR _lParm, DWORD_PTR _wParm, LONG_PTR _accParm)
	{
		GameObject* pObj = (GameObject*)_lParm;
		Scene* pScene = (Scene*)_wParm;

		pScene->EraseObject(pObj->GetLayerType(), pObj);

		if (pObj->IsPoolObject())
			W::ObjectPoolManager::AddObjectPool(pObj->GetName(), pObj);
		else
			delete pObj;
	}

	void EventManager::create_object_id(DWORD_PTR _lParm, DWORD_PTR _wParm, LONG_PTR _accParm)
	{
		UINT iSceneLayerCreateIdId = (UINT)_lParm;
		const tTransformInfo& tTrInfo = *reinterpret_cast<tTransformInfo*>(_wParm);
		const wstring& strObjectName = *reinterpret_cast<wstring*>(_accParm);

		UCHAR cSceneID = (iSceneLayerCreateIdId >> 24) & 0xFF;
		if (cSceneID == SceneManger::GetActiveScene()->GetSceneID())
		{
			UCHAR cLayer = (iSceneLayerCreateIdId >> 16) & 0xFF;
			UCHAR cCreateid = (iSceneLayerCreateIdId >> 8) & 0xFF;
			UCHAR CID = iSceneLayerCreateIdId & 0xFF;

			GameObject* pObj = nullptr;
			if (strObjectName.empty())
				pObj = GameObjectManager::GetMonsterOfID(cCreateid);
			else
				pObj = ObjectPoolManager::PopObject(strObjectName);


			pObj->GetComponent<Transform>()->SetDirectPosition(tTrInfo.vPosition);
			pObj->GetComponent<Transform>()->SetDirectRotation(tTrInfo.vRotation);

			eLayerType eLayerType = (W::eLayerType)cLayer;
			pObj->SetObjectID(CID);
			SceneManger::AddGameObject(eLayerType, pObj);

			pObj->Initialize();
		}
		delete &tTrInfo;
		delete &strObjectName;
	}

	void EventManager::delete_object_id(DWORD_PTR _lParm, DWORD_PTR _wParm, LONG_PTR _accParm)
	{
		UINT ID = (UINT)_lParm;
		eLayerType eLayer = (eLayerType)_wParm;
		UINT iSceneID = (UINT)_accParm;

		Scene* pScene = SceneManger::FindScene(iSceneID);
		if (pScene == nullptr)
			assert(nullptr);

		GameObject* pObj = SceneManger::FindObject(pScene, ID, eLayer);
		if (!pObj)
			return;

		pScene->EraseObject(eLayer, pObj);

		if (pObj->IsPoolObject())
			ObjectPoolManager::AddObjectPool(pObj->GetName(), pObj);
		else
			delete pObj;
	}

	void EventManager::change_scene(DWORD_PTR _lParm, DWORD_PTR _wParm, LONG_PTR _accParm)
	{	
		UINT iPlayerID = (UINT)_lParm;

		Protocol::C_MAP_LOADING pkt;
		pkt.set_player_id(iPlayerID);
		shared_ptr<SendBuffer> pBuffer = ServerPacketHandler::MakeSendBuffer(pkt);
		GClientService->GetClientSession()->Send(pBuffer);

		SceneManger::LoadScene(m_iNextScene);
	}

	void EventManager::add_player(DWORD_PTR _lParm, DWORD_PTR _wParm, LONG_PTR _accParm)
	{
		UINT iPlayerID = (UINT)_lParm;

		Player* pPlayer = new Player();
		pPlayer->SetName(L"Player");
		pPlayer->m_iPlayerID = iPlayerID;
		pPlayer->SetObjectID(iPlayerID);
		pPlayer->Initialize();
		pPlayer->SetTargetPlayer();

		SceneManger::AddGameObject(eLayerType::Player, pPlayer);
	}

	void EventManager::add_other_player(DWORD_PTR _lParm, DWORD_PTR _wParm, LONG_PTR _accParm)
	{
		UINT iPlayerID = (UINT)_lParm;
		UINT iObjectID = (UINT)_wParm;

		Player* pPlayer = new Player();
		pPlayer->SetName(L"Other_Player");
		pPlayer->m_iPlayerID = iPlayerID;
		pPlayer->SetObjectID(iObjectID);
		pPlayer->Initialize();

		SceneManger::AddGameObject(eLayerType::Player, pPlayer);
	}

	void EventManager::delete_player(DWORD_PTR _lParm, DWORD_PTR _wParm, LONG_PTR _accParm)
	{

	}

	void EventManager::delete_otehr_player(DWORD_PTR _lParm, DWORD_PTR _wParm, LONG_PTR _accParm)
	{

	}

	void EventManager::update_state(DWORD_PTR _lParm, DWORD_PTR _wParm, LONG_PTR _accParm)
	{
		UINT iLayerID = (UINT)_lParm;
		int iState = (int)_wParm;
		//static_cast는 컴파일러가 타입 간 변환 규칙이 안전하다고 판단할 때만 허용
		//reinterpret_cast는 포인터끼리 강제 변환
		wstring* pStrAnimName = reinterpret_cast<wstring*>(_accParm);

		W::eLayerType eLayer = (W::eLayerType)((iLayerID >> 24) & 0xFF);
		UINT ID = iLayerID & 0x00FFFFFF;

		GameObject* pObj = SceneManger::FindObject(ID, eLayer);
		if (pObj)
			pObj->UpdateState(*pStrAnimName, iState);

		delete pStrAnimName;
	}

	void EventManager::update_trasnform(DWORD_PTR _lParm, DWORD_PTR _wParm, LONG_PTR _accParm)
	{
		UINT ID = (UINT)_lParm;
		eLayerType eLayer = (eLayerType)_wParm;
		tTransformInfo* tTrInfo = reinterpret_cast<tTransformInfo*>(_accParm);

		GameObject* pObj = SceneManger::FindObject(ID, eLayer);
		
		if (pObj)
		{
			Transform* pTr = pObj->GetComponent<Transform>();
			pTr->recv_transform(tTrInfo->vPosition, tTrInfo->vRotation);
		}
			
		delete tTrInfo;
	}

	void EventManager::CreateObject(GameObject* _pObj, eLayerType _eLayer)
	{
		tEvent eve = {};
		eve.eEventType = EVENT_TYPE::CREATE_OBJECT;
		eve.lParm = (DWORD_PTR)_pObj;
		eve.wParm = (DWORD_PTR)_eLayer;

		AddEvent(eve);
	}

	void EventManager::CreateObjectID(UINT _iSceneLayerCreateIdId, const tTransformInfo& _tTransformInfo, const wstring& _strObjectName)
	{
		//GameObject* pObj = GameObjectManager::GetMonsterOfID(_ID);

		tEvent eve = {};
		eve.eEventType = EVENT_TYPE::CREATE_OBJECT_ID;

		eve.lParm = (DWORD_PTR)_iSceneLayerCreateIdId;
		eve.wParm = (DWORD_PTR)new tTransformInfo(_tTransformInfo);
		eve.accParm = (LONG_PTR)new wstring(_strObjectName);

		AddEvent(eve);
	}


}