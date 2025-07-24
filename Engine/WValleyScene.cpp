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

#include "WRenderer.h"
#include "WGround.h"
#include "WTexture.h"
#include "WSkelegon.h"

#include "WBossUI.h"
#include "WAudioClip.h"
#include "WAudioSource.h"
#include "WObjectPoolManager.h"
#include "WResources.h"
#include "WEffect.h"
#include "WThreadPool.h"
#include "WAnimator.h"
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

		SetMapSize(0.f, 7.f, 0.f, -7.f);
		SetMapPossibleSize(-4.37f, 4.37f);

		//리소스
		m_vecResource.push_back(std::make_pair(L"SkelegonTex", L"..\\Resources\\Texture\\Monster\\skelegon.png"));
		m_vecResource.push_back(std::make_pair(L"SklaserEffect", L"..\\Resources\\Texture\\Monster\\attack1_hit.png"));

		m_vecSoundResource.push_back(std::make_pair(L"valleysound", L"..\\Resources\\sound\\DragonNest.mp3"));
	}
	ValleyScene::~ValleyScene()
	{

	}
	void ValleyScene::Initialize()
	{
	
		CreateBackground();
		setobject();
		add_objectpool();

		InterfaceUI* pInterUI = new InterfaceUI();
		pInterUI->SetObjectID(0);
		pInterUI->SetName(L"Interface");
		AddGameObject(eLayerType::UI, pInterUI);
		pInterUI->Initialize();

		BossUI* pBossUI = new BossUI();
		pBossUI->SetObjectID(3);
		pBossUI->SetName(L"Boss");
		AddGameObject(eLayerType::UI, pBossUI);
		pBossUI->Initialize();

		{
			GameObject* pCamera = new GameObject();
			pCamera->SetName(L"ObjCam");
			pCamera->SetObjectID(0);
			AddGameObject(eLayerType::Camera, pCamera);
			pCamera->GetComponent<Transform>()->SetPosition(Vector3(0.f, 0.f, -10.f));
			Camera* pCameraComp = pCamera->AddComponent<Camera>();
			pCameraComp->TurnLayerMask(eLayerType::UI, false);
			CameraScript* pCameraScript = pCamera->AddComponent<CameraScript>();
			renderer::MainCamera = pCameraComp;
			//pCameraScript->SetPlayer(pPlayer);
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
			renderer::UICamera = pCameraComp;
		}
	}
	void ValleyScene::Update()
	{
		Scene::Update();
	}
	void ValleyScene::LateUpdate()
	{
		Scene::LateUpdate();
	}
	void ValleyScene::Render()
	{
		Scene::Render();
	}

	void ValleyScene::SendEnter()
	{
		mapping_resource();

		Protocol::C_START_MAP pkt;
		
		UINT iSceneID = GetSceneID();
		pkt.set_scene_player_id((iSceneID<<16) | PLAYER_ID);
		
		SceneManger::StartWaitForMapData();
		
		shared_ptr<SendBuffer> pSendBuffer = ServerPacketHandler::MakeSendBuffer(pkt);
		GClientService->GetClientSession()->Send(pSendBuffer);

		Scene::StartSound();
	}

	void ValleyScene::OnEnter()
	{
		Scene::OnEnter();
	}
	void ValleyScene::OnExit()
	{
		Scene::OnExit();
	}
	void ValleyScene::CreateBackground()
	{
		GameObject* pBackGround = new GameObject();
		pBackGround->SetClientObject(true);

		AddGameObject(eLayerType::Background, pBackGround);
		MeshRenderer* pMeshRender = pBackGround->AddComponent<MeshRenderer>();
		pMeshRender->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
		pMeshRender->SetMaterial(Resources::Find<Material>(L"dragonValleyMater"));
		pBackGround->GetComponent<Transform>()->SetPosition(0.f, 0.f, 5.f);
		//035 : 1
		pBackGround->GetComponent<Transform>()->SetScale(25 * 0.35f,  25.f * 1.f, 1.f);
	}

	void ValleyScene::add_objectpool()
	{
		Skelegon* pSkelegon = new Skelegon();
		ObjectPoolManager::AddObjectPool(pSkelegon->GetName(), pSkelegon);

		Effect* pEffect = new Effect();
		pEffect->CreateAnimation(nullptr, L"sklaser_hit", Vector2(0.f, 0.f), Vector2(134.f, 97.f), 1, 1, Vector2(100.f, 100.f), Vector2::Zero, Vector2(134.f, 97.f),0.2f);
		ObjectPoolManager::AddObjectPool(pEffect->GetName(), pEffect);

		MonsterAttackObject* pLaser = new MonsterAttackObject();
		pLaser->SetName(L"sklaser");
		ObjectPoolManager::AddObjectPool(pLaser->GetName(), pLaser);
	}

	void ValleyScene::mapping_resource()
	{
		mapping_texture(L"SklaserEffect", L"sklaser_hit");
	}

	void ValleyScene::setobject()
	{
		Ladder* pLadder0 = new Ladder();
		MeshRenderer* pLadderMeshRender0 = pLadder0->AddComponent<MeshRenderer>();
		pLadderMeshRender0->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
		pLadderMeshRender0->SetMaterial(Resources::Find<Material>(L"LadderBaseMater9_"));
		pLadder0->GetComponent<Transform>()->SetPosition(0.f, -4.4f, -0.1f);
		pLadder0->GetComponent<Transform>()->SetScale(1.f * 0.6f, 5.5f * 0.6f, 0.f);
		pLadder0->Initialize();
		AddGameObject(eLayerType::Ladder, pLadder0);

		Ladder* pLadder1 = new Ladder();
		pLadder1->SetObjectID(1);
		MeshRenderer* pLadderMeshRender1 = pLadder1->AddComponent<MeshRenderer>();
		pLadderMeshRender1->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
		pLadderMeshRender1->SetMaterial(Resources::Find<Material>(L"LadderBaseMater9_"));
		pLadder1->GetComponent<Transform>()->SetPosition(2.f, 4.2f, -0.1f);
		pLadder1->GetComponent<Transform>()->SetScale(1.f * 0.6f, 5.6f * 0.6f, 0.f);
		pLadder1->Initialize();
		AddGameObject(eLayerType::Ladder, pLadder1);

		Ladder* pLadder2 = new Ladder();
		pLadder2->SetObjectID(2);
		MeshRenderer* pLadderMeshRender2 = pLadder2->AddComponent<MeshRenderer>();
		pLadderMeshRender2->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
		pLadderMeshRender2->SetMaterial(Resources::Find<Material>(L"LadderBaseMater9"));
		pLadder2->GetComponent<Transform>()->SetPosition(-1.f, -0.7f, -0.1f);
		pLadder2->GetComponent<Transform>()->SetScale(1.f * 0.6f, 4.5f * 0.6f, 0.f);
		pLadder2->Initialize();
		AddGameObject(eLayerType::Ladder, pLadder2);
	}
	
}
