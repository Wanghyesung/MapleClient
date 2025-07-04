#include "WTempleBossScene.h"
#include "WResources.h"
#include "WShader.h"
#include "WGameObject.h"
#include "WMesh.h"
#include "WMaterial.h"
#include "WMeshRenderer.h"
#include "WTransform.h"
#include "WInput.h"
#include "WSceneManger.h"
#include "WCamera.h"
#include "WCameraScript.h"
#include "WNPC.h"
#include "WGround.h"
#include "WSolomon.h"
#include "WRex.h"
#include "WMunin.h"
#include "WAriel.h"
#include "WPinkBean.h"
#include "WWhiggin.h"
#include "WThreadPool.h"
#include "WEffect.h"
namespace W
{
	TempleBossScene::TempleBossScene()
	{
		SetMapSize(-0.5f, 0.f, 0.5f, 0.f);
		SetMapPossibleSize(-7.5f, 7.5f);

		m_vecResource.push_back(std::make_pair(L"PinkBean1", L"..\\Resources\\Texture\\Monster\\Pinkbean\\PinkBean\\Pinkbean1.png"));
		m_vecResource.push_back(std::make_pair(L"PinkBean2", L"..\\Resources\\Texture\\Monster\\Pinkbean\\PinkBean\\Pinkbean2.png"));
		m_vecResource.push_back(std::make_pair(L"PinkBean_attack0", L"..\\Resources\\Texture\\Monster\\PinkBean\\PinkBean\\attack0_effect.png"));
		m_vecResource.push_back(std::make_pair(L"PinkBean_attack2", L"..\\Resources\\Texture\\Monster\\Pinkbean\\PinkBean\\attack2_effect.png"));
		m_vecResource.push_back(std::make_pair(L"PinkBean_attack3", L"..\\Resources\\Texture\\Monster\\Pinkbean\\PinkBean\\attack3_effect.png"));
		m_vecResource.push_back(std::make_pair(L"miniBean", L"..\\Resources\\Texture\\Monster\\Pinkbean\\PinkBean\\minibean.png"));
		m_vecResource.push_back(std::make_pair(L"SolomonTex", L"..\\Resources\\Texture\\Monster\\Pinkbean\\Solomon\\Solomon.png"));
		m_vecResource.push_back(std::make_pair(L"Solomon_attack1", L"..\\Resources\\Texture\\Monster\\Pinkbean\\Solomon\\attack1_hit.png"));

		m_vecResource.push_back(std::make_pair(L"RexTex", L"..\\Resources\\Texture\\Monster\\Pinkbean\\Rex\\Rex.png"));
		m_vecResource.push_back(std::make_pair(L"Rex_attack1", L"..\\Resources\\Texture\\Monster\\Pinkbean\\Rex\\attack1_hit.png"));
		m_vecResource.push_back(std::make_pair(L"MuninTex", L"..\\Resources\\Texture\\Monster\\Pinkbean\\Munin\\Munin.png"));
		m_vecResource.push_back(std::make_pair(L"MuninStoneTex", L"..\\Resources\\Texture\\Monster\\PinkBean\\Munin\\attack1_effect.png"));
		m_vecResource.push_back(std::make_pair(L"WhigginTex", L"..\\Resources\\Texture\\Monster\\Pinkbean\\Whiggin\\Whiggin.png"));

		m_vecResource.push_back(std::make_pair(L"ArielTex", L"..\\Resources\\Texture\\Monster\\Pinkbean\\Ariel\\Ariel.png"));
		m_vecResource.push_back(std::make_pair(L"Ariel_attack0", L"..\\Resources\\Texture\\Monster\\Pinkbean\\Ariel\\attack0_effect.png"));
		m_vecResource.push_back(std::make_pair(L"Ariel_attack1", L"..\\Resources\\Texture\\Monster\\Pinkbean\\Ariel\\attack1_effect.png"));
		
		m_vecResource.push_back(std::make_pair(L"PinkBean_attack0_hit", L"..\\Resources\\Texture\\Monster\\PinkBean\\PinkBean\\attack0_hit.png"));
		m_vecResource.push_back(std::make_pair(L"PinkBean_attack1_hit", L"..\\Resources\\Texture\\Monster\\PinkBean\\PinkBean\\attack1_hit.png"));
		m_vecResource.push_back(std::make_pair(L"PinkBean_attack2_hit", L"..\\Resources\\Texture\\Monster\\Pinkbean\\PinkBean\\attack2_hit.png"));
		m_vecResource.push_back(std::make_pair(L"PinkBean_attack3_hit", L"..\\Resources\\Texture\\Monster\\Pinkbean\\PinkBean\\attack3_hit.png"));
		m_vecResource.push_back(std::make_pair(L"MiniBean_attack0_hit", L"..\\Resources\\Texture\\Monster\\PinkBean\\PinkBean\\minibean_attack0_hit.png"));
		m_vecResource.push_back(std::make_pair(L"Solomon_attack0_hit", L"..\\Resources\\Texture\\Monster\\Pinkbean\\Solomon\\attack0_hit.png"));
		m_vecResource.push_back(std::make_pair(L"Solomon_attack2_hit", L"..\\Resources\\Texture\\Monster\\Pinkbean\\Solomon\\attack2_hit.png"));
		m_vecResource.push_back(std::make_pair(L"Rex_attack0_hit", L"..\\Resources\\Texture\\Monster\\Pinkbean\\Rex\\attack0_hit.png"));
		m_vecResource.push_back(std::make_pair(L"Rex_attack2_hit", L"..\\Resources\\Texture\\Monster\\Pinkbean\\Rex\\attack2_hit.png"));
		m_vecResource.push_back(std::make_pair(L"Munin_attack0_hit", L"..\\Resources\\Texture\\Monster\\Pinkbean\\Munin\\attack0_hit.png"));
		m_vecResource.push_back(std::make_pair(L"Munin_attack1_hit", L"..\\Resources\\Texture\\Monster\\Pinkbean\\Munin\\attack1_hit.png"));
		m_vecResource.push_back(std::make_pair(L"Whiggin_attack0_hit", L"..\\Resources\\Texture\\Monster\\Pinkbean\\Whiggin\\attack0_hit.png"));

	}
	TempleBossScene::~TempleBossScene()
	{

	}
	void TempleBossScene::Initialize()
	{
		CreateBackground();
		add_objectpool();

		{
			GameObject* pCamera = new GameObject();
			pCamera->SetName(L"ObjCam");
			pCamera->SetObjectID(0);
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
			pUICamera->SetObjectID(1);
			AddGameObject(eLayerType::Camera, pUICamera);
			pUICamera->GetComponent<Transform>()->SetPosition(Vector3(0.f, 0.f, -10.f));
			Camera* pCameraComp = pUICamera->AddComponent<Camera>();
			pCameraComp->TurnUILayerMask();//UI만 그리게
			//pCamera->AddComponent<CameraScript>();
		}
	}
	void TempleBossScene::Update()
	{
		Scene::Update();
	}
	void TempleBossScene::LateUpdate()
	{
		Scene::LateUpdate();
	}
	void TempleBossScene::Render()
	{
		Scene::Render();
	}
	void TempleBossScene::OnEnter()
	{
		Scene::OnEnter();
		
	}
	void TempleBossScene::OnExit()
	{
		Scene::OnExit();
	
	}
	void TempleBossScene::CreateBackground()
	{
		GameObject* pBackGround = new GameObject();
		
		AddGameObject(eLayerType::Background, pBackGround);
		MeshRenderer* pMeshRender = pBackGround->AddComponent<MeshRenderer>();
		pMeshRender->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
		pMeshRender->SetMaterial(Resources::Find<Material>(L"TempleBossMater"));
		pBackGround->GetComponent<Transform>()->SetPosition(0.f, 0.f, 0.f);
		//2 : 1
		pBackGround->GetComponent<Transform>()->SetScale(2.f * 8.f, 1.f * 8.f, 1.f);

	}
	void TempleBossScene::SendEnter()
	{
		mapping_resource();

		Scene::SendEnter();
	}

	void TempleBossScene::StartSound()
	{
	
	}

	void TempleBossScene::EndSound()
	{
	}

	void TempleBossScene::add_objectpool()
	{
		PinkBean* pPinkBean = new PinkBean();
		ObjectPoolManager::AddObjectPool(pPinkBean->GetName(), pPinkBean);

		Ariel* pAriel = new Ariel();
		ObjectPoolManager::AddObjectPool(pAriel->GetName(), pAriel);

		Whiggin* pWhiggin = new Whiggin();
		ObjectPoolManager::AddObjectPool(pWhiggin->GetName(), pWhiggin);

		Munin* pMunin = new Munin();
		ObjectPoolManager::AddObjectPool(pMunin->GetName(), pMunin);

		Solomon* pSolomon = new Solomon();
		ObjectPoolManager::AddObjectPool(pSolomon->GetName(), pSolomon);

		Rex* pRex = new Rex();
		ObjectPoolManager::AddObjectPool(pRex->GetName(), pRex);
	
	
		Effect* pEffect = nullptr;
		for (int i = 0; i < 5; ++i)
		{
			pEffect = new Effect();
			pEffect->CreateAnimation(nullptr, L"PinkBean_attack0_hit", Vector2(0.f, 0.f), Vector2(97.f, 107.f), 7, 1, Vector2(120.f, 120.f), Vector2(0.f, 0.2f), Vector2(582.f, 107.f));
			ObjectPoolManager::AddObjectPool(pEffect->GetName(), pEffect);
		}
		for (int i = 0; i < 5; ++i)
		{
			pEffect = new Effect();
			pEffect->CreateAnimation(nullptr, L"PinkBean_attack1_hit", Vector2(0.f, 0.f), Vector2(124.f, 112.f), 5, 1, Vector2(120.f, 120.f), Vector2(0.f, 0.2f), Vector2(620.f, 112.f));
			ObjectPoolManager::AddObjectPool(pEffect->GetName(), pEffect);
		}
		for (int i = 0; i < 5; ++i)
		{
			pEffect = new Effect();
			pEffect->CreateAnimation(nullptr, L"PinkBean_attack2_hit", Vector2(0.f, 0.f), Vector2(112.f, 110.f), 6, 1, Vector2(120.f, 120.f), Vector2(0.f, 0.2f), Vector2(672.f, 110.f));
			ObjectPoolManager::AddObjectPool(pEffect->GetName(), pEffect);
		}
		for (int i = 0; i < 5; ++i)
		{
			pEffect = new Effect();
			pEffect->CreateAnimation(nullptr, L"PinkBean_attack3_hit", Vector2(0.f, 0.f), Vector2(88.f, 87.f), 4, 1, Vector2(120.f, 120.f), Vector2(0.f, 0.2f), Vector2(352.f, 87.f));
			ObjectPoolManager::AddObjectPool(pEffect->GetName(), pEffect);
		}
		for (int i = 0; i < 5; ++i)
		{
			pEffect = new Effect();
			pEffect->CreateAnimation(nullptr, L"MiniBean_attack0_hit", Vector2(0.f, 0.f), Vector2(97.f, 107.f), 7, 1, Vector2(120.f, 120.f), Vector2(0.f, 0.2f), Vector2(470.f, 89.f));
			ObjectPoolManager::AddObjectPool(pEffect->GetName(), pEffect);
		}
		for (int i = 0; i < 5; ++i)
		{
			pEffect = new Effect();
			pEffect->CreateAnimation(nullptr, L"Solomon_attack0_hit", Vector2(0.f, 0.f), Vector2(131.f, 128.f), 7, 1, Vector2(120.f, 120.f), Vector2(0.f, 0.2f), Vector2(917.f, 128.f));
			ObjectPoolManager::AddObjectPool(pEffect->GetName(), pEffect);
		}
		for (int i = 0; i < 5; ++i)
		{
			pEffect = new Effect();
			pEffect->CreateAnimation(nullptr, L"Solomon_attack2_hit", Vector2(0.f, 0.f), Vector2(217.f, 163.f), 8, 1, Vector2(200.f, 200.f), Vector2::Zero, Vector2(1736.f, 163.f));
			ObjectPoolManager::AddObjectPool(pEffect->GetName(), pEffect);
		}
		for (int i = 0; i < 5; ++i)
		{
			pEffect = new Effect();
			pEffect->CreateAnimation(nullptr, L"Rex_attack0_hit", Vector2(0.f, 0.f), Vector2(129.f, 128.f), 7, 1, Vector2(120.f, 120.f), Vector2(0.f, 0.2f), Vector2(903.f, 128.f));
			ObjectPoolManager::AddObjectPool(pEffect->GetName(), pEffect);
		}
		for (int i = 0; i < 5; ++i)
		{
			pEffect = new Effect();
			pEffect->CreateAnimation(nullptr, L"Rex_attack2_hit", Vector2(0.f, 0.f), Vector2(219.f, 163.f), 8, 1, Vector2(200.f, 200.f), Vector2::Zero, Vector2(1752.f, 165.f));
			ObjectPoolManager::AddObjectPool(pEffect->GetName(), pEffect);
		}
		for (int i = 0; i < 5; ++i)
		{
			pEffect = new Effect();
			pEffect->CreateAnimation(nullptr, L"Munin_attack0_hit", Vector2(0.f, 0.f), Vector2(117.f, 156.f), 5, 1, Vector2(150.f, 150.f), Vector2(0.f, 0.2f), Vector2(585.f, 156.f));
			ObjectPoolManager::AddObjectPool(pEffect->GetName(), pEffect);
		}
		//*2
		for (int i = 0; i < 5; ++i)
		{
			pEffect = new Effect();
			pEffect->CreateAnimation(nullptr, L"Munin_attack1_hit", Vector2(0.f, 0.f), Vector2(109.f, 104.f), 8, 1, Vector2(200.f, 200.f), Vector2::Zero, Vector2(763.f, 104.f));
			ObjectPoolManager::AddObjectPool(pEffect->GetName(), pEffect);
		}
		for (int i = 0; i < 5; ++i)
		{
			pEffect = new Effect();
			pEffect->CreateAnimation(nullptr, L"Whiggin_attack0_hit", Vector2(0.f, 0.f), Vector2(117.f, 156.f), 5, 1, Vector2(150.f, 150.f), Vector2(0.f, 0.2f), Vector2(585.f, 156.f));
			ObjectPoolManager::AddObjectPool(pEffect->GetName(), pEffect);
		}
		for (int i = 0; i < 5; ++i)
		{
			pEffect = new Effect();
			pEffect->CreateAnimation(nullptr, L"Whiggin_attack1_hit", Vector2(0.f, 0.f), Vector2(109.f, 104.f), 8, 1, Vector2(200.f, 200.f), Vector2::Zero, Vector2(763.f, 104.f));
			ObjectPoolManager::AddObjectPool(pEffect->GetName(), pEffect);
		}
	}

	void TempleBossScene::mapping_resource()
	{
		mapping_texture(L"PinkBean_attack0_hit", L"PinkBean_attack0_hit");
		mapping_texture(L"PinkBean_attack1_hit", L"PinkBean_attack1_hit");
		mapping_texture(L"PinkBean_attack2_hit", L"PinkBean_attack2_hit");
		mapping_texture(L"PinkBean_attack3_hit", L"PinkBean_attack3_hit");
		mapping_texture(L"MiniBean_attack0_hit", L"MiniBean_attack0_hit");
		mapping_texture(L"Solomon_attack0_hit", L"Solomon_attack0_hit");
		mapping_texture(L"Solomon_attack2_hit", L"Solomon_attack2_hit");
		mapping_texture(L"Rex_attack0_hit", L"Rex_attack0_hit");
		mapping_texture(L"Rex_attack2_hit", L"Rex_attack2_hit");
		mapping_texture(L"Munin_attack0_hit", L"Munin_attack0_hit");
		mapping_texture(L"Munin_attack1_hit", L"Munin_attack1_hit");
		mapping_texture(L"Whiggin_attack0_hit", L"Whiggin_attack0_hit");
		mapping_texture(L"Munin_attack1_hit", L"Whiggin_attack1_hit");
	}

	void TempleBossScene::create_monster()
	{
		
	}

}