#include "WCaveScene.h"
#include "WShader.h"
#include "WMeshRenderer.h"
#include "WMesh.h"
#include "WResources.h"
#include "WGameObject.h"
#include "WTransform.h"
#include "WCamera.h"
#include "WCameraScript.h"
#include "WGround.h"
#include "WInput.h"
#include "WSceneManger.h"
#include "WGround.h"
#include "WCollisionManager.h"
#include "WRenderer.h"
#include "WStone.h"
#include "WHorntail.h"
#include "WStoneScript.h"
#include "WLadder.h"
#include "WThreadPool.h"
#include "WMonsterManager.h"

namespace W
{
	CaveScene::CaveScene()
	{
		SetMapSize(0.f, 1.f, 0.f, -1.f);
		SetMapPossibleSize(-7.f, 7.f);

	
		//내가 할당할 리소스들
		m_vecResource.push_back(std::make_pair(L"StoneTex", L"..\\Resources\\Texture\\Monster\\Horntail\\stone.png"));
		m_vecResource.push_back(std::make_pair(L"HorntailStartTex", L"..\\Resources\\Texture\\Monster\\Horntail\\start.png"));
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
	}
	CaveScene::~CaveScene()
	{
		
	}
	void CaveScene::Initialize()
	{
		create_object();
		create_effect();

		CreateBackground();
		{
			GameObject* pCamera = new GameObject();
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
		
		ThreadPool::Joinable();

		create_monster();

		StartSound();

		CollisionManager::SetLayer(eLayerType::Player, eLayerType::Ground, true);
		CollisionManager::SetLayer(eLayerType::Player, eLayerType::Box, true);
		CollisionManager::SetLayer(eLayerType::AttackObject, eLayerType::Box, true);
		CollisionManager::SetLayer(eLayerType::Player, eLayerType::Ladder, true);
		CollisionManager::SetLayer(eLayerType::Monster, eLayerType::AttackObject, true);
		CollisionManager::SetLayer(eLayerType::Monster, eLayerType::Player, true);
		CollisionManager::SetLayer(eLayerType::Player, eLayerType::MonsterAttack, true);
		CollisionManager::SetLayer(eLayerType::Player, eLayerType::Portal, true);
	}
	void CaveScene::OnExit()
	{
		Scene::OnExit();//리소스 해제

		//몬스터 해제
		DeleteMonsterObject();
		MonsterManager::DeleteMonster();

		ThreadPool::Joinable();

		EndSound();
		CollisionManager::Clear();
	}
	void CaveScene::CreateBackground()
	{
		GameObject* pBackGround = new GameObject();
		AudioSource* pAudio = pBackGround->AddComponent<AudioSource>();
		pAudio->SetClip(Resources::Load<AudioClip>(L"cavesound", L"..\\Resources\\sound\\HonTale.mp3"));

		AddGameObject(eLayerType::Background, pBackGround);
		MeshRenderer* pMeshRender = pBackGround->AddComponent<MeshRenderer>();
		pMeshRender->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
		pMeshRender->SetMaterial(Resources::Find<Material>(L"WoodCaveMater"));
		pBackGround->GetComponent<Transform>()->SetPosition(0.f, 0.f, 1.f);
		//14::10
		pBackGround->GetComponent<Transform>()->SetScale(14.f * 1.f, 10.f * 1.f, 1.f);
		
	}
	void CaveScene::StartSound()
	{
		const std::vector<GameObject*> m_vecBackGround = GetLayer(eLayerType::Background).GetGameObjects();
		AudioSource* pAudio = m_vecBackGround[0]->GetComponent<AudioSource>();
		pAudio->SetLoop(true);
		pAudio->Play();
	}

	void CaveScene::EndSound()
	{
		const std::vector<GameObject*> m_vecBackGround = GetLayer(eLayerType::Background).GetGameObjects();
		AudioSource* pAudio = m_vecBackGround[0]->GetComponent<AudioSource>();
		pAudio->Stop();
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

		Ground* pGround = new Ground(true);
		AddGameObject(eLayerType::Ground, pGround);
		pGround->GetComponent<Transform>()->SetPosition(0.f, -3.8f, -0.1f);
		pGround->GetComponent<Transform>()->SetScale(2.7f * 5.f, 1.f * 0.3f, 0.f);

		pGround = new Ground();
		AddGameObject(eLayerType::Ground, pGround);
		pGround->GetComponent<Transform>()->SetPosition(2.71f, -1.7f, -0.1f);
		pGround->GetComponent<Transform>()->SetScale(1.f * 0.6f, 1.f * 0.2f, 0.f);

		pGround = new Ground();
		AddGameObject(eLayerType::Ground, pGround);
		pGround->GetComponent<Transform>()->SetPosition(2.8f, -0.7f, -0.1f);
		pGround->GetComponent<Transform>()->SetScale(1.f * 0.6f, 1.f * 0.2f, 0.f);
		//
		pGround = new Ground();
		AddGameObject(eLayerType::Ground, pGround);
		pGround->GetComponent<Transform>()->SetPosition(4.3f, -1.18f, -0.1f);
		pGround->GetComponent<Transform>()->SetScale(1.f * 2.f, 1.f * 0.2f, 0.f);

		Ladder* pLadder2 = new Ladder();
		AddGameObject(eLayerType::Ladder, pLadder2);
		MeshRenderer* pLadderMeshRender2 = pLadder2->AddComponent<MeshRenderer>();
		pLadderMeshRender2->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
		pLadderMeshRender2->SetMaterial(Resources::Find<Material>(L"LadderBaseMater9"));
		pLadder2->GetComponent<Transform>()->SetPosition(3.5f, -2.4f, -0.1f);
		pLadder2->GetComponent<Transform>()->SetScale(1.f * 0.6f, 4.5f * 0.6f, 0.f);
		pLadder2->Initialize();
		pLadder2->GetComponent<Collider2D>()->SetSize(Vector2(0.3f, 0.9f));
		pLadder2->GetComponent<Collider2D>()->SetCenter(Vector2(0.f, 0.11f));
		//
		//pGround = new Ground();
		//AddGameObject(eLayerType::Ground, pGround);
		//pGround->GetComponent<Transform>()->SetPosition(0.f, -3.8f, -0.1f);
		//pGround->GetComponent<Transform>()->SetScale(2.7f * 5.f, 1.f * 0.3f, 0.f);


	}
	void CaveScene::create_effect()
	{	
		std::shared_ptr<Texture> pTex = 
			Resources::Load<Texture>(L"icebreathHit", L"..\\Resources\\Texture\\Monster\\Horntail\\headA\\attack0_hit.png");
		Effect* pEffect = new Effect();
		pEffect->SetName(L"icebreath");
		pEffect->CreateAnimation(pTex, Vector2(0.f, 0.f), Vector2(110.f, 113.f), 2, 1, Vector2(100.f, 100.f), Vector2::Zero, 0.2f);

		pTex = Resources::Load<Texture>(L"iceHit", L"..\\Resources\\Texture\\Monster\\Horntail\\headA\\attack1_hit.png");
		pEffect = new Effect();
		pEffect->SetName(L"ice");
		pEffect->CreateAnimation(pTex, Vector2(0.f, 0.f), Vector2(118.f, 87.f), 2, 1, Vector2(100.f, 100.f), Vector2::Zero, 0.2f);

		pTex = Resources::Load<Texture>(L"firebreathHit", L"..\\Resources\\Texture\\Monster\\Horntail\\headB\\attack1_hit.png");
		pEffect = new Effect();
		pEffect->SetName(L"firebreath");
		pEffect->CreateAnimation(pTex, Vector2(0.f, 0.f), Vector2(99.f, 107.f), 2, 1, Vector2(100.f, 100.f), Vector2::Zero, 0.2f);

		pTex = Resources::Load<Texture>(L"fireHit", L"..\\Resources\\Texture\\Monster\\Horntail\\headB\\attack2_hit.png");
		pEffect = new Effect();
		pEffect->SetName(L"fire");
		pEffect->CreateAnimation(pTex, Vector2(0.f, 0.f), Vector2(92.f, 91.f), 4, 1, Vector2(100.f, 100.f), Vector2::Zero, 0.2f);

		pTex = Resources::Load<Texture>(L"thunderbreathHit", L"..\\Resources\\Texture\\Monster\\Horntail\\headC\\attack1_hit.png");
		pEffect = new Effect();
		pEffect->SetName(L"thunderbreath");
		pEffect->CreateAnimation(pTex, Vector2(0.f, 0.f), Vector2(72.f, 82.f), 4, 1, Vector2(100.f, 100.f), Vector2::Zero, 0.2f);

		pTex = Resources::Load<Texture>(L"thunderHit", L"..\\Resources\\Texture\\Monster\\Horntail\\headC\\attack2_hit.png");
		pEffect = new Effect();
		pEffect->SetName(L"thunder");
		pEffect->CreateAnimation(pTex, Vector2(0.f, 0.f), Vector2(78.f, 75.f), 5, 1, Vector2(100.f, 100.f), Vector2::Zero, 0.2f);

		pTex = Resources::Load<Texture>(L"legattack1Hit", L"..\\Resources\\Texture\\Monster\\Horntail\\Leg\\attack1_hit.png");
		pEffect = new Effect();
		pEffect->SetName(L"legattack1");
		pEffect->CreateAnimation(pTex, Vector2(0.f, 0.f), Vector2(126.f, 107.f), 5, 1, Vector2(100.f, 100.f), Vector2::Zero, 0.2f);

		pTex = Resources::Load<Texture>(L"legattack2Hit", L"..\\Resources\\Texture\\Monster\\Horntail\\Leg\\attack2_hit.png");
		pEffect = new Effect();
		pEffect->SetName(L"legattack2");
		pEffect->CreateAnimation(pTex, Vector2(0.f, 0.f), Vector2(197, 119.f), 6, 1, Vector2(100.f, 100.f), Vector2(0.f, 0.3f), 0.1f);
		
		pTex = Resources::Load<Texture>(L"tailHit", L"..\\Resources\\Texture\\Monster\\Horntail\\tail\\attack0_hit.png");
		pEffect = new Effect();
		pEffect->SetName(L"tailattack");
		pEffect->CreateAnimation(pTex, Vector2(0.f, 0.f), Vector2(132.f, 120.f), 5, 1, Vector2(100.f, 100.f), Vector2(0.f, 0.3f), 0.2f);
	}

	void CaveScene::create_monster()
	{
		Stone* pStone = new Stone();
		AddGameObject(eLayerType::Box, pStone);
		pStone->GetComponent<Transform>()->SetPosition(4.45f, 0.f, -0.1f);

		Horntail* pHorntail = new Horntail();
		pHorntail->Initialize();
		AddGameObject(eLayerType::Monster, pHorntail);
		pHorntail->GetComponent<Transform>()->SetPosition(-1.2f, 0.73f, -1.5f);

		std::function<void()> start = std::bind(&Horntail::Start, pHorntail);
		pStone->GetScript<StoneScript>()->SetFunction(start);
	}

}