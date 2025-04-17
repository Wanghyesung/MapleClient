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
	std::vector<tEvent> EventManager::m_vecEvent = {};


	std::wstring EventManager::m_strNextScene = {};
#define ObjectPoolPosition 2000.f
	void EventManager::Update()
	{
		for (int i = 0; i < m_vecEvent.size(); ++i)
		{
			excute(m_vecEvent[i]);
		}
		m_vecEvent.clear();
	}
	
	void EventManager::excute(const tEvent& _tEve)
	{
		switch (_tEve.eEventType)
		{
		case EVENT_TYPE::UPDATE_TRANSFORM:
		{
			UINT ID = (UINT)_tEve.lParm;
			eLayerType eLayer = (eLayerType)_tEve.wParm;
			Vector3* vPosition = reinterpret_cast<Vector3*>(_tEve.accParm);
			
			GameObject* pObj = SceneManger::FindObject(ID, eLayer);
			if (pObj != nullptr)
				pObj->GetComponent<Transform>()->SetPosition(*vPosition);

			delete vPosition;
		}
		break;

		case EVENT_TYPE::UPDATE_STATE:
		{
			//UINT ID = (UINT)_tEve.lParm;
			//eLayerType eLayer = (eLayerType)_tEve.wParm;
			//wstring* pStrAnimName = reinterpret_cast<wstring*>(_tEve.accParm);
			//
			//GameObject* pObj = SceneManger::FindObject(ID, eLayer);
			//if (pObj == nullptr)
			//	assert(nullptr);
			//
			//pObj->GetComponent<Animator>()->Play()

		}
		break;

		case EVENT_TYPE::CREATE_PLAYER:
		{
			UINT iPlayerID = (UINT)_tEve.lParm;
			UINT iObjectID = (UINT)_tEve.wParm;

			Player* pPlayer = new Player();
			pPlayer->SetName(L"Player");
			pPlayer->m_iPlayerID = iPlayerID;
			pPlayer->SetObjectID(iObjectID);
			pPlayer->Initialize();
			pPlayer->SetTargetPlayer();

			SceneManger::AddGameObject(eLayerType::Player, pPlayer);
		}
		break;

		case EVENT_TYPE::CREATE_OTHER_PLAYER:
		{
			UINT iPlayerID = (UINT)_tEve.lParm;
			UINT iObjectID = (UINT)_tEve.wParm;

			Player* pPlayer = new Player();
			pPlayer->SetName(L"Other_Player");
			pPlayer->m_iPlayerID = iPlayerID;
			pPlayer->SetObjectID(iObjectID);
			pPlayer->Initialize();

			SceneManger::AddGameObject(eLayerType::Player, pPlayer);
		}
		break;

		case EVENT_TYPE::CREATE_OBJECT:
		{
			GameObject* pObj = (GameObject*)_tEve.lParm;
			pObj->Initialize();

			eLayerType eLyaer = (eLayerType)_tEve.wParm;

			SceneManger::AddGameObject(eLyaer, pObj);
		}
		break;

		case EVENT_TYPE::DELET_OBJECT:
		{
			GameObject* pObj = (GameObject*)_tEve.lParm;
			Scene* pScene = (Scene*)_tEve.wParm;

			pScene->EraseObject(pObj->GetLayerType(), pObj);
			delete pObj;
		}
		break;

		case EVENT_TYPE::DELET_OBJECT_ID:
		{
			UINT ID = (UINT)_tEve.lParm;
			eLayerType eLayer = (eLayerType)_tEve.wParm;

			GameObject* pObj = SceneManger::FindObject(ID, eLayer);
			SceneManger::GetActiveScene()->EraseObject(eLayer, pObj);

			delete pObj;
		}
		break;

		case EVENT_TYPE::SCENE_CHANGE:
		{
			SceneManger::LoadScene(m_strNextScene);
		}
		break;

		//case EVENT_TYPE::ADD_PLAYER_POOL:
		//{
		//	GameObject* pObj = (GameObject*)_tEve.lParm;
		//
		//	m_vecPlayer_Pool.push_back(pObj);
		//}
		//break;
		//
		//case EVENT_TYPE::ADD_MONSTER_POOL:
		//{
		//	GameObject* pObj = (GameObject*)_tEve.lParm;
		//
		//	m_vecMonster_Pool.push_back(pObj);
		//}
		//break;

		}
	}
	void EventManager::DeleteObject(GameObject* _pObj, Scene* _pScene)
	{
		tEvent eve = {};
		eve.lParm = (DWORD_PTR)_pObj;
		eve.wParm = (DWORD_PTR)_pScene;

		eve.eEventType = EVENT_TYPE::DELET_OBJECT;
		AddEvent(eve);
	}

	void EventManager::DeleteObject(UINT _ID, eLayerType _eType)
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
	void EventManager::AddPlayer(UINT _iPlayerID, UINT _iObjectID, vector<UINT> _vecPlayerID, vector<UINT> _vecObjectID)
	{
		tEvent eve = {};
		eve.eEventType = EVENT_TYPE::CREATE_PLAYER;
		eve.lParm = (DWORD_PTR)_iPlayerID;
		eve.wParm = (DWORD_PTR)_iObjectID;
		AddEvent(eve);

		for (int i = 0; i < _vecPlayerID.size(); ++i)
			AddOtherPlayer(_vecPlayerID[i],_vecObjectID[i]);
	}
	void EventManager::AddOtherPlayer(UINT _iPlayerID, UINT _iObjectID)
	{
		tEvent eve = {};
		eve.eEventType = EVENT_TYPE::CREATE_OTHER_PLAYER;

		eve.lParm = (DWORD_PTR)_iPlayerID;
		eve.wParm = (DWORD_PTR)_iObjectID;
	
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

	void EventManager::UpdateState(UINT _ID, eLayerType _eLayer, const wstring& _strAnimState)
	{
		tEvent eve = {};
		eve.eEventType = EVENT_TYPE::UPDATE_STATE;

		eve.lParm = (DWORD_PTR)_ID;
		eve.wParm = (DWORD_PTR)_eLayer;
		eve.accParm = (DWORD_PTR)new wstring(_strAnimState);

		AddEvent(eve);
	}

	void EventManager::CreateObject(GameObject* _pObj, eLayerType _eLayer)
	{
		tEvent eve = {};
		eve.eEventType = EVENT_TYPE::CREATE_OBJECT;
		eve.lParm = (DWORD_PTR)_pObj;
		eve.wParm = (DWORD_PTR)_eLayer;

		AddEvent(eve);
	}

	void EventManager::CreateObject(UINT _ID, eLayerType _eLayer)
	{
		GameObject* pObj = GameObjectManager::GetMonsterOfID(_ID);

		tEvent eve = {};
		eve.eEventType = EVENT_TYPE::CREATE_OBJECT;

		eve.lParm = (DWORD_PTR)pObj;
		eve.wParm = (DWORD_PTR)_eLayer;

		AddEvent(eve);
	}


}