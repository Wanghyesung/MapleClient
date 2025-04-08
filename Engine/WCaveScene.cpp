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
#include "WRenderer.h"
#include "WStone.h"
#include "WHorntail.h"
#include "WLadder.h"
#include "WThreadPool.h"

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

	}
	void CaveScene::OnExit()
	{
		Scene::OnExit();//리소스 해제

		ThreadPool::Joinable();

	}
	void CaveScene::CreateBackground()
	{
		GameObject* pBackGround = new GameObject();
		
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

	}
	void CaveScene::create_effect()
	{

		Resources::Load<Texture>(L"icebreathHit", L"..\\Resources\\Texture\\Monster\\Horntail\\headA\\attack0_hit.png");

		Resources::Load<Texture>(L"iceHit", L"..\\Resources\\Texture\\Monster\\Horntail\\headA\\attack1_hit.png");

		Resources::Load<Texture>(L"firebreathHit", L"..\\Resources\\Texture\\Monster\\Horntail\\headB\\attack1_hit.png");

		Resources::Load<Texture>(L"fireHit", L"..\\Resources\\Texture\\Monster\\Horntail\\headB\\attack2_hit.png");

		Resources::Load<Texture>(L"thunderbreathHit", L"..\\Resources\\Texture\\Monster\\Horntail\\headC\\attack1_hit.png");

		Resources::Load<Texture>(L"thunderHit", L"..\\Resources\\Texture\\Monster\\Horntail\\headC\\attack2_hit.png");

		Resources::Load<Texture>(L"legattack1Hit", L"..\\Resources\\Texture\\Monster\\Horntail\\Leg\\attack1_hit.png");

		Resources::Load<Texture>(L"legattack2Hit", L"..\\Resources\\Texture\\Monster\\Horntail\\Leg\\attack2_hit.png");

		Resources::Load<Texture>(L"tailHit", L"..\\Resources\\Texture\\Monster\\Horntail\\tail\\attack0_hit.png");

	}

	void CaveScene::create_monster()
	{
		//Stone* pStone = new Stone();
		//AddGameObject(eLayerType::Box, pStone);
		//pStone->GetComponent<Transform>()->SetPosition(4.45f, 0.f, -0.1f);
		//
		//Horntail* pHorntail = new Horntail();
		//pHorntail->Initialize();
		//AddGameObject(eLayerType::Monster, pHorntail);
		//pHorntail->GetComponent<Transform>()->SetPosition(-1.2f, 0.73f, -1.5f);
		
	}

}