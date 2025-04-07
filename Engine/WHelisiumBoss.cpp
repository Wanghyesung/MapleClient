#include "WHelisiumBoss.h"
#include "WResources.h"
#include "WCamera.h"
#include "WCameraScript.h"
#include "WGround.h"
#include "WMegnus.h"
#include "WThreadPool.h"
#include "WTransform.h"

namespace W
{
	HelisiumBoss::HelisiumBoss()
	{
		SetMapSize(-7.5f, -1.f, 7.5f, -1.f);
		SetMapPossibleSize(-14.f, 14.f);

		std::shared_ptr<Texture> pTempleBossTex =
			Resources::Load<Texture>(L"HelisiumBoss", L"..\\Resources\\Texture\\background\\Helisium_boss.png");
		std::shared_ptr<Material> pMater = std::make_shared<Material>();
		pMater->SetShader(Resources::Find<Shader>(L"BackgroundShader"));
		pMater->SetTexture(pTempleBossTex);
		Resources::Insert(L"HelisiumBossMater", pMater);

		m_vecResource.push_back(std::make_pair(L"Megnus1", L"..\\Resources\\Texture\\Monster\\megnus\\megnus0.png"));
		m_vecResource.push_back(std::make_pair(L"Megnus2", L"..\\Resources\\Texture\\Monster\\megnus\\megnus1.png"));
		m_vecResource.push_back(std::make_pair(L"Megnus_attack1_effect", L"..\\Resources\\Texture\\Monster\\megnus\\attack1_effect.png"));
		m_vecResource.push_back(std::make_pair(L"magnus_stone", L"..\\Resources\\Texture\\Monster\\megnus\\magnusstone.png"));

		m_vecResource.push_back(std::make_pair(L"Megnus_Zone0", L"..\\Resources\\Texture\\Monster\\megnus\\mobzon1.png"));
		m_vecResource.push_back(std::make_pair(L"Megnus_Zone1", L"..\\Resources\\Texture\\Monster\\megnus\\mobzon2.png"));
		m_vecResource.push_back(std::make_pair(L"Megnus_Zone2", L"..\\Resources\\Texture\\Monster\\megnus\\mobzon3.png"));
		m_vecResource.push_back(std::make_pair(L"Megnus_Zone3", L"..\\Resources\\Texture\\Monster\\megnus\\mobzon4.png"));

		m_vecResource.push_back(std::make_pair(L"sleepGas", L"..\\Resources\\Texture\\Monster\\megnus\\gas\\sleepGas.png"));

	}
	HelisiumBoss::~HelisiumBoss()
	{

	}
	void HelisiumBoss::Initialize()
	{
		CreateBackground();

		{
			GameObject* pCamera = new GameObject();
			pCamera->SetName(L"ObjCam");
			AddGameObject(eLayerType::Camera, pCamera);
			pCamera->GetComponent<Transform>()->SetPosition(Vector3(0.f, 0.f, -10.f));
			Camera* pCameraComp = pCamera->AddComponent<Camera>();
			pCameraComp->TurnLayerMask(eLayerType::UI, false);
			pCamera->AddComponent<CameraScript>();
		}

		//ui camera
		{
			GameObject* pUICamera = new GameObject();
			pUICamera->SetName(L"UICam");
			AddGameObject(eLayerType::Camera, pUICamera);
			pUICamera->GetComponent<Transform>()->SetPosition(Vector3(0.f, 0.f, -10.f));
			Camera* pCameraComp = pUICamera->AddComponent<Camera>();
			pCameraComp->TurnUILayerMask();//UI만 그리게
			//pCamera->AddComponent<CameraScript>();
		}
	}
	void HelisiumBoss::Update()
	{
		Scene::Update();
	}
	void HelisiumBoss::LateUpdate()
	{
		Scene::LateUpdate();
	}
	void HelisiumBoss::Render()
	{
		Scene::Render();

	}
	void HelisiumBoss::OnEnter()
	{
		Scene::OnEnter();
		ThreadPool::Joinable();

		create_monster();

	}
	void HelisiumBoss::OnExit()
	{
		Scene::OnExit();

	}
	void HelisiumBoss::CreateBackground()
	{
		GameObject* pBackGround = new GameObject();
		
		AddGameObject(eLayerType::Background, pBackGround);
		MeshRenderer* pMeshRender = pBackGround->AddComponent<MeshRenderer>();
		pMeshRender->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
		pMeshRender->SetMaterial(Resources::Find<Material>(L"HelisiumBossMater"));
		pBackGround->GetComponent<Transform>()->SetPosition(0.f, 0.f, 0.f);
		//2 : 1
		pBackGround->GetComponent<Transform>()->SetScale(3.65f * 8.f, 1.f * 8.f, 1.f);

	}
	void HelisiumBoss::StartSound()
	{
		const std::vector<GameObject*> m_vecBackGround = GetLayer(eLayerType::Background).GetGameObjects();
		AudioSource* pAudio = m_vecBackGround[0]->GetComponent<AudioSource>();
		pAudio->SetLoop(true);
		pAudio->Play();
	}

	void HelisiumBoss::EndSound()
	{
		const std::vector<GameObject*> m_vecBackGround = GetLayer(eLayerType::Background).GetGameObjects();
		AudioSource* pAudio = m_vecBackGround[0]->GetComponent<AudioSource>();
		pAudio->Stop();
	}
	void HelisiumBoss::create_monster()
	{
		//Megnus* pMegnus = new Megnus();
		//pMegnus->Initialize();
		//AddGameObject(eLayerType::Monster, pMegnus);
	}

	void HelisiumBoss::create_effect()
	{
		
		Resources::Load<Texture>(L"Megnus_attack0_hit", L"..\\Resources\\Texture\\Monster\\megnus\\attack0_hit.png");
		
		Resources::Load<Texture>(L"Megnus_attack1_hit", L"..\\Resources\\Texture\\Monster\\megnus\\attack1_hit.png");
		
		Resources::Load<Texture>(L"Megnus_attack2_hit", L"..\\Resources\\Texture\\Monster\\megnus\\attack2_hit.png");

		Resources::Load<Texture>(L"Megnus_attack3_hit", L"..\\Resources\\Texture\\Monster\\megnus\\attack3_hit.png");

		Resources::Load<Texture>(L"Megnus_attack4_hit", L"..\\Resources\\Texture\\Monster\\megnus\\attack4_hit.png");
		
	}
}