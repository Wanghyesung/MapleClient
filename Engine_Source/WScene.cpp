#include "WScene.h"
#include "WUI.h"
#include "WThreadPool.h"
#include "..\Engine\WMonsterHP.h"
#include "..\Engine\WEventManager.h"
#include "WSceneManger.h"
#include "Map.pb.h"
#include "..\Engine\WObjectPoolManager.h"


namespace W
{
	//std::vector<eLayerType> Scene::m_vecUpdateLayer = 
	//{eLayerType::Camera, eLayerType::Background, eLayerType::Light,eLayerType::UI};

	Scene::Scene() :
		m_bLoading(false)
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
		if (!m_bLoading)
		{
			for (Layer* layer : m_vecLayer)
			{
				layer->Update();
			}
		}

	}
	void Scene::LateUpdate()
	{
		if (!m_bLoading)
		{
			for (Layer* layer : m_vecLayer)
			{
				layer->LateUpdate();
			}
		}
	}
	void Scene::Render()
	{
		if (!m_bLoading)
		{
			for (Layer* layer : m_vecLayer)
			{
				layer->Render();
			}
		}
	}

	void Scene::OnEnter()
	{
		for (int i = 0; i < m_vecResource.size(); ++i)
			ThreadPool::LoadingResource<Texture>(m_vecResource[i].first, m_vecResource[i].second);


		StartLoading();
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

	void Scene::SendEnter()
	{
		Protocol::C_MAP pkt;

		const wstring& strNextScenename = GetName();
		if (GHashWstringToString.find(strNextScenename) == GHashWstringToString.end())
			GHashWstringToString[strNextScenename] = WstringToString(strNextScenename);

		pkt.set_scene(GHashWstringToString[strNextScenename]);
		pkt.set_player_id(PLAYER_ID);

		SceneManger::StartWaitForMapData();

		shared_ptr<SendBuffer> pSendBuffer = ServerPacketHandler::MakeSendBuffer(pkt);
		GClientService->GetClientSession()->Send(pSendBuffer);
	}

	void Scene::RenderLoading()
	{

		static shared_ptr<Mesh> pRectMesh = Resources::Find<Mesh>(L"RectMesh");
		static shared_ptr<Material> pMtrl = Resources::Find<Material>(L"FullScreenMaterial");
		//
		static bool bSet = false;
		if (!bSet)
		{
			//텍스쳐 따로 로딩
			wstring strFileName = L"..\\Resources\\Texture\\background\\start_logo.png";
			//
			bSet = true;
			pMtrl->SetTexture(Resources::Load<Texture>(L"LoadingTex", strFileName));
		}


		pRectMesh->BindBuffer();
		pMtrl->Binds();

		pRectMesh->Render();

		pMtrl->Clear();
	}

	void Scene::mapping_texture(const wstring& _strTexName, const wstring& _strObjectName, const wstring& _strObjectAnimName)
	{
		std::shared_ptr<Texture> pAtlas = Resources::Find<Texture>(_strTexName);
		auto& vec = ObjectPoolManager::GetObejcts(_strObjectName);

		if (_strObjectAnimName.empty())
		{
			for (int i = 0; i < vec.size(); ++i)
				vec[i]->GetComponent<Animator>()->SetTexture(pAtlas);
		}
		else
		{
			for (int i = 0; i < vec.size(); ++i)
				vec[i]->GetComponent<Animator>()->SetTexture(_strObjectAnimName, pAtlas);
		}
	}
}