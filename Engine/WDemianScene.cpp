#include "WDemianScene.h"
#include "WResources.h"
#include "WCamera.h"
#include "WCameraScript.h"
#include "WGround.h"
#include "WDemian.h"
#include "WDemianPhase2.h"
#include "WSharHP.h"
#include "WWhite.h"
#include "WEventManager.h"
#include "WStigmaBack.h"
#include "WTime.h"
#include "WThreadPool.h"
#include "WTransform.h"
#include "WEffect.h"
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


		m_vecResource.push_back(std::make_pair(L"demianfire1hit", L"..\\Resources\\Texture\\Monster\\demian\\demianfire1hit.png"));
		m_vecResource.push_back(std::make_pair(L"DemianAttack0Effect", L"..\\Resources\\Texture\\Monster\\demian\\demianEffect.png"));
		m_vecResource.push_back(std::make_pair(L"demianClone0", L"..\\Resources\\Texture\\Monster\\demian\\demianclone0.png"));
		m_vecResource.push_back(std::make_pair(L"demianClone1", L"..\\Resources\\Texture\\Monster\\demian\\demianclone1.png"));
		m_vecResource.push_back(std::make_pair(L"DemianTarget", L"..\\Resources\\Texture\\Monster\\demian\\target.png"));

	}
	DemianScene::~DemianScene()
	{
		
	}
	void DemianScene::Initialize()
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
	void DemianScene::Update()
	{
		

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

		
		m_bEnd = false;
		m_iFadeCallStack = 1;
	}
	void DemianScene::OnExit()
	{
		Scene::OnExit();

		m_pWhite = nullptr;

	}
	void DemianScene::CreateBackground()
	{
		GameObject* pBackGround = new GameObject();
		
		AddGameObject(eLayerType::Background, pBackGround);
		MeshRenderer* pMeshRender = pBackGround->AddComponent<MeshRenderer>();
		pMeshRender->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
		pMeshRender->SetMaterial(Resources::Find<Material>(L"DemianBackMater"));
		pBackGround->GetComponent<Transform>()->SetPosition(0.f, 0.f, 1.f);
		//2 : 1
		pBackGround->GetComponent<Transform>()->SetScale(2.2372f * 8.f, 1.f * 8.f, 1.f);
	}

	void DemianScene::StartSound()
	{
	
	}

	void DemianScene::EndSound()
	{
	}

	void DemianScene::SendEnter()
	{
		mapping_resource();

		Scene::SendEnter();
	}

	void DemianScene::add_objectpool()
	{
		Demian* pDemian = new Demian();
		ObjectPoolManager::AddObjectPool(pDemian->GetName(), pDemian);

		DemianPhase2* pDemian2 = new DemianPhase2();
		ObjectPoolManager::AddObjectPool(pDemian2->GetName(), pDemian2);

		Effect* pAttack_hit1 = new Effect();
		pAttack_hit1->CreateAnimation(nullptr, L"Demian2_attack1_hit", Vector2(0.f, 0.f), Vector2(227.f, 228.f), 5, 1, Vector2(250.f, 250.f), Vector2(0.f, 0.f), Vector2(1362.f,228.f));
		ObjectPoolManager::AddObjectPool(pAttack_hit1->GetName(), pAttack_hit1);

		Effect* pEffect = new Effect();
		pEffect->GetComponent<Transform>()->SetScale(Vector3(18.f, 18.f, 0.f));
		pEffect->CreateAnimation(nullptr,L"DemianAttack0Effect_hit", Vector2(0.f, 0.f), Vector2(1122.f, 382.f), 9, 1, Vector2(2000.f, 2000.f), Vector2(0.f, 0.f), Vector2(10098.f,382.f));
		ObjectPoolManager::AddObjectPool(pEffect->GetName(), pEffect);

		for (int i = 0; i < 2; ++i)
		{
			Effect* pClone1 = new Effect();
			pClone1->GetComponent<Transform>()->SetScale(Vector3(18.f, 18.f, 0.f));
			pClone1->CreateAnimation(nullptr, L"DemianClone0", Vector2(0.f, 0.f), Vector2(515.f, 318.f), 8, 1, Vector2(2000.f, 2000.f), Vector2(0.f, 0.f), Vector2(5172.f, 1095.f));
		}

		Effect* pClone2 = new Effect();
		pClone2->GetComponent<Transform>()->SetScale(Vector3(18.f, 18.f, 0.f));
		pClone2->CreateAnimation(nullptr, L"DemianClone1", Vector2(0.f, 0.f), Vector2(679.f, 542.f), 8, 1, Vector2(1800.f, 1800.f), Vector2(0.f, 0.f), Vector2(5172.f, 1095.f));

		for (int i = 0; i < 3; ++i)
		{
			Effect* pEffect = new Effect();
			pEffect->GetComponent<Transform>()->SetScale(3.5f, 3.5f, 0.f);
			pEffect->CreateAnimation(nullptr, L"DemianTarget_hit", Vector2(0.f, 0.f), Vector2(286.f, 288.f), 14, 1, Vector2(300.f, 300.f), Vector2::Zero, Vector2(2268.f, 187.f));
		}
	}

	void DemianScene::mapping_resource()
	{
		mapping_texture(L"demianfire1hit", L"Demian2_attack1_hit");
		mapping_texture(L"DemianAttack0Effect", L"DemianAttack0Effect_hit");
		mapping_texture(L"demianClone0", L"demianClone0");
		mapping_texture(L"demianClone1", L"demianClone1");
		mapping_texture(L"DemianTarget", L"DemianTarget_hit");
	}

	void DemianScene::fadein()
	{
		m_bEnd = true;
		m_iFadeCallStack = 0;
		
	}
	void DemianScene::phase2()
	{
	
	}



	void DemianScene::create_monster()
	{
		
	}
}