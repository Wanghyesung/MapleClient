#include "WDemian.h"
#include "WResources.h"
#include "WAnimator.h"
#include "WEventManager.h"
#include "WDemianExplode.h"
#include "WSpawnMonsterAttack.h"
#include "WDemianFire0.h"
#include "WDemianSword.h"
#include "WSceneManger.h"
#include "WSceneManger.h"
#include "WDemianKeyAttack.h"
#include "WSwordExplode.h"
#include "WTime.h"
#include "WObjectPoolManager.h"
#include "WInput.h"
#include "WInputObject.h"
namespace W
{
	Demian::Demian()
	{
		SetName(L"Demian1");

		MeshRenderer* pRenderer = AddComponent<MeshRenderer>();
		pRenderer->SetMesh(Resources::Find<Mesh>(L"RectMesh"));


		std::shared_ptr<Material> pMater = std::make_shared<Material>();
		pMater->SetRenderinMode(eRenderingMode::Transparent);
		pMater->SetShader(Resources::Find<Shader>(L"MonsterShader"));
		Resources::Insert(L"DemianMater", pMater);

		pRenderer->SetMaterial(pMater);
	
		GetComponent<Transform>()->SetScale(18.f, 18.f, 0.f);

		//pAttack0->BindShaderResource(eShaderStage::PS, 12);
		//pAttack1->BindShaderResource(eShaderStage::PS, 12);
		//pAttack2->BindShaderResource(eShaderStage::PS, 12);
		//pAttack3->BindShaderResource(eShaderStage::PS, 12);
		//pDead->BindShaderResource(eShaderStage::PS, 12);

		Animator* pAnim = AddComponent<Animator>();
		pAnim->Create(L"Demian1_stand_left", nullptr, Vector2(0.f, 0.f), Vector2(2000.f, 2000.f), 7, Vector2(2000.f, 2000.f), Vector2::Zero, Vector2(14000.f, 1300.f),0.15f);

		pAnim->Create(L"Demian1_dead_left", nullptr, Vector2(0.f, 0.f), Vector2(2000.f, 2000.f), 7, Vector2(2000.f, 2000.f), Vector2::Zero, Vector2(14000, 5200.f),0.15f);
		pAnim->FindAnimation(L"Demian1_dead_left")->Create(L"Demian1_dead_left", nullptr, Vector2(0.f, 1300.f), Vector2(2000.f, 2000.f), 6, Vector2(2000.f, 2000.f), Vector2::Zero, Vector2(14000, 5200.f), 0.15f);
		for (int i = 0; i < 3; ++i)
		{
			pAnim->FindAnimation(L"Demian1_dead_left")->Create(L"Demian1_dead_left", nullptr, Vector2(0.f, 2600.f), Vector2(2000.f, 2000.f), 7, Vector2(2000.f, 2000.f), Vector2::Zero, Vector2(14000, 5200.f), 0.15f);
			pAnim->FindAnimation(L"Demian1_dead_left")->Create(L"Demian1_dead_left", nullptr, Vector2(0.f, 3900.f), Vector2(2000.f, 2000.f), 5, Vector2(2000.f, 2000.f), Vector2::Zero, Vector2(14000, 5200.f), 0.15f);
		}

		pAnim->Create(L"Demian1_attack0_left", nullptr, Vector2(0.f, 0.f), Vector2(2000.f, 2000.f), 7, Vector2(2000.f, 2000.f), Vector2::Zero, Vector2(14000.f, 6500.f), 0.15f);
		pAnim->FindAnimation(L"Demian1_attack0_left")->Create(L"Demian1_attack0_left", nullptr, Vector2(0.f, 1300.f), Vector2(2000.f, 2000.f), 7, Vector2(2000.f, 2000.f),  Vector2::Zero, Vector2(14000.f, 6500.f), 0.15f);
		pAnim->FindAnimation(L"Demian1_attack0_left")->Create(L"Demian1_attack0_left", nullptr, Vector2(0.f, 2600.f), Vector2(2000.f, 2000.f), 7, Vector2(2000.f, 2000.f), Vector2::Zero, Vector2(14000.f, 6500.f), 0.15f);
		pAnim->FindAnimation(L"Demian1_attack0_left")->Create(L"Demian1_attack0_left", nullptr, Vector2(0.f, 3900.f), Vector2(2000.f, 2000.f), 7, Vector2(2000.f, 2000.f), Vector2::Zero, Vector2(14000.f, 6500.f), 0.15f);
		pAnim->FindAnimation(L"Demian1_attack0_left")->Create(L"Demian1_attack0_left", nullptr, Vector2(0.f, 5200.f), Vector2(2000.f, 2000.f), 7, Vector2(2000.f, 2000.f), Vector2::Zero, Vector2(14000.f, 6500.f), 0.15f);

		pAnim->Create(L"Demian1_attack1_left", nullptr, Vector2(0.f, 0.f), Vector2(2000.f, 2000.f), 7, Vector2(2000.f, 2000.f), Vector2::Zero, Vector2(14000.f, 7800.f), 0.15f);
		pAnim->FindAnimation(L"Demian1_attack1_left")->Create(L"Demian1_attack1_left", nullptr, Vector2(0.f, 1300.f), Vector2(2000.f, 2000.f), 7, Vector2(2000.f, 2000.f), Vector2::Zero, Vector2(14000.f, 7800.f), 0.15f);
		pAnim->FindAnimation(L"Demian1_attack1_left")->Create(L"Demian1_attack1_left", nullptr, Vector2(0.f, 2600.f), Vector2(2000.f, 2000.f), 7, Vector2(2000.f, 2000.f), Vector2::Zero, Vector2(14000.f, 7800.f), 0.15f);
		pAnim->FindAnimation(L"Demian1_attack1_left")->Create(L"Demian1_attack1_left", nullptr, Vector2(0.f, 3900.f), Vector2(2000.f, 2000.f), 7, Vector2(2000.f, 2000.f), Vector2::Zero, Vector2(14000.f, 7800.f), 0.15f);
		pAnim->FindAnimation(L"Demian1_attack1_left")->Create(L"Demian1_attack1_left", nullptr, Vector2(0.f, 5200.f), Vector2(2000.f, 2000.f), 7, Vector2(2000.f, 2000.f), Vector2::Zero, Vector2(14000.f, 7800.f), 0.15f);
		pAnim->FindAnimation(L"Demian1_attack1_left")->Create(L"Demian1_attack1_left", nullptr, Vector2(0.f, 6500.f), Vector2(2000.f, 2000.f), 6, Vector2(2000.f, 2000.f), Vector2::Zero, Vector2(14000.f, 7800.f), 0.15f);

		pAnim->Create(L"Demian1_attack2_left", nullptr, Vector2(0.f, 0.f), Vector2(2000.f, 2000.f), 7, Vector2(2000.f, 2000.f), Vector2::Zero, Vector2(14000.f, 7800.f), 0.15f);
		pAnim->FindAnimation(L"Demian1_attack2_left")->Create(L"Demian1_attack2_left", nullptr, Vector2(0.f, 1300.f), Vector2(2000.f, 2000.f), 7, Vector2(2000.f, 2000.f), Vector2::Zero, Vector2(14000.f, 7800.f),0.15f);
		pAnim->FindAnimation(L"Demian1_attack2_left")->Create(L"Demian1_attack2_left", nullptr, Vector2(0.f, 2600.f), Vector2(2000.f, 2000.f), 7, Vector2(2000.f, 2000.f), Vector2::Zero, Vector2(14000.f, 7800.f),0.15f);
		pAnim->FindAnimation(L"Demian1_attack2_left")->Create(L"Demian1_attack2_left", nullptr, Vector2(0.f, 3900.f), Vector2(2000.f, 2000.f), 7, Vector2(2000.f, 2000.f), Vector2::Zero, Vector2(14000.f, 7800.f),0.15f);
		pAnim->FindAnimation(L"Demian1_attack2_left")->Create(L"Demian1_attack2_left", nullptr, Vector2(0.f, 5200.f), Vector2(2000.f, 2000.f), 7, Vector2(2000.f, 2000.f), Vector2::Zero, Vector2(14000.f, 7800.f),0.15f);
		pAnim->FindAnimation(L"Demian1_attack2_left")->Create(L"Demian1_attack2_left", nullptr, Vector2(0.f, 6500.f), Vector2(2000.f, 2000.f), 4, Vector2(2000.f, 2000.f), Vector2::Zero, Vector2(14000.f, 7800.f),0.15f);
	

		pAnim->Create(L"Demian1_attack3_left", nullptr, Vector2(0.f, 0.f), Vector2(2000.f, 2000.f), 7, Vector2(2000.f, 2000.f), Vector2::Zero, Vector2(14000.f, 6500.f),  0.15f);
		pAnim->FindAnimation(L"Demian1_attack3_left")->Create(L"Demian1_attack3_left", nullptr, Vector2(0.f, 1300.f), Vector2(2000.f, 2000.f), 7, Vector2(2000.f, 2000.f), Vector2::Zero, Vector2(14000.f, 6500.f), 0.15f);
		pAnim->FindAnimation(L"Demian1_attack3_left")->Create(L"Demian1_attack3_left", nullptr, Vector2(0.f, 2600.f), Vector2(2000.f, 2000.f), 7, Vector2(2000.f, 2000.f), Vector2::Zero, Vector2(14000.f, 6500.f), 0.15f);
		for (int i = 0; i < 3; ++i)
		{
			//이미지 반복
			for (int j = 0; j < 10; ++j)
				pAnim->FindAnimation(L"Demian1_attack3_left")->Create(L"Demian1_attack3_left", nullptr, Vector2(8000.f, 2600.f), Vector2(2000.f, 2000.f), 3, Vector2(2000.f, 2000.f), Vector2::Zero, Vector2(14000.f, 6500.f), 0.15f);
		}
		pAnim->FindAnimation(L"Demian1_attack3_left")->Create(L"Demian1_attack3_left", nullptr, Vector2(0.f, 3900.f), Vector2(2000.f, 2000.f), 7, Vector2(2000.f, 2000.f), Vector2::Zero, Vector2(14000.f, 6500.f), 0.15f);
		pAnim->FindAnimation(L"Demian1_attack3_left")->Create(L"Demian1_attack3_left", nullptr, Vector2(0.f, 5200.f), Vector2(2000.f, 2000.f), 7, Vector2(2000.f, 2000.f), Vector2::Zero, Vector2(14000.f, 6500.f), 0.15f);

		pAnim->Create(L"Demian1_stand_right", nullptr, Vector2(12000.f, 0.f), Vector2(-2000.f, 2000.f), 7, Vector2(2000.f, 2000.f), Vector2::Zero, Vector2(14000.f, 1300.f), 0.15f);
		
		pAnim->Create(L"Demian1_dead_right", nullptr, Vector2(12000.f, 0.f), Vector2(12000.f, 1300.f), 7, Vector2(-2000.f, 2000.f), Vector2::Zero, Vector2(14000.f, 5200.f), 0.15f);
		pAnim->FindAnimation(L"Demian1_dead_right")->Create(L"Demian1_dead_right", nullptr, Vector2(12000.f, 1300.f), Vector2(-2000.f, 2000.f), 6, Vector2(2000.f, 2000.f), Vector2::Zero, Vector2(14000.f, 5200.f), 0.15f);
		for (int i = 0; i < 3; ++i)
		{
			pAnim->FindAnimation(L"Demian1_dead_right")->Create(L"Demian1_dead_right", nullptr, Vector2(12000.f, 2600.f), Vector2(-2000.f, 2000.f), 7, Vector2(2000.f, 2000.f), Vector2::Zero, Vector2(14000.f, 5200.f), 0.15f);
			pAnim->FindAnimation(L"Demian1_dead_right")->Create(L"Demian1_dead_right", nullptr, Vector2(12000.f, 3900.f), Vector2(-2000.f, 2000.f), 5, Vector2(2000.f, 2000.f), Vector2::Zero, Vector2(14000.f, 5200.f), 0.15f);
		}

		pAnim->Create(L"Demian1_attack0_right", nullptr, Vector2(12000.f, 0.f), Vector2(-2000.f, 2000.f), 7, Vector2(2000.f, 2000.f), Vector2::Zero, Vector2(14000.f, 6500.f), 0.15f);
		pAnim->FindAnimation(L"Demian1_attack0_right")->Create(L"Demian1_attack0_right", nullptr, Vector2(12000.f, 1300.f), Vector2(-2000.f, 2000.f), 7, Vector2(2000.f, 2000.f), Vector2::Zero, Vector2(14000.f, 6500.f), 0.15f);
		pAnim->FindAnimation(L"Demian1_attack0_right")->Create(L"Demian1_attack0_right", nullptr, Vector2(12000.f, 2600.f), Vector2(-2000.f, 2000.f), 7, Vector2(2000.f, 2000.f), Vector2::Zero, Vector2(14000.f, 6500.f), 0.15f);
		pAnim->FindAnimation(L"Demian1_attack0_right")->Create(L"Demian1_attack0_right", nullptr, Vector2(12000.f, 3900.f), Vector2(-2000.f, 2000.f), 7, Vector2(2000.f, 2000.f), Vector2::Zero, Vector2(14000.f, 6500.f), 0.15f);
		pAnim->FindAnimation(L"Demian1_attack0_right")->Create(L"Demian1_attack0_right", nullptr, Vector2(12000.f, 5200.f), Vector2(-2000.f, 2000.f), 7, Vector2(2000.f, 2000.f), Vector2::Zero, Vector2(14000.f, 6500.f), 0.15f);

		pAnim->Create(L"Demian1_attack1_right", nullptr, Vector2(12000.f, 0.f), Vector2(-2000.f, 2000.f), 7, Vector2(2000.f, 2000.f), Vector2::Zero, Vector2(14000.f, 7800.f), 0.15f);
		pAnim->FindAnimation(L"Demian1_attack1_right")->Create(L"Demian1_attack1_right", nullptr, Vector2(12000.f, 1300.f), Vector2(-2000.f, 2000.f), 7, Vector2(2000.f, 2000.f), Vector2::Zero, Vector2(14000.f, 7800.f), 0.15f);
		pAnim->FindAnimation(L"Demian1_attack1_right")->Create(L"Demian1_attack1_right", nullptr, Vector2(12000.f, 2600.f), Vector2(-2000.f, 2000.f), 7, Vector2(2000.f, 2000.f), Vector2::Zero, Vector2(14000.f, 7800.f), 0.15f);
		pAnim->FindAnimation(L"Demian1_attack1_right")->Create(L"Demian1_attack1_right", nullptr, Vector2(12000.f, 3900.f), Vector2(-2000.f, 2000.f), 7, Vector2(2000.f, 2000.f), Vector2::Zero, Vector2(14000.f, 7800.f), 0.15f);
		pAnim->FindAnimation(L"Demian1_attack1_right")->Create(L"Demian1_attack1_right", nullptr, Vector2(12000.f, 5200.f), Vector2(-2000.f, 2000.f), 7, Vector2(2000.f, 2000.f), Vector2::Zero, Vector2(14000.f, 7800.f), 0.15f);
		pAnim->FindAnimation(L"Demian1_attack1_right")->Create(L"Demian1_attack1_right", nullptr, Vector2(12000.f, 6500.f), Vector2(-2000.f, 2000.f), 6, Vector2(2000.f, 2000.f), Vector2::Zero, Vector2(14000.f, 7800.f), 0.15f);
		
		pAnim->Create(L"Demian1_attack2_right", nullptr, Vector2(12000.f, 0.f), Vector2(-2000.f, 2000.f), 7, Vector2(2000.f, 2000.f), Vector2::Zero, Vector2(14000.f, 7800.f), 0.15f);
		pAnim->FindAnimation(L"Demian1_attack2_right")->Create(L"Demian1_attack2_right", nullptr, Vector2(12000.f, 1300.f), Vector2(-2000.f, 2000.f), 7, Vector2(2000.f, 2000.f), Vector2::Zero, Vector2(14000.f, 7800.f), 0.15f);
		pAnim->FindAnimation(L"Demian1_attack2_right")->Create(L"Demian1_attack2_right", nullptr, Vector2(12000.f, 2600.f), Vector2(-2000.f, 2000.f), 7, Vector2(2000.f, 2000.f), Vector2::Zero, Vector2(14000.f, 7800.f), 0.15f);
		pAnim->FindAnimation(L"Demian1_attack2_right")->Create(L"Demian1_attack2_right", nullptr, Vector2(12000.f, 3900.f), Vector2(-2000.f, 2000.f), 7, Vector2(2000.f, 2000.f), Vector2::Zero, Vector2(14000.f, 7800.f), 0.15f);
		pAnim->FindAnimation(L"Demian1_attack2_right")->Create(L"Demian1_attack2_right", nullptr, Vector2(12000.f, 5200.f), Vector2(-2000.f, 2000.f), 7, Vector2(2000.f, 2000.f), Vector2::Zero, Vector2(14000.f, 7800.f), 0.15f);
		pAnim->FindAnimation(L"Demian1_attack2_right")->Create(L"Demian1_attack2_right", nullptr, Vector2(12000.f, 6500.f), Vector2(-2000.f, 2000.f), 4, Vector2(2000.f, 2000.f), Vector2::Zero, Vector2(14000.f, 7800.f), 0.15f);
	

		pAnim->Create(L"Demian1_attack3_right", nullptr, Vector2(12000.f, 0.f), Vector2(-2000.f, 2000.f), 7, Vector2(2000.f, 2000.f), Vector2::Zero, Vector2(14000.f, 6500.f), 0.15f);
		pAnim->FindAnimation(L"Demian1_attack3_right")->Create(L"Demian1_attack3_right", nullptr, Vector2(12000.f, 1300.f), Vector2(-2000.f, 2000.f), 7, Vector2(2000.f, 2000.f), Vector2::Zero, Vector2(14000.f, 6500.f), 0.15f);
		pAnim->FindAnimation(L"Demian1_attack3_right")->Create(L"Demian1_attack3_right", nullptr, Vector2(12000.f, 2600.f), Vector2(-2000.f, 2000.f), 7, Vector2(2000.f, 2000.f), Vector2::Zero, Vector2(14000.f, 6500.f), 0.15f);
		for (int i = 0; i < 3; ++i)
		{
			for (int j = 0; j < 10; ++j)
				pAnim->FindAnimation(L"Demian1_attack3_right")->Create(L"Demian1_attack3_right", nullptr, Vector2(4000.f, 2600.f), Vector2(-2000.f, 2000.f), 3, Vector2(2000.f, 2000.f), Vector2::Zero, Vector2(14000.f, 6500.f), 0.15f);
		}
		pAnim->FindAnimation(L"Demian1_attack3_right")->Create(L"Demian1_attack3_right", nullptr, Vector2(12000.f, 3900.f), Vector2(-2000.f, 2000.f), 7, Vector2(2000.f, 2000.f), Vector2::Zero, Vector2(14000.f, 6500.f), 0.15f);
		pAnim->FindAnimation(L"Demian1_attack3_right")->Create(L"Demian1_attack3_right", nullptr, Vector2(12000.f, 5200.f), Vector2(-2000.f, 2000.f), 7, Vector2(2000.f, 2000.f), Vector2::Zero, Vector2(14000.f, 6500.f), 0.15f);


		for (int i = 0; i < 6; ++i)
		{
			for (int j = (int)eKeyCode::UP; j <= (int)eKeyCode::RIGHT; ++j)
			{
				InputObject* pInputObj = new InputObject();
				pInputObj->CreateInputObject((eKeyCode)j);
				ObjectPoolManager::AddObjectPool(pInputObj->GetName(), pInputObj);
			}
		}

		DemianSword* pSword = new DemianSword();
		pSword->SetName(L"demianSword");
		ObjectPoolManager::AddObjectPool(pSword->GetName(), pSword);

		SwordExplode* pExplode = new SwordExplode();
		pExplode->SetName(L"SwordExplode");
		ObjectPoolManager::AddObjectPool(pExplode->GetName(), pExplode);

		//키입력 오브젝트
		for (int i = 0; i < 5; ++i)
		{
			DemianKeyAttack* pKeyAttack = new DemianKeyAttack();
			pKeyAttack->SetName(L"KeyAttackObj");
			ObjectPoolManager::AddObjectPool(pKeyAttack->GetName(), pKeyAttack);
		}

		//데미안 불덩이들 소환 오브젝트
		SpawnMonsterAttack* pSpawnObj = new SpawnMonsterAttack();
		pSpawnObj->SetName(L"SpawnObj");
		ObjectPoolManager::AddObjectPool(pSpawnObj->GetName(), pSpawnObj);

		for (int i = 0; i < 4; ++i)
		{
			DemianExplode* pAttack0 = new DemianExplode();
			pAttack0->SetName(L"Demian_attack0");
			ObjectPoolManager::AddObjectPool(pAttack0->GetName(), pAttack0);
		}

		MonsterAttackObject* pAttack1 = new MonsterAttackObject();
		pAttack1->SetName(L"Demian_attack1");
		ObjectPoolManager::AddObjectPool(pAttack1->GetName(), pAttack1);


		MonsterAttackObject* pAttack2 = new MonsterAttackObject();
		pAttack2->SetName(L"Demian_attack2");
		ObjectPoolManager::AddObjectPool(pAttack2->GetName(), pAttack2);

		for (int i = 0; i < 20; ++i)
		{
			DemianFire0* pAttack3 = new DemianFire0();
			pAttack3->SetName(L"Demian_attack3");
			ObjectPoolManager::AddObjectPool(pAttack3->GetName(), pAttack3);
		}

		m_strCurStateName.clear();

	}

	Demian::~Demian()
	{
		
	}

	void Demian::Initialize()
	{
		std::shared_ptr<Texture> pNormal = Resources::Find<Texture>(L"DemianNormal");
		std::shared_ptr<Texture> pDead = Resources::Find<Texture>(L"DemianDead");
		std::shared_ptr<Texture> pAttack0 = Resources::Find<Texture>(L"Demian_attack0");
		std::shared_ptr<Texture> pAttack1 = Resources::Find<Texture>(L"Demian_attack1");
		std::shared_ptr<Texture> pAttack2 = Resources::Find<Texture>(L"Demian_attack2");
		std::shared_ptr<Texture> pAttack3 = Resources::Find<Texture>(L"Demian_attack3");

		Animator* pAnim = GetComponent<Animator>();
		pAnim->SetTextureBothDir(L"Demian1_stand", pNormal);
		pAnim->SetTextureBothDir(L"Demian1_dead", pDead);
		pAnim->SetTextureBothDir(L"Demian1_attack0", pAttack0);
		pAnim->SetTextureBothDir(L"Demian1_attack1", pAttack1);
		pAnim->SetTextureBothDir(L"Demian1_attack2", pAttack2);
		pAnim->SetTextureBothDir(L"Demian1_attack3", pAttack3);
	}
	void Demian::Update()
	{
		
	}
	void Demian::LateUpdate()
	{
		Monster::LateUpdate();
	}
	void Demian::Render()
	{
		Monster::Render();
	}

	void Demian::UpdateState(const wstring& _strStateName, int _iState)
	{
		Monster::UpdateState(_strStateName, _iState);
	}
	
}