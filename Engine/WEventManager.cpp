#include "WEventManager.h"
#include "WSceneManger.h"
#include "WTransform.h"
#include "WObjectPoolManager.h"
#include "..\Engine\WPlayerAttackObject.h"
#include "..\Engine\WMonsterAttackObject.h"
#include "..\Engine\WPlayer.h"
#include "WGameObject.h"
#include "WLayer.h"
#include "WGameObjectManager.h"
#include "..\Engine_Source\WAnimator.h"
#include "..\Engine_Source\WTransform.h"
namespace W
{
	std::function<void(DWORD_PTR, DWORD_PTR, LONG_PTR)> EventManager::m_arrFunction[(UINT)EVENT_TYPE::END] = {};
	std::vector<tEvent> EventManager::m_vecEvent[2] = {};
	atomic<int> EventManager::m_iActiveIdx = 1;

	RWLock EventManager::m_lock = {};

	std::wstring EventManager::m_strNextScene = {};
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

	void EventManager::DeleteObjectID(UINT _ID, eLayerType _eType)
	{
		tEvent eve = {};
		eve.lParm = (DWORD_PTR)_ID;
		eve.wParm = (DWORD_PTR)_eType;
		
		eve.eEventType = EVENT_TYPE::DELET_OBJECT_ID;
		AddEvent(eve);
	}

	/*void EventManager::AddPlayerPool(GameObject* _pObj)
	{
		tEvent eve = {};
		eve.lParm = (DWORD_PTR)_pObj;
	
		eve.eEventType = EVENT_TYPE::ADD_PLAYER_POOL;
	
		Vector3 vPosition = _pObj->GetComponent<Transform>()->GetPosition();
		vPosition.x += ObjectPoolPosition;
		vPosition.y += ObjectPoolPosition;
		_pObj->GetComponent<Transform>()->SetPosition(vPosition);

		AddEvent(eve);
	}

	void EventManager::AddMonsterPool(GameObject* _pObj)
	{
		tEvent eve = {};
		eve.lParm = (DWORD_PTR)_pObj;
		
		eve.eEventType = EVENT_TYPE::ADD_MONSTER_POOL;


		Vector3 vPosition = _pObj->GetComponent<Transform>()->GetPosition();
		vPosition.x += ObjectPoolPosition;
		vPosition.y += ObjectPoolPosition;
		_pObj->GetComponent<Transform>()->SetPosition(vPosition);

		AddEvent(eve);
	}*/

	void EventManager::ChangeScene(const std::wstring& _strNextScene)
	{
		tEvent eve = {};
		eve.eEventType = EVENT_TYPE::SCENE_CHANGE;
		m_strNextScene = _strNextScene;

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

	void EventManager::UpdateTransform(UINT _ID, eLayerType _eType, Vector3 _vPosition)
	{
		tEvent eve = {};
		eve.eEventType = EVENT_TYPE::UPDATE_TRANSFORM;

		eve.lParm = (DWORD_PTR)_ID;
		eve.wParm = (DWORD_PTR)_eType;
		eve.accParm = (DWORD_PTR)new Vector3(_vPosition);

		AddEvent(eve);
	}

	void EventManager::UpdateState(UINT _iLayerID, int _iAnim, const wstring& _strAnimState)
	{
		tEvent eve = {};
		eve.eEventType = EVENT_TYPE::UPDATE_STATE;

		eve.lParm = (DWORD_PTR)_iLayerID;
		eve.wParm = (DWORD_PTR)_iAnim;
		eve.accParm = (DWORD_PTR)new wstring(_strAnimState);

		AddEvent(eve);
	}


	void EventManager::create_object(DWORD_PTR _lParm, DWORD_PTR _wParm, LONG_PTR _accParm)
	{
		GameObject* pObj = (GameObject*)_lParm;
		eLayerType eLyaer = (eLayerType)_wParm;
		pObj->Initialize();
		////나중에 여기서 분기처리 objectpool인지 그냥 삭제인지
		SceneManger::AddGameObject(eLyaer, pObj);
	}

	void EventManager::delete_object(DWORD_PTR _lParm, DWORD_PTR _wParm, LONG_PTR _accParm)
	{
		GameObject* pObj = (GameObject*)_lParm;
		Scene* pScene = (Scene*)_wParm;

		pScene->EraseObject(pObj->GetLayerType(), pObj);
		delete pObj;
	}

	void EventManager::create_object_id(DWORD_PTR _lParm, DWORD_PTR _wParm, LONG_PTR _accParm)
	{
		
	}

	void EventManager::delete_object_id(DWORD_PTR _lParm, DWORD_PTR _wParm, LONG_PTR _accParm)
	{
		UINT ID = (UINT)_lParm;
		eLayerType eLayer = (eLayerType)_wParm;

		GameObject* pObj = SceneManger::FindObject(ID, eLayer);
		SceneManger::GetActiveScene()->EraseObject(eLayer, pObj);

		//나중에 여기서 분기처리 objectpool인지 그냥 삭제인지
		delete pObj;
	}

	void EventManager::change_scene(DWORD_PTR _lParm, DWORD_PTR _wParm, LONG_PTR _accParm)
	{
		SceneManger::LoadScene(m_strNextScene);
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
		int iAnim = (int)_wParm;
		//static_cast는 컴파일러가 타입 간 변환 규칙이 안전하다고 판단할 때만 허용
		//reinterpret_cast는 포인터끼리 강제 변환
		wstring* pStrAnimName = reinterpret_cast<wstring*>(_accParm);

		W::eLayerType eLayer = (W::eLayerType)((iLayerID >> 24) & 0xFF);
		UINT ID = iLayerID & 0x00FFFFFF;

		GameObject* pObj = SceneManger::FindObject(ID, eLayer);
		if (pObj)
			pObj->UpdateState(*pStrAnimName, iAnim);

		delete pStrAnimName;
	}

	void EventManager::update_trasnform(DWORD_PTR _lParm, DWORD_PTR _wParm, LONG_PTR _accParm)
	{
		UINT ID = (UINT)_lParm;
		eLayerType eLayer = (eLayerType)_wParm;
		Vector3* vPosition = reinterpret_cast<Vector3*>(_accParm);

		GameObject* pObj = SceneManger::FindObject(ID, eLayer);
		pObj->GetComponent<Transform>()->recv_position(*vPosition);

		delete vPosition;
	}

	void EventManager::CreateObject(GameObject* _pObj, eLayerType _eLayer)
	{
		tEvent eve = {};
		eve.eEventType = EVENT_TYPE::CREATE_OBJECT;
		eve.lParm = (DWORD_PTR)_pObj;
		eve.wParm = (DWORD_PTR)_eLayer;

		AddEvent(eve);
	}

	void EventManager::CreateObjectID(UINT _ID, eLayerType _eLayer)
	{
		GameObject* pObj = GameObjectManager::GetMonsterOfID(_ID);

		tEvent eve = {};
		eve.eEventType = EVENT_TYPE::CREATE_OBJECT;

		eve.lParm = (DWORD_PTR)pObj;
		eve.wParm = (DWORD_PTR)_eLayer;

		AddEvent(eve);
	}


}