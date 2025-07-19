#include "WHelisiumBoss.h"
#include "WResources.h"
#include "WCamera.h"
#include "WCameraScript.h"
#include "WGround.h"
#include "WMegnus.h"
#include "WThreadPool.h"
#include "WTransform.h"
#include "WEffect.h"

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

		m_vecResource.push_back(std::make_pair(L"Megnus_attack0_hit", L"..\\Resources\\Texture\\Monster\\megnus\\attack0_hit.png"));
		m_vecResource.push_back(std::make_pair(L"Megnus_attack1_hit", L"..\\Resources\\Texture\\Monster\\megnus\\attack1_hit.png"));
		m_vecResource.push_back(std::make_pair(L"Megnus_attack2_hit", L"..\\Resources\\Texture\\Monster\\megnus\\attack2_hit.png"));
		m_vecResource.push_back(std::make_pair(L"Megnus_attack3_hit", L"..\\Resources\\Texture\\Monster\\megnus\\attack3_hit.png"));
		m_vecResource.push_back(std::make_pair(L"Megnus_attack4_hit", L"..\\Resources\\Texture\\Monster\\megnus\\attack4_hit.png"));

		m_vecSoundResource.push_back(std::make_pair(L"Helisiumsound", L"..\\Resources\\sound\\thefinalWar.mp3"));

	}
	HelisiumBoss::~HelisiumBoss()
	{

	}
	void HelisiumBoss::Initialize()
	{
		CreateBackground();
		add_objectpool();
		{
			GameObject* pCamera = new GameObject();
			pCamera->SetObjectID(0);
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
			pUICamera->SetObjectID(1);
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
		

	}
	void HelisiumBoss::OnExit()
	{
		Scene::OnExit();

	}

	void HelisiumBoss::SendEnter()
	{
		mapping_resource();

		Scene::SendEnter();
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

	void HelisiumBoss::add_objectpool()
	{
		Megnus* pMegnus = new Megnus();
		ObjectPoolManager::AddObjectPool(pMegnus->GetName(), pMegnus);

		Effect* pEffect = nullptr;
		for (int i = 0; i < 5; ++i)
		{
			pEffect = new Effect();
			pEffect->CreateAnimation(nullptr, L"Megnus_attack0_hit", Vector2(0.f, 0.f), Vector2(320.f, 244.f), 5, 1, Vector2(320.f, 320.f), Vector2::Zero, Vector2(1600.f, 244.f));
			ObjectPoolManager::AddObjectPool(pEffect->GetName(), pEffect);
		}
		
		for (int i = 0; i < 5; ++i)
		{
			pEffect = new Effect();
			pEffect->CreateAnimation(nullptr, L"Megnus_attack1_hit", Vector2(0.f, 0.f), Vector2(256.f, 196.f), 5, 1, Vector2(250.f, 250.f), Vector2(0.f, 0.f), Vector2(1280.f, 192.f));
			ObjectPoolManager::AddObjectPool(pEffect->GetName(), pEffect);
		}
		
		for (int i = 0; i < 5; ++i)
		{
			pEffect = new Effect();
			pEffect->CreateAnimation(nullptr, L"Megnus_attack2_hit", Vector2(0.f, 0.f), Vector2(236.f, 229.f), 7, 1, Vector2(240.f, 240.f), Vector2(0.f, 0.f), Vector2(1652.f, 229.f));
			ObjectPoolManager::AddObjectPool(pEffect->GetName(), pEffect);
		}
		for (int i = 0; i < 5; ++i)
		{
			pEffect = new Effect();
			pEffect->CreateAnimation(nullptr, L"Megnus_attack3_hit", Vector2(0.f, 0.f), Vector2(228.f, 231.f), 7, 1, Vector2(230.f, 230.f), Vector2(0.f, 0.f), Vector2(1596.f, 231.f));
			ObjectPoolManager::AddObjectPool(pEffect->GetName(), pEffect);
		}
		for (int i = 0; i < 5; ++i)
		{
			pEffect = new Effect();
			pEffect->CreateAnimation(nullptr, L"Megnus_attack4_hit", Vector2(0.f, 0.f), Vector2(165.f, 168.f), 7, 1, Vector2(170.f, 170.f), Vector2(0.f, 0.f), Vector2(825.f, 168.f));
			ObjectPoolManager::AddObjectPool(pEffect->GetName(), pEffect);
		}
	}
	void HelisiumBoss::mapping_resource()
	{
		
		mapping_texture(L"Megnus_attack0_hit", L"Megnus_attack0_hit");
		mapping_texture(L"Megnus_attack1_hit", L"Megnus_attack1_hit");
		mapping_texture(L"Megnus_attack2_hit", L"Megnus_attack2_hit");
		mapping_texture(L"Megnus_attack3_hit", L"Megnus_attack3_hit");
		mapping_texture(L"Megnus_attack4_hit", L"Megnus_attack4_hit");
	}
	
	void HelisiumBoss::create_monster()
	{
		
	}

	void HelisiumBoss::create_effect()
	{
		
		
		
	}
}