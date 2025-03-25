#include "WValleyScene.h"
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
#include "WLadder.h"
#include "WNPC.h"
#include "WCage.h"
#include "WInterfaceUI.h"
#include "WEquipState.h"
#include "WAlixirUI.h"
#include "WPlayer.h"
#include "WObject.h"
#include "WRenderer.h"
#include "WGround.h"
#include "WCollisionManager.h"
#include "WTexture.h"
#include "WSkelegon.h"
#include "WPortal.h"
#include "WPortalScript.h"
#include "WBossUI.h"
#include "WAudioClip.h"
#include "WAudioSource.h"
namespace W
{
	ValleyScene::ValleyScene()
	{
		std::shared_ptr<Texture> pValleyTex =
			Resources::Load<Texture>(L"dragonValleyTex", L"..\\Resources\\Texture\\background\\dragonValley.png");
		std::shared_ptr<Material> pValleyMater = std::make_shared<Material>();
		pValleyMater->SetShader(Resources::Find<Shader>(L"BackgroundShader"));
		pValleyMater->SetTexture(pValleyTex);
		//pValleyMater->SetRenderinMode(eRenderingMode::Transparent);
		Resources::Insert(L"dragonValleyMater", pValleyMater);


		//npc
		std::shared_ptr<Texture> pNPCTex =
			Resources::Load<Texture>(L"NPCTex1", L"..\\Resources\\Texture\\NPC\\npc1.png");

		std::shared_ptr<Material> pNPCMater = std::make_shared<Material>();
		pNPCMater->SetShader(Resources::Find<Shader>(L"ObjectShader"));
		pNPCMater->SetTexture(pNPCTex);
		Resources::Insert(L"NPCMater1", pNPCMater);

		SetMapSize(0.f, 7.f, 0.f, -7.f);
		SetMapPossibleSize(-4.37f, 4.37f);
	}
	ValleyScene::~ValleyScene()
	{

	}
	void ValleyScene::Initialize()
	{
		CreateBackground();
		setobject();
		setmonster();

		Player* pPlayer = new Player();
		AddGameObject(eLayerType::Player, pPlayer);
		pPlayer->Initialize();


		NPC* pNPC = new NPC();
	 	MeshRenderer* pMeshRenderer = pNPC->AddComponent<MeshRenderer>();
		AddGameObject(eLayerType::NPC, pNPC);
		pMeshRenderer->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
		pMeshRenderer->SetMaterial(Resources::Find<Material>(L"NPCMater1"));
		pNPC->GetComponent<Transform>()->SetPosition(2.5f, 7.5f, -0.2f);
		pNPC->GetComponent<Transform>()->SetScale(0.761f, 1.f, 0.f);
		//0.761 : 1
	
		EquipState* pEquipState = new EquipState();
		SceneManger::AddGameObject(eLayerType::UI, pEquipState);
		pEquipState->SetPlayer(pPlayer);
		pEquipState->Initialize();

		InterfaceUI* pInterUI = new InterfaceUI();
		AddGameObject(eLayerType::UI, pInterUI);
		pInterUI->Initialize();

		BossUI* pBossUI = new BossUI();
		AddGameObject(eLayerType::UI, pBossUI);
		pBossUI->Initialize();

		//AlixirUI* pTest = new AlixirUI();
		//AddGameObject(eLayerType::UI, pTest);
		//pTest->GetComponent<Transform>()->SetPosition(0.f, 0.f, -0.22f);
		//pTest->GetComponent<Transform>()->SetScale(0.1f *2.5f, 0.1f*2.5f , 0.f); //1 : 1

		{
			GameObject* pCamera = new GameObject();
			pCamera->SetName(L"ObjCam");
			AddGameObject(eLayerType::Camera, pCamera);
			pCamera->GetComponent<Transform>()->SetPosition(Vector3(0.f, 0.f, -10.f));
			Camera* pCameraComp = pCamera->AddComponent<Camera>();
			pCameraComp->TurnLayerMask(eLayerType::UI, false);
			CameraScript* pCameraScript = pCamera->AddComponent<CameraScript>();
			renderer::MainCamera = pCameraComp;
			pCameraScript->SetPlayer(pPlayer);
		}

		//ui camera
		{
			GameObject* pUICamera = new GameObject();
			pUICamera->SetName(L"UICam");
			AddGameObject(eLayerType::Camera, pUICamera);
			pUICamera->GetComponent<Transform>()->SetPosition(Vector3(0.f, 0.f, -10.f));
			Camera* pCameraComp = pUICamera->AddComponent<Camera>();
			pCameraComp->TurnUILayerMask();//UI만 그리게
			renderer::UICamera = pCameraComp;
		}
	}
	void ValleyScene::Update()
	{
		Scene::Update();

		
		//if (Input::GetKeyDown(eKeyCode::SPACE))
		//{
		//	SceneManger::LoadScene(L"Cave");
		//}

	}
	void ValleyScene::LateUpdate()
	{
		Scene::LateUpdate();
	}
	void ValleyScene::Render()
	{
		Scene::Render();
	}
	void ValleyScene::OnEnter()
	{
		StartSound();

		CollisionManager::SetLayer(eLayerType::Player, eLayerType::Ground, true);
		CollisionManager::SetLayer(eLayerType::ItemObject, eLayerType::Ground, true);
		CollisionManager::SetLayer(eLayerType::ItemObject, eLayerType::Player, true);
		CollisionManager::SetLayer(eLayerType::Player, eLayerType::Ladder, true);
		CollisionManager::SetLayer(eLayerType::Monster, eLayerType::AttackObject, true);
		CollisionManager::SetLayer(eLayerType::Monster, eLayerType::Player, true);
		CollisionManager::SetLayer(eLayerType::Player, eLayerType::MonsterAttack, true);
		CollisionManager::SetLayer(eLayerType::Player, eLayerType::Portal, true);

	}
	void ValleyScene::OnExit()
	{
		EndSound();

		CollisionManager::Clear();
	}
	void ValleyScene::CreateBackground()
	{
		GameObject* pBackGround = new GameObject();
		AudioSource* pAudio = pBackGround->AddComponent<AudioSource>();
		std::shared_ptr<AudioClip> pAudioClip = Resources::Load<AudioClip>(L"valleysound", L"..\\Resources\\sound\\DragonNest.mp3");
		pAudioClip->SetLoop(true);
		pAudio->SetClip(pAudioClip);

		AddGameObject(eLayerType::Background, pBackGround);
		MeshRenderer* pMeshRender = pBackGround->AddComponent<MeshRenderer>();
		pMeshRender->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
		pMeshRender->SetMaterial(Resources::Find<Material>(L"dragonValleyMater"));
		pBackGround->GetComponent<Transform>()->SetPosition(0.f, 0.f, 0.2f);
		//035 : 1
		pBackGround->GetComponent<Transform>()->SetScale(25 * 0.35f,  25.f * 1.f, 1.f);
	}

	void ValleyScene::StartSound()
	{
		const std::vector<GameObject*> m_vecBackGround = GetLayer(eLayerType::Background).GetGameObjects();
		AudioSource* pAudio = m_vecBackGround[0]->GetComponent<AudioSource>();
		pAudio->Play();
	}

	void ValleyScene::EndSound()
	{
		const std::vector<GameObject*> m_vecBackGround = GetLayer(eLayerType::Background).GetGameObjects();
		AudioSource* pAudio = m_vecBackGround[0]->GetComponent<AudioSource>();
		pAudio->Stop();
	}

	void ValleyScene::setobject()
	{
		Cage* pCage = new Cage();
		AddGameObject(eLayerType::Box, pCage);
		
		pCage->GetComponent<Transform>()->SetPosition(2.5f, 7.57f, -0.3f);
		pCage->GetComponent<Transform>()->SetScale(0.641f * 2.2f, 1.f * 2.2f, 0.f);
		//0.641 : 1

		Ladder* pLadder0 = new Ladder();
		AddGameObject(eLayerType::Ladder, pLadder0);
		MeshRenderer* pLadderMeshRender0 = pLadder0->AddComponent<MeshRenderer>();
		pLadderMeshRender0->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
		pLadderMeshRender0->SetMaterial(Resources::Find<Material>(L"LadderBaseMater9_"));
		pLadder0->GetComponent<Transform>()->SetPosition(0.f, -4.4f, -0.1f);
		pLadder0->GetComponent<Transform>()->SetScale(1.f * 0.6f, 5.5f * 0.6f, 0.f);
		pLadder0->Initialize();
		pLadder0->GetComponent<Collider2D>()->SetCenter(Vector2(0.f, -0.1f));
	

		Ladder* pLadder1 = new Ladder();
		AddGameObject(eLayerType::Ladder, pLadder1);
		MeshRenderer* pLadderMeshRender1 = pLadder1->AddComponent<MeshRenderer>();
		pLadderMeshRender1->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
		pLadderMeshRender1->SetMaterial(Resources::Find<Material>(L"LadderBaseMater9_"));
		pLadder1->GetComponent<Transform>()->SetPosition(2.f, 4.2f, -0.1f);
		pLadder1->GetComponent<Transform>()->SetScale(1.f * 0.6f, 5.6f * 0.6f, 0.f);
		pLadder1->Initialize();

		Ladder* pLadder2 = new Ladder();
		AddGameObject(eLayerType::Ladder, pLadder2);
		MeshRenderer* pLadderMeshRender2 = pLadder2->AddComponent<MeshRenderer>();
		pLadderMeshRender2->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
		pLadderMeshRender2->SetMaterial(Resources::Find<Material>(L"LadderBaseMater9"));
		pLadder2->GetComponent<Transform>()->SetPosition(-1.f, -0.7f, -0.1f);
		pLadder2->GetComponent<Transform>()->SetScale(1.f * 0.6f, 4.5f * 0.6f, 0.f);
		pLadder2->Initialize();

		Ground* pGround1 = new Ground();
		AddGameObject(eLayerType::Ground, pGround1);
		pGround1->GetComponent<Transform>()->SetPosition(0.f, 0.48f, -0.1f);
		pGround1->GetComponent<Transform>()->SetScale(2.7f * 5.f, 1.f * 0.3f, 0.f);


		Ground* pGround2 = new Ground();
		AddGameObject(eLayerType::Ground, pGround2);
		pGround2->GetComponent<Transform>()->SetPosition(-0.6f, -3.f, -0.1f);
		pGround2->GetComponent<Transform>()->SetScale(2.7f * 1.5f, 1.f * 0.3f, 0.f);

		Ground* pGround3 = new Ground(true);
		AddGameObject(eLayerType::Ground, pGround3);
		pGround3->GetComponent<Transform>()->SetPosition(0.f, -7.6f, -0.1f);
		pGround3->GetComponent<Transform>()->SetScale(2.7f * 5.f, 1.f * 0.3f, 0.f);

		Portal* pPortal = new Portal();
		AddGameObject(eLayerType::Portal, pPortal);
		//pPortal->GetScript<PortalScript>()->SetNextScene(L"Helisium");
		pPortal->GetScript<PortalScript>()->SetNextScene(L"DemianScene");
		//pPortal->GetScript<PortalScript>()->SetNextScene(L"Cave");
		pPortal->GetComponent<Transform>()->SetPosition(3.6f, -6.8f, -0.1f);

		Portal* pPortal2 = new Portal();
		AddGameObject(eLayerType::Portal, pPortal2);
		pPortal2->GetScript<PortalScript>()->SetNextScene(L"TempleBoss");
		pPortal2->GetComponent<Transform>()->SetPosition(-3.6f, -6.8f, -0.1f);


	}
	void ValleyScene::setmonster()
	{
		Skelegon* pSkelegon = object::Instantiate<Skelegon>(Vector3(3.f, 1.2f, -1.5f), eLayerType::Monster);
		pSkelegon->Initialize();
		//Light* lightComp = pSkelegon->AddComponent<Light>();
		//lightComp->SetType(eLightType::FadeOut);
		//lightComp->SetColor(Vector4(0.8f, 0.8f, 0.8f, 0.0f));
		//lightComp->SetRadius(2.0f);

	}
}
