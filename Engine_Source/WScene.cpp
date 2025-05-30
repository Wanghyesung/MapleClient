#include "WScene.h"
#include "WUI.h"
#include "WThreadPool.h"
#include "..\Engine\WMonsterHP.h"
#include "WSceneManger.h"
#include "Map.pb.h"



namespace W
{
	//std::vector<eLayerType> Scene::m_vecUpdateLayer = 
	//{eLayerType::Camera, eLayerType::Background, eLayerType::Light,eLayerType::UI};

	Scene::Scene()
	{
		for (UINT i = 0; i < (UINT)eLayerType::End; ++i)
		{
			m_vecLayer.push_back(new Layer());
		}
	}
	Scene::~Scene()
	{
		for (UINT i = 0; i < (UINT)eLayerType::End; ++i)
		{
			delete m_vecLayer[i];
			m_vecLayer[i] = nullptr;
		}
	}
	void Scene::Initialize()
	{
	}
	void Scene::Update()
	{
		for (Layer* layer : m_vecLayer)
		{
			layer->Update();
		}
		
	}
	void Scene::LateUpdate()
	{
		for (Layer* layer : m_vecLayer)
		{
			layer->LateUpdate();
		}
	}
	void Scene::Render()
	{
		for (Layer* layer : m_vecLayer)
		{
			layer->Render();
		}
	}

	void Scene::OnEnter()
	{
		for (int i = 0; i < m_vecResource.size(); ++i)
		{
			ThreadPool::LoadingResource<Texture>(m_vecResource[i].first, m_vecResource[i].second);
		}

		SendEnter();
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
		m_vecLayer[(UINT)_eType]->AddGameObject(_pGameObj);
		_pGameObj->SetLayerType(_eType);
	}

	void Scene::Scene::SendEnter()
	{
		Protocol::C_MAP pkt;
		pkt.set_scene(WstringToString(GetName()));
		pkt.set_player_id(PLAYER_ID);

		shared_ptr<SendBuffer> pSendBuffer = ServerPacketHandler::MakeSendBuffer(pkt);
		GClientService->GetClientSession()->Send(pSendBuffer);
	}
	
}