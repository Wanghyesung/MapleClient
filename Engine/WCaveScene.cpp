#include "WCaveScene.h"
#include "WMeshRenderer.h"
#include "WResources.h"
#include "WGameObject.h"
#include "WTransform.h"
#include "WCamera.h"
#include "WCameraScript.h"

#include "WSceneManger.h"
#include "WGround.h"
#include "WRenderer.h"
#include "WStone.h"
#include "WHorntail.h"
#include "WLadder.h"
#include "WEffect.h"

#include "WHorntailHeadA.h"
#include "WHorntailHeadB.h"
#include "WHorntailHeadC.h"
#include "WHorntailLeftHand.h"
#include "WHorntailRightHand.h"
#include "WHorntailLeg.h"
#include "WHorntailTail.h"
#include "WHorntailWing.h"


namespace W
{
	CaveScene::CaveScene()
	{
		SetMapSize(0.f, 1.f, 0.f, -1.f);
		SetMapPossibleSize(-7.f, 7.f);

	
		//내가 할당할 리소스들
		m_vecResource.push_back(std::make_pair(L"StoneTex", L"..\\Resources\\Texture\\Monster\\Horntail\\stone.png"));
		m_vecResource.push_back(std::make_pair(L"HeadATex", L"..\\Resources\\Texture\\Monster\\Horntail\\headA\\headA.png"));
		m_vecResource.push_back(std::make_pair(L"HeadBTex", L"..\\Resources\\Texture\\Monster\\Horntail\\headB\\headB.png"));
		m_vecResource.push_back(std::make_pair(L"HeadCTex", L"..\\Resources\\Texture\\Monster\\Horntail\\headC\\headC.png"));
		m_vecResource.push_back(std::make_pair(L"LeftHandTex", L"..\\Resources\\Texture\\Monster\\Horntail\\LeftHand\\lefthand.png"));
		m_vecResource.push_back(std::make_pair(L"RightHandTex", L"..\\Resources\\Texture\\Monster\\Horntail\\RightHand\\RightHand.png"));
		m_vecResource.push_back(std::make_pair(L"LegTex", L"..\\Resources\\Texture\\Monster\\Horntail\\Leg\\Leg.png"));
		m_vecResource.push_back(std::make_pair(L"WingTex", L"..\\Resources\\Texture\\Monster\\Horntail\\wing\\wing.png"));
		m_vecResource.push_back(std::make_pair(L"TailTex", L"..\\Resources\\Texture\\Monster\\Horntail\\tail\\tail.png"));
		
		m_vecResource.push_back(std::make_pair(L"SpearTex", L"..\\Resources\\Texture\\Monster\\Horntail\\LeftHand\\attack0.png"));
		m_vecResource.push_back(std::make_pair(L"IceTex", L"..\\Resources\\Texture\\Monster\\Horntail\\headA\\attack1_effect.png"));
		m_vecResource.push_back(std::make_pair(L"FireTex", L"..\\Resources\\Texture\\Monster\\Horntail\\headB\\attack1_effect.png"));
		m_vecResource.push_back(std::make_pair(L"ThunderTex", L"..\\Resources\\Texture\\Monster\\Horntail\\headC\\attack2_effect.png"));
		m_vecResource.push_back(std::make_pair(L"HorntailStartTex", L"..\\Resources\\Texture\\Monster\\Horntail\\start.png"));
		m_vecResource.push_back(std::make_pair(L"HorntailDead", L"..\\Resources\\Texture\\Monster\\Horntail\\dead.png"));

		m_vecResource.push_back(std::make_pair(L"icebreathEffect", L"..\\Resources\\Texture\\Monster\\Horntail\\headA\\attack0_hit.png"));
		m_vecResource.push_back(std::make_pair(L"iceEffect", L"..\\Resources\\Texture\\Monster\\Horntail\\headA\\attack1_hit.png"));
		m_vecResource.push_back(std::make_pair(L"firebreathEffect", L"..\\Resources\\Texture\\Monster\\Horntail\\headB\\attack1_hit.png"));
		m_vecResource.push_back(std::make_pair(L"fireEffect", L"..\\Resources\\Texture\\Monster\\Horntail\\headB\\attack2_hit.png"));
		m_vecResource.push_back(std::make_pair(L"thunderbreathEffect", L"..\\Resources\\Texture\\Monster\\Horntail\\headC\\attack1_hit.png"));
		m_vecResource.push_back(std::make_pair(L"thunderEffect", L"..\\Resources\\Texture\\Monster\\Horntail\\headC\\attack2_hit.png"));
		m_vecResource.push_back(std::make_pair(L"legattack1Effect", L"..\\Resources\\Texture\\Monster\\Horntail\\Leg\\attack1_hit.png"));
		m_vecResource.push_back(std::make_pair(L"legattack2Effect", L"..\\Resources\\Texture\\Monster\\Horntail\\Leg\\attack2_hit.png"));
		m_vecResource.push_back(std::make_pair(L"tailEffect", L"..\\Resources\\Texture\\Monster\\Horntail\\tail\\attack0_hit.png"));

		m_vecSoundResource.push_back(std::make_pair(L"cavesound", L"..\\Resources\\sound\\HonTale.mp3"));
	}
	CaveScene::~CaveScene()
	{
		
	}
	void CaveScene::Initialize()
	{
		create_object();
		add_objectpool();

		CreateBackground();
		{
			GameObject* pCamera = new GameObject();
			pCamera->SetObjectID(0);
			pCamera->SetName(L"ObjCam");
			AddGameObject(eLayerType::Camera, pCamera);
			pCamera->GetComponent<Transform>()->SetPosition(Vector3(0.f, 0.f, -10.f));
			Camera* pCameraComp = pCamera->AddComponent<Camera>();
			pCameraComp->TurnLayerMask(eLayerType::UI, false);
			CameraScript* pCameraScript = pCamera->AddComponent<CameraScript>();
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
		}

	}
	void CaveScene::Update()
	{
		Scene::Update();
	}

	void CaveScene::LateUpdate()
	{
		Scene::LateUpdate();	
	}

	void CaveScene::Render()
	{
		Scene::Render();
	}
	void CaveScene::OnEnter()
	{
		Scene::OnEnter();
		
	}
	void CaveScene::OnExit()
	{
		Scene::OnExit();//리소스 해제

	}
	void CaveScene::SendEnter()
	{
		mapping_resource();

		Scene::SendEnter();
	}
	void CaveScene::CreateBackground()
	{
		GameObject* pBackGround = new GameObject();
		pBackGround->SetClientObject(true);

		pBackGround->SetObjectID(0);
		
		AddGameObject(eLayerType::Background, pBackGround);
		MeshRenderer* pMeshRender = pBackGround->AddComponent<MeshRenderer>();
		pMeshRender->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
		pMeshRender->SetMaterial(Resources::Find<Material>(L"WoodCaveMater"));
		pBackGround->GetComponent<Transform>()->SetPosition(0.f, 0.f, 5.f);
		//14::10
		pBackGround->GetComponent<Transform>()->SetScale(14.f * 1.f, 10.f * 1.f, 1.f);
		
	}
	
	void CaveScene::create_object()
	{	
		std::shared_ptr<Texture> pLadder9 = Resources::Load<Texture>(L"Ladder9BaseTex", L"..\\Resources\\Texture\\Object\\ladder\\9_base.png");
		std::shared_ptr<Texture> pLadder9_ = Resources::Load<Texture>(L"Ladder9Base_Tex", L"..\\Resources\\Texture\\Object\\ladder\\9base.png");

		std::shared_ptr<Material> pLadderMater9 = std::make_shared<Material>();
		pLadderMater9->SetShader(Resources::Find<Shader>(L"ObjectShader"));
		pLadderMater9->SetTexture(pLadder9);
		Resources::Insert(L"LadderBaseMater9", pLadderMater9);

		std::shared_ptr<Material> pLadderMater9_ = std::make_shared<Material>();
		pLadderMater9_->SetShader(Resources::Find<Shader>(L"ObjectShader"));
		pLadderMater9_->SetTexture(pLadder9_);
		Resources::Insert(L"LadderBaseMater9_", pLadderMater9_);	

		Ladder* pLadder2 = new Ladder();
		MeshRenderer* pLadderMeshRender2 = pLadder2->AddComponent<MeshRenderer>();
		pLadderMeshRender2->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
		pLadderMeshRender2->SetMaterial(Resources::Find<Material>(L"LadderBaseMater9"));
		pLadder2->GetComponent<Transform>()->SetPosition(3.5f, -2.4f, -0.1f);
		pLadder2->GetComponent<Transform>()->SetScale(1.f * 0.6f, 4.5f * 0.6f, 0.f);
		pLadder2->Initialize();
		AddGameObject(eLayerType::Ladder, pLadder2);
	}


	void CaveScene::add_objectpool()
	{
		Horntail* pHorntail = new Horntail();
		ObjectPoolManager::AddObjectPool(pHorntail->GetName(), pHorntail);

		HorntailHeadA* pHeadA = new HorntailHeadA();
		ObjectPoolManager::AddObjectPool(pHeadA->GetName(), pHeadA);

		HorntailHeadB* pHeadB = new HorntailHeadB();
		ObjectPoolManager::AddObjectPool(pHeadB->GetName(), pHeadB);

		HorntailHeadC* pHeadC = new HorntailHeadC();
		ObjectPoolManager::AddObjectPool(pHeadC->GetName(), pHeadC);

		HorntailLeftHand* pLHand = new HorntailLeftHand();
		ObjectPoolManager::AddObjectPool(pLHand->GetName(), pLHand);

		HorntailRightHand* pRHand = new HorntailRightHand();
		ObjectPoolManager::AddObjectPool(pRHand->GetName(), pRHand);

		HorntailLeg* pLeg = new HorntailLeg();
		ObjectPoolManager::AddObjectPool(pLeg->GetName(), pLeg);

		HorntailWing* pWing = new HorntailWing();
		ObjectPoolManager::AddObjectPool(pWing->GetName(), pWing);

		HorntailTail* pTail = new HorntailTail();
		ObjectPoolManager::AddObjectPool(pTail->GetName(), pTail);

		Effect* pEffect = nullptr;
		
		for (int i = 0; i < 5; ++i)
		{
			pEffect = new Effect();
			pEffect->CreateAnimation(nullptr, L"icebreath_hit", Vector2(0.f, 0.f), Vector2(110.f, 113.f), 2, 1, Vector2(100.f, 100.f), Vector2::Zero, Vector2(220.f,113.f));
			ObjectPoolManager::AddObjectPool(pEffect->GetName(), pEffect);
		}

		for (int i = 0; i < 5; ++i)
		{
			pEffect = new Effect();
			pEffect->CreateAnimation(nullptr, L"ice_hit", Vector2(0.f, 0.f), Vector2(118.f, 87.f), 2, 1, Vector2(100.f, 100.f), Vector2::Zero, Vector2(236.f, 87.f));
			ObjectPoolManager::AddObjectPool(pEffect->GetName(), pEffect);
		}

		for (int i = 0; i < 5; ++i)
		{
			pEffect = new Effect();
			pEffect->CreateAnimation(nullptr, L"firebreath_hit", Vector2(0.f, 0.f), Vector2(99.f, 107.f), 2, 1, Vector2(100.f, 100.f), Vector2::Zero, Vector2(198.f, 107.f));
			ObjectPoolManager::AddObjectPool(pEffect->GetName(), pEffect);
		}
		for (int i = 0; i < 5; ++i)
		{
			pEffect = new Effect();
			pEffect->CreateAnimation(nullptr, L"fire_hit", Vector2(0.f, 0.f), Vector2(92.f, 91.f), 4, 1, Vector2(100.f, 100.f), Vector2::Zero, Vector2(368.f, 91.f));
			ObjectPoolManager::AddObjectPool(pEffect->GetName(), pEffect);
		}
		for (int i = 0; i < 5; ++i)
		{
			pEffect = new Effect();
			pEffect->CreateAnimation(nullptr, L"thunderbreath_hit", Vector2(0.f, 0.f), Vector2(72.f, 82.f), 4, 1, Vector2(100.f, 100.f), Vector2::Zero, Vector2(288.f, 82.f));
			ObjectPoolManager::AddObjectPool(pEffect->GetName(), pEffect);
		}
		for (int i = 0; i < 5; ++i)
		{
			pEffect = new Effect();
			pEffect->CreateAnimation(nullptr, L"thunder_hit", Vector2(0.f, 0.f), Vector2(78.f, 75.f), 5, 1, Vector2(100.f, 100.f), Vector2::Zero, Vector2(390.f, 75.f));
			ObjectPoolManager::AddObjectPool(pEffect->GetName(), pEffect);
		}
		for (int i = 0; i < 5; ++i)
		{
			pEffect = new Effect();
			pEffect->CreateAnimation(nullptr, L"legattack1_hit", Vector2(0.f, 0.f), Vector2(126.f, 107.f), 5, 1, Vector2(100.f, 100.f), Vector2::Zero, Vector2(630.f, 107.f));
			ObjectPoolManager::AddObjectPool(pEffect->GetName(), pEffect);
		}
		for (int i = 0; i < 5; ++i)
		{
			pEffect = new Effect();
			pEffect->CreateAnimation(nullptr, L"legattack2_hit", Vector2(0.f, 0.f), Vector2(197, 119.f), 6, 1, Vector2(100.f, 100.f), Vector2(0.f, 0.3f), Vector2(1182.f, 119.f));
			ObjectPoolManager::AddObjectPool(pEffect->GetName(), pEffect);
		}
		for (int i = 0; i < 5; ++i)
		{
			pEffect = new Effect();
			pEffect->CreateAnimation(nullptr, L"tailattack_hit", Vector2(0.f, 0.f), Vector2(132.f, 120.f), 5, 1, Vector2(100.f, 100.f), Vector2(0.f, 0.3f), Vector2(690.f, 120.f));
			ObjectPoolManager::AddObjectPool(pEffect->GetName(), pEffect);
		}
	}

	void CaveScene::mapping_resource()
	{
		mapping_texture(L"icebreathEffect", L"icebreath_hit");
		mapping_texture(L"iceEffect", L"ice_hit");
		mapping_texture(L"firebreathEffect", L"firebreath_hit");
		mapping_texture(L"fireEffect", L"fire_hit");
		mapping_texture(L"thunderbreathEffect", L"thunderbreath_hit");
		mapping_texture(L"thunderEffect", L"thunder_hit");
		mapping_texture(L"legattack1Effect", L"legattack1_hit");
		mapping_texture(L"legattack2Effect", L"legattack2_hit");
		mapping_texture(L"tailEffect", L"tailattack_hit");


		Resources::Find<Texture>(L"HorntailStartTex")->BindShaderResource(eShaderStage::PS, 12);
		Resources::Find<Texture>(L"HorntailDead")->BindShaderResource(eShaderStage::PS, 12);
	}

}