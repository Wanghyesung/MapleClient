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
#include "WCollisionManager.h"
#include "WRex.h"
#include "WMunin.h"
#include "WAriel.h"
#include "WPinkBean.h"
#include "WWhiggin.h"
#include "WThreadPool.h"
#include "WMonsterManager.h"
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
	}
	TempleBossScene::~TempleBossScene()
	{

	}
	void TempleBossScene::Initialize()
	{
		CreateBackground();
		create_effect();


		NPC* pNPC = new NPC();
		AddGameObject(eLayerType::NPC, pNPC);
		MeshRenderer* pMeshRender = pNPC->AddComponent<MeshRenderer>();
		pMeshRender->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
		pMeshRender->SetMaterial(Resources::Find<Material>(L"NPCMater5"));
		pNPC->GetComponent<Transform>()->SetPosition(-7.f, -2.f, -1.f);
		pNPC->GetComponent<Transform>()->SetScale(0.547f * 1.2, 1.f * 1.2f, 0.f);
		pNPC->GetComponent<Transform>()->SetRotation(0.f, 0.f, 0.f);


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
		ThreadPool::Joinable();

		create_monster();

		StartSound();

		CollisionManager::SetLayer(eLayerType::Player, eLayerType::Ground, true);
		CollisionManager::SetLayer(eLayerType::ItemObject, eLayerType::Ground, true);
		CollisionManager::SetLayer(eLayerType::ItemObject, eLayerType::Player, true);
		CollisionManager::SetLayer(eLayerType::Player, eLayerType::Ladder, true);
		CollisionManager::SetLayer(eLayerType::Monster, eLayerType::AttackObject, true);
		CollisionManager::SetLayer(eLayerType::Player, eLayerType::MonsterAttack, true);
	}
	void TempleBossScene::OnExit()
	{
		Scene::OnExit();
		DeleteMonsterObject();
		MonsterManager::DeleteMonster();

		EndSound();

		CollisionManager::Clear();
	}
	void TempleBossScene::CreateBackground()
	{
		GameObject* pBackGround = new GameObject();
		AudioSource* pAudio = pBackGround->AddComponent<AudioSource>();
		pAudio->SetClip(Resources::Load<AudioClip>(L"pinkbeansound", L"..\\Resources\\sound\\FightingPinkBeen.mp3"));

		AddGameObject(eLayerType::Background, pBackGround);
		MeshRenderer* pMeshRender = pBackGround->AddComponent<MeshRenderer>();
		pMeshRender->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
		pMeshRender->SetMaterial(Resources::Find<Material>(L"TempleBossMater"));
		pBackGround->GetComponent<Transform>()->SetPosition(0.f, 0.f, 0.f);
		//2 : 1
		pBackGround->GetComponent<Transform>()->SetScale(2.f * 8.f, 1.f * 8.f, 1.f);


		Ground* pGround = new Ground(true);
		AddGameObject(eLayerType::Ground, pGround);
		pGround->GetComponent<Transform>()->SetPosition(0.f, -2.75f, -0.1f);
		pGround->GetComponent<Transform>()->SetScale(2.7f * 7.f, 1.f * 0.3f, 0.f);
	}

	void TempleBossScene::StartSound()
	{
		const std::vector<GameObject*> m_vecBackGround = GetLayer(eLayerType::Background).GetGameObjects();
		AudioSource* pAudio = m_vecBackGround[0]->GetComponent<AudioSource>();
		pAudio->SetLoop(true);
		pAudio->Play();
	}

	void TempleBossScene::EndSound()
	{
		const std::vector<GameObject*> m_vecBackGround = GetLayer(eLayerType::Background).GetGameObjects();
		AudioSource* pAudio = m_vecBackGround[0]->GetComponent<AudioSource>();
		pAudio->Stop();
	}

	void TempleBossScene::create_monster()
	{
		PinkBean* pPinkBean = new PinkBean();
		pPinkBean->Initialize();
		AddGameObject(eLayerType::Monster, pPinkBean);
	}

	void TempleBossScene::create_effect()
	{
		std::shared_ptr<Texture> pTex =
			 Resources::Load<Texture>(L"PinkBean_attack0_hit", L"..\\Resources\\Texture\\Monster\\PinkBean\\PinkBean\\attack0_hit.png");
		Effect* pEffect = new Effect();
		pEffect->SetName(L"PinkBean_attack0");
		pEffect->CreateAnimation(pTex, Vector2(0.f, 0.f), Vector2(97.f, 107.f), 7, 1, Vector2(120.f, 120.f), Vector2(0.f, 0.2f), 0.2f);

		pTex = Resources::Load<Texture>(L"PinkBean_attack1_hit", L"..\\Resources\\Texture\\Monster\\PinkBean\\PinkBean\\attack1_hit.png");
		pEffect = new Effect();
		pEffect->SetName(L"PinkBean_attack1");
		pEffect->CreateAnimation(pTex, Vector2(0.f, 0.f), Vector2(124.f, 112.f), 5, 1, Vector2(120.f, 120.f), Vector2(0.f, 0.2f), 0.2f);

		
		pTex = Resources::Load<Texture>(L"PinkBean_attack2_hit", L"..\\Resources\\Texture\\Monster\\Pinkbean\\PinkBean\\attack2_hit.png");
		pEffect = new Effect();
		pEffect->SetName(L"PinkBean_attack2");
		pEffect->CreateAnimation(pTex, Vector2(0.f, 0.f), Vector2(112.f, 110.f), 6, 1, Vector2(120.f, 120.f), Vector2(0.f, 0.2f), 0.2f);

		pTex = Resources::Load<Texture>(L"PinkBean_attack3_hit", L"..\\Resources\\Texture\\Monster\\Pinkbean\\PinkBean\\attack3_hit.png");
		pEffect = new Effect();
		pEffect->SetName(L"PinkBean_attack3");
		pEffect->CreateAnimation(pTex, Vector2(0.f, 0.f), Vector2(88.f, 87.f), 4, 1, Vector2(120.f, 120.f), Vector2(0.f, 0.2f), 0.2f);

		
		pTex = Resources::Load<Texture>(L"MiniBean_attack0", L"..\\Resources\\Texture\\Monster\\PinkBean\\PinkBean\\minibean_attack0_hit.png");
		pEffect = new Effect();
		pEffect->SetName(L"MiniBean_attack0");
		pEffect->CreateAnimation(pTex, Vector2(0.f, 0.f), Vector2(97.f, 107.f), 7, 1, Vector2(120.f, 120.f), Vector2(0.f, 0.2f), 0.2f);


		pTex =	Resources::Load<Texture>(L"Solomon_attack0", L"..\\Resources\\Texture\\Monster\\Pinkbean\\Solomon\\attack0_hit.png");
		pEffect = new Effect();
		pEffect->SetName(L"Solomon_attack0");
		pEffect->CreateAnimation(pTex, Vector2(0.f, 0.f), Vector2(131.f, 128.f), 7, 1, Vector2(120.f, 120.f), Vector2(0.f,0.2f), 0.2f);

		pTex = Resources::Load<Texture>(L"Solomon_attack2", L"..\\Resources\\Texture\\Monster\\Pinkbean\\Solomon\\attack2_hit.png");
		pEffect = new Effect();
		pEffect->SetName(L"Solomon_attack2");
		pEffect->CreateAnimation(pTex, Vector2(0.f, 0.f), Vector2(217.f, 163.f), 8, 1, Vector2(200.f, 200.f), Vector2::Zero, 0.1f);

		pTex = Resources::Load<Texture>(L"Rex_attack0", L"..\\Resources\\Texture\\Monster\\Pinkbean\\Rex\\attack0_hit.png");
		pEffect = new Effect();
		pEffect->SetName(L"Rex_attack0");
		pEffect->CreateAnimation(pTex, Vector2(0.f, 0.f), Vector2(129.f, 128.f), 7, 1, Vector2(120.f, 120.f), Vector2(0.f, 0.2f), 0.2f);

		pTex = Resources::Load<Texture>(L"Rex_attack2", L"..\\Resources\\Texture\\Monster\\Pinkbean\\Rex\\attack2_hit.png");
		pEffect = new Effect();
		pEffect->SetName(L"Rex_attack2");
		pEffect->CreateAnimation(pTex, Vector2(0.f, 0.f), Vector2(219.f, 163.f), 8, 1, Vector2(200.f, 200.f), Vector2::Zero, 0.1f);
		
		pTex = Resources::Load<Texture>(L"Munin_attack0", L"..\\Resources\\Texture\\Monster\\Pinkbean\\Munin\\attack0_hit.png");
		pEffect = new Effect();
		pEffect->SetName(L"Munin_attack0");
		pEffect->CreateAnimation(pTex, Vector2(0.f, 0.f), Vector2(117.f, 156.f), 5, 1, Vector2(150.f, 150.f), Vector2(0.f, 0.2f), 0.2f);

		pTex = Resources::Load<Texture>(L"Munin_attack1", L"..\\Resources\\Texture\\Monster\\Pinkbean\\Munin\\attack1_hit.png");
		pEffect = new Effect();
		pEffect->SetName(L"Munin_attack1");
		pEffect->CreateAnimation(pTex, Vector2(0.f, 0.f), Vector2(109.f, 104.f), 8, 1, Vector2(200.f, 200.f), Vector2::Zero, 0.1f);

		//Resources::Load<Texture>(L"Munin_attack1", L"..\\Resources\\Texture\\Monster\\Pinkbean\\Munin\\attack1_hit.png");
		pEffect = new Effect();
		pEffect->SetName(L"Whiggin_attack1");
		pEffect->CreateAnimation(pTex, Vector2(0.f, 0.f), Vector2(109.f, 104.f), 8, 1, Vector2(200.f, 200.f), Vector2::Zero, 0.1f);

		pTex = Resources::Load<Texture>(L"Whiggin_attack0", L"..\\Resources\\Texture\\Monster\\Pinkbean\\Whiggin\\attack0_hit.png");
		pEffect = new Effect();
		pEffect->SetName(L"Whiggin_attack0");
		pEffect->CreateAnimation(pTex, Vector2(0.f, 0.f), Vector2(117.f, 156.f), 5, 1, Vector2(150.f, 150.f), Vector2(0.f, 0.2f), 0.2f);

		
	
	}
}