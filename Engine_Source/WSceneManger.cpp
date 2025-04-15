#include "WSceneManger.h"
#include "WCamera.h"
#include "WRenderer.h"
#include "..\Engine\WCameraScript.h"
#include "..\Engine\WItemManager.h"
#include "..\Engine\WPlayerAttackObject.h"
#include "..\Engine\WObjectPoolManager.h"

extern UINT PLAYER_ID;
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
		SwapPlayer(m_pActiveScene, iter->second);

		m_pActiveScene->OnExit();
		m_pActiveScene = iter->second;
		m_pActiveScene->OnEnter();

		SwapCamera();
		return iter->second;
	}

	GameObject* SceneManger::FindPlayer()
	{		
		std::unordered_map<UINT, GameObject*> vecObjs = 
			m_pActiveScene->GetLayer(eLayerType::Player).GetGameObjects();

		return vecObjs[PLAYER_ID];
	}

	void SceneManger::SwapObject(Scene* _pPrevScene, Scene* _pNextScene, GameObject* _pGameObject)
	{
		eLayerType eType = _pGameObject->GetLayerType();
		
		_pPrevScene->EraseObject(eType, _pGameObject);
		_pNextScene->AddGameObject(eType, _pGameObject);
	}

	void SceneManger::SwapObject(Scene* _pPrevScene, Scene* _pNextScene, const std::wstring& _strGameName, eLayerType _eLayerType)
	{
		GameObject* pGameObject = _pPrevScene->GetLayer(_eLayerType).FindObjectByName(_strGameName);
		if (pGameObject == nullptr)
			assert(nullptr);

		eLayerType eType = pGameObject->GetLayerType();

		_pPrevScene->EraseObject(eType, pGameObject);
		_pNextScene->AddGameObject(eType, pGameObject);
	}

	void SceneManger::SwapUI(Scene* _pPrevScene, Scene* _pNextScene)
	{
		SwapObject(_pPrevScene, _pNextScene, L"Equip", eLayerType::UI);
		SwapObject(_pPrevScene, _pNextScene, L"Interface", eLayerType::UI);
		SwapObject(_pPrevScene, _pNextScene, L"Boss", eLayerType::UI);
		SwapObject(_pPrevScene, _pNextScene, L"Inven", eLayerType::UI);
		SwapObject(_pPrevScene, _pNextScene, L"Skill", eLayerType::UI);	
	}

	void SceneManger::SwapPlayer(Scene* _pPrevScene, Scene* _pNextScene)
	{
		SwapObject(_pPrevScene, _pNextScene, L"Player", eLayerType::Player);
	}

	
	void SceneManger::SwapCamera()
	{

		std::unordered_map<UINT, GameObject*> hashObj =
			m_pActiveScene->GetLayer(eLayerType::Camera).GetGameObjects();
		
		////1 main , 2 UI
		renderer::MainCamera = hashObj[0]->GetComponent<Camera>();
		renderer::UICamera = hashObj[1]->GetComponent<Camera>();

		hashObj[0]->GetScript<CameraScript>()->SetPlayer(FindPlayer());
	}

	

}
