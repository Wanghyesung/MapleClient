#include "WScene.h"
#include "WUI.h"
#include "WThreadPool.h"
#include "..\Engine\WMonsterHP.h"
#include "WSceneManger.h"
namespace W
{
	std::vector<eLayerType> Scene::m_vecUpdateLayer = 
	{eLayerType::Camera, eLayerType::Background, eLayerType::Light,eLayerType::UI};

	Scene::Scene()
	{
		m_vecLayer.resize((UINT)W::eLayerType::End);
	}
	Scene::~Scene()
	{
	}
	void Scene::Initialize()
	{
	}
	void Scene::Update()
	{
		for (eLayerType eType : m_vecUpdateLayer)
		{
			Layer& UILayer = m_vecLayer[(UINT)eType];
			UILayer.Update();
		}
		
	}
	void Scene::LateUpdate()
	{
		for (eLayerType eType : m_vecUpdateLayer)
		{
			Layer& UILayer = m_vecLayer[(UINT)eType];
			UILayer.LateUpdate();
		}
	}
	void Scene::Render()
	{
		for (eLayerType eType : m_vecUpdateLayer)
		{
			Layer& UILayer = m_vecLayer[(UINT)eType];
			UILayer.Render();
		}
	}

	void Scene::Destroy()
	{
		for (UINT i = 0; i < m_vecLayer.size(); ++i)
		{
			if (i == (UINT)eLayerType::UI)
				continue;

			m_vecLayer[i].Destory();
		}
	}

	void Scene::OnEnter()
	{
		for (int i = 0; i < m_vecResource.size(); ++i)
		{
			ThreadPool::LoadingResource<Texture>(m_vecResource[i].first, m_vecResource[i].second);
		}
	}
	void Scene::OnExit()
	{
		for (int i = 0; i < m_vecResource.size(); ++i)
		{
			ThreadPool::DeleteResource<Texture>(m_vecResource[i].first);
		}
	}
	void Scene::AddGameObject(eLayerType _eType, GameObject* _pGameObj)
	{
		m_vecLayer[(UINT)_eType].AddGameObject(_pGameObj);
		_pGameObj->SetLayerType(_eType);
	}

	
}