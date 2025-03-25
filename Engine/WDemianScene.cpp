#include "WDemianScene.h"
#include "WResources.h"
#include "WCamera.h"
#include "WCameraScript.h"
#include "WGround.h"
#include "WDemian.h"
#include "WCollisionManager.h"
#include "WDemianPhase2.h"
#include "WSharHP.h"
#include "WMonsterScript.h"
#include "WWhite.h"
#include "WEventManager.h"
#include "WStigmaBack.h"
#include "WTime.h"
#include "WThreadPool.h"
#include "WMonsterManager.h"

namespace W
{
	DemianScene::DemianScene():
		m_pWhite(nullptr),
		m_bEnd(false),
		m_pStigmaBack(nullptr),
		m_iFadeCallStack(1),
		m_fStigmaTime(30.f),
		m_fCurStigmaTime(0.f)
	{
		SetMapSize(-1.9f, -1.f, 1.9f, -1.f);
		SetMapPossibleSize(-8.9f, 8.9f);

		std::shared_ptr<Texture> pTempleBossTex =
			Resources::Load<Texture>(L"DemianBossScene", L"..\\Resources\\Texture\\background\\demain_back.png");
		std::shared_ptr<Material> pMater = std::make_shared<Material>();
		pMater->SetShader(Resources::Find<Shader>(L"BackgroundShader"));
		pMater->SetTexture(pTempleBossTex);
		Resources::Insert(L"DemianBackMater", pMater);

		m_vecResource.push_back(std::make_pair(L"DemianNormal", L"..\\Resources\\Texture\\Monster\\demian\\stand.png"));
		m_vecResource.push_back(std::make_pair(L"DemianDead", L"..\\Resources\\Texture\\Monster\\demian\\dead0.png"));
		m_vecResource.push_back(std::make_pair(L"Demian_attack0", L"..\\Resources\\Texture\\Monster\\demian\\attack0.png"));
		m_vecResource.push_back(std::make_pair(L"Demian_attack1", L"..\\Resources\\Texture\\Monster\\demian\\attack1.png"));
		m_vecResource.push_back(std::make_pair(L"Demian_attack2", L"..\\Resources\\Texture\\Monster\\demian\\attack2.png"));
		m_vecResource.push_back(std::make_pair(L"Demian_attack3", L"..\\Resources\\Texture\\Monster\\demian\\attack3.png"));

		m_vecResource.push_back(std::make_pair(L"demainfire0", L"..\\Resources\\Texture\\Monster\\demian\\demainfire0.png"));
		m_vecResource.push_back(std::make_pair(L"demianExplode", L"..\\Resources\\Texture\\Monster\\demian\\demain_explode.png"));
		m_vecResource.push_back(std::make_pair(L"demainkeyAttack", L"..\\Resources\\Texture\\Monster\\demian\\keyAttack.png"));
		m_vecResource.push_back(std::make_pair(L"demainInputBack", L"..\\Resources\\Texture\\Monster\\demian\\inputbackground.png"));
		m_vecResource.push_back(std::make_pair(L"Inputright", L"..\\Resources\\Texture\\Monster\\demian\\right.png"));
		m_vecResource.push_back(std::make_pair(L"Inputleft", L"..\\Resources\\Texture\\Monster\\demian\\left.png"));
		m_vecResource.push_back(std::make_pair(L"Inputup", L"..\\Resources\\Texture\\Monster\\demian\\up.png"));
		m_vecResource.push_back(std::make_pair(L"Inputdown", L"..\\Resources\\Texture\\Monster\\demian\\down.png"));

		m_vecResource.push_back(std::make_pair(L"DemianSword", L"..\\Resources\\Texture\\Monster\\demian\\sword.png"));
		m_vecResource.push_back(std::make_pair(L"swordExplodeTex", L"..\\Resources\\Texture\\Monster\\demian\\swordexplode.png"));
		m_vecResource.push_back(std::make_pair(L"vine", L"..\\Resources\\Texture\\Monster\\demian\\vine.png"));
		m_vecResource.push_back(std::make_pair(L"Stigma", L"..\\Resources\\Texture\\Monster\\demian\\stigma.png"));
		m_vecResource.push_back(std::make_pair(L"StigmaBack", L"..\\Resources\\Texture\\Monster\\demian\\stigmaback.png"));

		m_vecResource.push_back(std::make_pair(L"Demian2Normal", L"..\\Resources\\Texture\\Monster\\demian\\stand1.png"));
		m_vecResource.push_back(std::make_pair(L"Demian2Dead", L"..\\Resources\\Texture\\Monster\\demian\\dead1.png"));
		m_vecResource.push_back(std::make_pair(L"Demian2_attack0", L"..\\Resources\\Texture\\Monster\\demian\\attack10.png"));
		m_vecResource.push_back(std::make_pair(L"Demian2_attack1", L"..\\Resources\\Texture\\Monster\\demian\\attack11.png"));
		m_vecResource.push_back(std::make_pair(L"Demian2_attack2", L"..\\Resources\\Texture\\Monster\\demian\\attack12.png"));
		m_vecResource.push_back(std::make_pair(L"Demian2_attack3", L"..\\Resources\\Texture\\Monster\\demian\\attack13.png"));
		m_vecResource.push_back(std::make_pair(L"Demian2_attack4", L"..\\Resources\\Texture\\Monster\\demian\\attack14.png"));
		m_vecResource.push_back(std::make_pair(L"Demian2_attack5", L"..\\Resources\\Texture\\Monster\\demian\\attack15.png"));

		m_vecResource.push_back(std::make_pair(L"demainfire1", L"..\\Resources\\Texture\\Monster\\demian\\demianfire1.png"));
		m_vecResource.push_back(std::make_pair(L"demainfire2", L"..\\Resources\\Texture\\Monster\\demian\\demainfire2.png"));
		
		m_vecResource.push_back(std::make_pair(L"demianspear0", L"..\\Resources\\Texture\\Monster\\demian\\demianspear0.png"));
		m_vecResource.push_back(std::make_pair(L"demianspear1", L"..\\Resources\\Texture\\Monster\\demian\\demianspear1.png"));
		
		//구
		m_vecResource.push_back(std::make_pair(L"DemianCircle", L"..\\Resources\\Texture\\Monster\\demian\\circle.png"));

		
	}
	DemianScene::~DemianScene()
	{
		if (!m_bEnd)
		{
			delete m_pWhite;
			m_pWhite = nullptr;
		}
	}
	void DemianScene::Initialize()
	{
		CreateBackground();
		create_effect();

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
	void DemianScene::Update()
	{
		float fRatio = 0.f;
		float fMaxHP = 0.f;
		float fHP = 0.f;

		const std::vector<GameObject*>& vecMonster =
			GetLayer(eLayerType::Monster).GetGameObjects();
		
		for (UINT i = 0; i < vecMonster.size(); ++i)
		{
			if (vecMonster[0]->GetState() == GameObject::eState::Paused)
			{
				if (m_iFadeCallStack == 1 &&
					dynamic_cast<Demian*>(vecMonster[0]))
				{
					fadein();
				}
			}
				
			const tObjectInfo& tInfo = vecMonster[i]->GetScript<MonsterScript>()->GetObjectInfo();

			fMaxHP += tInfo.fMaxHP;
			fHP += tInfo.fHP;
		}

		fRatio = (fHP / fMaxHP) * 100.f;
		m_pSharHP->SetHPValue(fRatio);

		Scene::Update();
	}
	void DemianScene::LateUpdate()
	{
		Scene::LateUpdate();

	}
	void DemianScene::Render()
	{
		Scene::Render();

	}
	void DemianScene::OnEnter()
	{
		Scene::OnEnter();
		ThreadPool::Joinable();

		create_monster();
		create_event();

		StartSound();

		CollisionManager::SetLayer(eLayerType::Player, eLayerType::Ground, true);
		CollisionManager::SetLayer(eLayerType::ItemObject, eLayerType::Ground, true);
		CollisionManager::SetLayer(eLayerType::ItemObject, eLayerType::Player, true);
		CollisionManager::SetLayer(eLayerType::Monster, eLayerType::AttackObject, true);
		CollisionManager::SetLayer(eLayerType::Player, eLayerType::MonsterAttack, true);
		CollisionManager::SetLayer(eLayerType::Ground, eLayerType::MonsterAttack, true);

		m_bEnd = false;
		m_iFadeCallStack = 1;
	}
	void DemianScene::OnExit()
	{
		Scene::OnExit();
		DeleteMonsterObject();
		MonsterManager::DeleteMonster();

		EndSound();
		m_pWhite = nullptr;

		CollisionManager::Clear();
	}
	void DemianScene::CreateBackground()
	{
		GameObject* pBackGround = new GameObject();
		AudioSource* pAudio = pBackGround->AddComponent<AudioSource>();
		pAudio->SetClip(Resources::Load<AudioClip>(L"DemianScene0sound", L"..\\Resources\\sound\\Demian.mp3"));

		AddGameObject(eLayerType::Background, pBackGround);
		MeshRenderer* pMeshRender = pBackGround->AddComponent<MeshRenderer>();
		pMeshRender->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
		pMeshRender->SetMaterial(Resources::Find<Material>(L"DemianBackMater"));
		pBackGround->GetComponent<Transform>()->SetPosition(0.f, 0.f, 1.f);
		//2 : 1
		pBackGround->GetComponent<Transform>()->SetScale(2.2372f * 8.f, 1.f * 8.f, 1.f);


		Ground* pGround = new Ground(true);
		AddGameObject(eLayerType::Ground, pGround);
		pGround->GetComponent<Transform>()->SetPosition(0.f, -2.95f, -0.1f);
		pGround->GetComponent<Transform>()->SetScale(4.3f * 7.f, 1.f * 0.3f, 0.f);
	}

	void DemianScene::StartSound()
	{
		const std::vector<GameObject*> m_vecBackGround = GetLayer(eLayerType::Background).GetGameObjects();
		AudioSource* pAudio = m_vecBackGround[0]->GetComponent<AudioSource>();
		pAudio->SetLoop(true);
		pAudio->Play();
	}

	void DemianScene::EndSound()
	{
		const std::vector<GameObject*> m_vecBackGround = GetLayer(eLayerType::Background).GetGameObjects();
		AudioSource* pAudio = m_vecBackGround[0]->GetComponent<AudioSource>();
		pAudio->Stop();
	}

	void DemianScene::fadein()
	{
		m_bEnd = true;
		m_iFadeCallStack = 0;
		m_pWhite->Initialize();
		EventManager::CreateObject(m_pWhite, eLayerType::Object);
	}
	void DemianScene::phase2()
	{
		m_bEnd = false;
		const std::vector<GameObject*>& vecGameObj =
			GetLayer(eLayerType::Monster).GetGameObjects();

		//phase2 데미안
		vecGameObj[1]->GetComponent<Collider2D>()->SetActive(true);
		vecGameObj[1]->SetState(GameObject::eState::Active);
	}

	void DemianScene::check_stigma()
	{
		m_fCurStigmaTime += Time::DeltaTime();
		if (m_fCurStigmaTime >= m_fStigmaTime)
		{
			m_fCurStigmaTime = 0.f;
			BattleManager::HitchAbnormal(BattleManager::eAbnormalType::Stigma);
		}
	}

	void DemianScene::create_monster()
	{
		Demian* pDemian = new Demian();
		pDemian->Initialize();
		AddGameObject(eLayerType::Monster, pDemian);

		DemianPhase2* pDemian2 = new DemianPhase2();
		pDemian2->Initialize();
		AddGameObject(eLayerType::Monster, pDemian2);
		pDemian2->GetComponent<Collider2D>()->SetActive(false);
		pDemian2->SetState(GameObject::eState::Paused);
	}

	void DemianScene::create_event()
	{
		m_pWhite = new White();
		m_pWhite->SetEndTime(2.f);
		m_pWhite->SetFunction(std::bind(&DemianScene::phase2, this));

		m_pSharHP = new SharHP();
		AddGameObject(eLayerType::UI, m_pSharHP);
		m_pSharHP->Initialize();

		m_pStigmaBack = new StigmaBack();
		m_pStigmaBack->Initialize();
		AddGameObject(eLayerType::Object, m_pStigmaBack);
	}

	void DemianScene::create_effect()
	{
		std::shared_ptr<Texture> pTex = Resources::Load<Texture>(L"demianfire1hit", L"..\\Resources\\Texture\\Monster\\demian\\demianfire1hit.png");
		Effect* pAttack_hit1 = new Effect();
		pAttack_hit1->SetName(L"Demian2_attack1");
		pAttack_hit1->CreateAnimation(pTex, Vector2(0.f, 0.f), Vector2(227.f, 228.f), 5, 1, Vector2(250.f, 250.f), Vector2(0.f, 0.f), 0.2f);

		pTex = Resources::Load<Texture>(L"DemianAttack0Effect", L"..\\Resources\\Texture\\Monster\\demian\\demianEffect.png");
		Effect* pEffect = new Effect();
		pEffect->GetComponent<Transform>()->SetScale(Vector3(18.f, 18.f, 0.f));
		pEffect->SetName(L"DemianAttack0Effect");
		pEffect->CreateAnimation(pTex, Vector2(0.f, 0.f), Vector2(1122.f, 382.f), 9, 1, Vector2(2000.f, 2000.f), Vector2(0.f, 0.f), 0.1f);


		for (int i = 0; i < 2; ++i)
		{
			Effect* pClone1 = new Effect();
			pClone1->GetComponent<Transform>()->SetScale(Vector3(18.f, 18.f, 0.f));
			pClone1->SetName(L"DemianClone0");
			pTex = Resources::Load<Texture>(L"demianClone0", L"..\\Resources\\Texture\\Monster\\demian\\demianclone0.png");
			pClone1->CreateAnimation(pTex, Vector2(0.f, 0.f), Vector2(515.f, 318.f), 8, 1, Vector2(2000.f, 2000.f), Vector2(0.f, 0.f), 0.1f);
		}
		//pClone1->SetFunction(std::bind(&DemianPhase2::create_spear0, this), 1);

		Effect* pClone2 = new Effect();
		pClone2->GetComponent<Transform>()->SetScale(Vector3(18.f, 18.f, 0.f));
		pClone2->SetName(L"DemianClone1");
		pTex = Resources::Load<Texture>(L"demianClone1", L"..\\Resources\\Texture\\Monster\\demian\\demianclone1.png");
		pClone2->CreateAnimation(pTex, Vector2(0.f, 0.f), Vector2(679.f, 542.f), 8, 1, Vector2(1800.f, 1800.f), Vector2(0.f, 0.f), 0.1f);
		//pClone2->SetFunction(std::bind(&DemianPhase2::create_spear1, this), 1);

		for (int i = 0; i < 3; ++i)
		{
			pTex = Resources::Load<Texture>(L"DemianTarget", L"..\\Resources\\Texture\\Monster\\demian\\target.png");
			Effect* pEffect = new Effect();
			pEffect->GetComponent<Transform>()->SetScale(3.5f, 3.5f, 0.f);
			pEffect->SetName(L"DemianTarget");
			pEffect->CreateAnimation(pTex, Vector2(0.f, 0.f), Vector2(286.f, 288.f), 14, 1, Vector2(300.f, 300.f), Vector2::Zero, 0.1f);
		}
	}
}