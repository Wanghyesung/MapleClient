#include "WSceneManger.h"
#include "WCamera.h"
#include "WRenderer.h"
#include "..\Engine\WCameraScript.h"
#include "..\Engine\WBossUI.h"
#include "..\Engine\WItemManager.h"
#include "..\Engine\WPlayerAttackObject.h"
#include "..\Engine\WObjectPoolManager.h"

namespace W
{
	Scene* SceneManger::m_pActiveScene = nullptr;
	std::map<std::wstring, Scene*> SceneManger::m_mapScene = {};
	void SceneManger::Initialize()
	{

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

		ObjectPoolManager::Release();
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

		SwapUI(m_pActiveScene, iter->second);
		
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

	
	void SceneManger::SwapCamera()
	{
		std::vector<GameObject*> vecObjs =
			m_pActiveScene->GetLayer(eLayerType::Camera).GetGameObjects();
		
		////1 main , 2 UI
		renderer::MainCamera = vecObjs[0]->GetComponent<Camera>();
		renderer::UICamera = vecObjs[1]->GetComponent<Camera>();

		vecObjs[0]->GetScript<CameraScript>()->SetPlayer(FindPlayer());
	}

	

}
