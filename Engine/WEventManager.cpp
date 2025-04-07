#include "WEventManager.h"
#include "WSceneManger.h"
#include "WTransform.h"
#include "WObjectPoolManager.h"
#include "..\Engine\WPlayerAttackObject.h"
#include "..\Engine\WMonsterAttackObject.h"
#include "WGameObject.h"
#include "WLayer.h"
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
		case EVENT_TYPE::CREATE_OBJECT:
		{
			GameObject* pObj = (GameObject*)_tEve.lParm;
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
	void EventManager::CreateObject(GameObject* _pObj, eLayerType _eLayer)
	{
		tEvent eve = {};
		eve.eEventType = EVENT_TYPE::CREATE_OBJECT;
		eve.lParm = (DWORD_PTR)_pObj;
		eve.wParm = (DWORD_PTR)_eLayer;

		AddEvent(eve);
	}


}