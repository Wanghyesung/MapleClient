#include "WSceneManger.h"
#include "WCamera.h"
#include "WRenderer.h"
#include "WRigidbody.h"
//#include "WPlayScene.h"
//#include "WLeafreScene.h"
//#include "WValleyScene.h"
//#include "WValleyScene_2.h"
//#include "WCaveScene.h"
//#include "WTempleScene.h"
//#include "WTempleScene_2.h"
//#include "WTempleBossScene.h"
#include "..\Engine\WCameraScript.h"
#include "..\Engine\WBossUI.h"
#include "..\Engine\WBattleManager.h"
#include "..\Engine\WItemManager.h"
#include "..\Engine\WPlayerAttackObject.h"
#include "..\Engine\WObjectPoolManager.h"
#include "..\Engine\WMonsterManager.h"
namespace W
{
	Scene* SceneManger::m_pActiveScene = nullptr;
	std::map<std::wstring, Scene*> SceneManger::m_mapScene = {};
	void SceneManger::Initialize()
	{
		//m_pActiveScene = nullptr;
		//PlayScene* pPlayScene = new PlayScene();
		//m_mapScene.insert(std::make_pair(L"PlayScene", pPlayScene));
		//LeafreScene* pLeaf  = new LeafreScene();
		//m_mapScene.insert(std::make_pair(L"Leafre", pLeaf));
		//ValleyScene* pValleyScene = new ValleyScene();
		//m_mapScene.insert(std::make_pair(L"Valley", pValleyScene));
		//ValleyScene_2* pValleyScene2 = new ValleyScene_2();
		//m_mapScene.insert(std::make_pair(L"Valley2", pValleyScene2));
		//CaveScene* pCaveSene = new CaveScene();
		//m_mapScene.insert(std::make_pair(L"Cave", pCaveSene));
		//TempleScene* pTemple = new TempleScene();
		//m_mapScene.insert(std::make_pair(L"Temple", pTemple));
		//TempleScene_2* pTemple2 = new TempleScene_2();
		//m_mapScene.insert(std::make_pair(L"Temple2", pTemple2));
		//TempleBossScene* pTempleBoss = new TempleBossScene();
		//m_mapScene.insert(std::make_pair(L"TempleBoss", pTempleBoss));
		//
		//m_pActiveScene = pLeaf;
		//
		//for (auto iter : m_mapScene)
		//{
		//	iter.second->Initialize();
		//}

	}
	void SceneManger::Update()
	{
		m_pActiveScene->Update();
	}
	void SceneManger::LateUpdate()
	{
		m_pActiveScene->LateUpdate();
	}
	void SceneManger::Render()
	{
		m_pActiveScene->Render();
	}

	void SceneManger::Destroy()
	{
		m_pActiveScene->Destroy();
	}

	void SceneManger::Release()
	{
		for (auto &iter : m_mapScene)
		{
			delete iter.second;
			iter.second = nullptr;
		}

		MonsterManager::DeleteMonster();
		ObjectPoolManager::Release();
		BattleManager::Release();
		ItemManager::Release();
	}

	void SceneManger::Erase(GameObject* _pGameObject)
	{
		m_pActiveScene->EraseObject(_pGameObject->GetLayerType(),_pGameObject);
	}
	Scene* SceneManger::LoadScene(std::wstring _strName)
	{
		std::map<std::wstring, Scene*>::iterator iter =
			m_mapScene.find(_strName);

		if (iter == m_mapScene.end())
			return nullptr;


		PushObjectPool(m_pActiveScene);//현재 씬 공격 오브젝트 회수
		SwapUI(m_pActiveScene, iter->second);
		SwapPlayer(m_pActiveScene, iter->second);

		m_pActiveScene->OnExit();
		m_pActiveScene = iter->second;
		m_pActiveScene->OnEnter();

		SwapCamera();
		return iter->second;
	}

	GameObject* SceneManger::FindPlayer()
	{
		std::vector<GameObject*> vecObjs = 
			m_pActiveScene->GetLayer(eLayerType::Player).GetGameObjects();

		return vecObjs[0];
	}

	void SceneManger::SwapObject(Scene* _pPrevScene, Scene* _pNextScene, GameObject* _pGameObject)
	{
		eLayerType eType = _pGameObject->GetLayerType();
		
		_pPrevScene->EraseObject(eType, _pGameObject);
		_pNextScene->AddGameObject(eType, _pGameObject);
	}

	void SceneManger::SwapUI(Scene* _pPrevScene, Scene* _pNextScene)
	{
		SwapObject(_pPrevScene, _pNextScene, (GameObject*)GetUI<class InterfaceUI>());
		SwapObject(_pPrevScene, _pNextScene, (GameObject*)GetUI<class Inventory>());
		SwapObject(_pPrevScene, _pNextScene, (GameObject*)GetUI<class Stat>());
		SwapObject(_pPrevScene, _pNextScene, (GameObject*)GetUI<class EquipState>());
		SwapObject(_pPrevScene, _pNextScene, (GameObject*)GetUI<class SKillStorage>());
		SwapObject(_pPrevScene, _pNextScene, (GameObject*)GetUI<class BossUI>());
	}

	void SceneManger::SwapPlayer(Scene* _pPrevScene, Scene* _pNextScene)
	{
		GameObject* pPlayer = FindPlayer();
		Vector3 vPos = pPlayer->GetComponent<Transform>()->GetPosition();
		vPos.x = 0.f; vPos.y = 0.f;
		pPlayer->GetComponent<Transform>()->SetPosition(vPos);
		pPlayer->GetComponent<Rigidbody>()->SetGround(false);

		SwapObject(_pPrevScene, _pNextScene, pPlayer);
	}

	void SceneManger::SwapCamera()
	{
		std::vector<GameObject*> vecObjs =
			m_pActiveScene->GetLayer(eLayerType::Camera).GetGameObjects();
		
		////1 main , 2 UI
		renderer::MainCamera = vecObjs[0]->GetComponent<Camera>();
		renderer::UICamera = vecObjs[1]->GetComponent<Camera>();

		vecObjs[0]->GetScript<CameraScript>()->SetPlayer(FindPlayer());
	}

	void SceneManger::PushObjectPool(Scene* _pPrevScene)
	{
		std::vector<GameObject*> m_vecObj =
			_pPrevScene->GetLayer(eLayerType::AttackObject).GetGameObjects();

		for (int i = 0; i < m_vecObj.size(); ++i)
			dynamic_cast<PlayerAttackObject*>(m_vecObj[i])->Off();
	}

}
