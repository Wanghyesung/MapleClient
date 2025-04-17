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
	
		std::shared_ptr<Texture> pNormal = Resources::Find<Texture>(L"DemianNormal");
		std::shared_ptr<Texture> pDead = Resources::Find<Texture>(L"DemianDead");
		std::shared_ptr<Texture> pAttack0 = Resources::Find<Texture>(L"Demian_attack0");
		std::shared_ptr<Texture> pAttack1 = Resources::Find<Texture>(L"Demian_attack1");
		std::shared_ptr<Texture> pAttack2 = Resources::Find<Texture>(L"Demian_attack2");
		std::shared_ptr<Texture> pAttack3 = Resources::Find<Texture>(L"Demian_attack3");

		pAttack0->BindShaderResource(eShaderStage::PS, 12);
		pAttack1->BindShaderResource(eShaderStage::PS, 12);
		pAttack2->BindShaderResource(eShaderStage::PS, 12);
		pAttack3->BindShaderResource(eShaderStage::PS, 12);
		pDead->BindShaderResource(eShaderStage::PS, 12);

		Animator* pAnim = AddComponent<Animator>();
		pAnim->Create(L"Demian1_stand_left", pNormal, Vector2(0.f, 0.f), Vector2(2000.f, 2000.f), 7, Vector2(2000.f, 2000.f), Vector2::Zero, 0.15f);

		pAnim->Create(L"Demian1_dead_left", pDead, Vector2(0.f, 0.f), Vector2(2000.f, 2000.f), 7, Vector2(2000.f, 2000.f), Vector2::Zero, 0.15f);
		pAnim->FindAnimation(L"Demian1_dead_left")->Create(L"Demian1_dead_left", pDead, Vector2(0.f, 1300.f), Vector2(2000.f, 2000.f), 6, Vector2(2000.f, 2000.f), Vector2::Zero, 0.15f);
		for (int i = 0; i < 3; ++i)
		{
			pAnim->FindAnimation(L"Demian1_dead_left")->Create(L"Demian1_dead_left", pDead, Vector2(0.f, 2600.f), Vector2(2000.f, 2000.f), 7, Vector2(2000.f, 2000.f), Vector2::Zero, 0.15f);
			pAnim->FindAnimation(L"Demian1_dead_left")->Create(L"Demian1_dead_left", pDead, Vector2(0.f, 3900.f), Vector2(2000.f, 2000.f), 5, Vector2(2000.f, 2000.f), Vector2::Zero, 0.15f);
		}

		pAnim->Create(L"Demian1_attack0_left", pAttack0, Vector2(0.f, 0.f), Vector2(2000.f, 2000.f), 7, Vector2(2000.f, 2000.f), Vector2::Zero, 0.15f);
		pAnim->FindAnimation(L"Demian1_attack0_left")->Create(L"Demian1_attack0_left",pAttack0, Vector2(0.f, 1300.f), Vector2(2000.f, 2000.f), 7, Vector2(2000.f, 2000.f), Vector2::Zero, 0.15f);
		pAnim->FindAnimation(L"Demian1_attack0_left")->Create(L"Demian1_attack0_left", pAttack0, Vector2(0.f, 2600.f), Vector2(2000.f, 2000.f), 7, Vector2(2000.f, 2000.f), Vector2::Zero, 0.15f);
		pAnim->FindAnimation(L"Demian1_attack0_left")->Create(L"Demian1_attack0_left", pAttack0, Vector2(0.f, 3900.f), Vector2(2000.f, 2000.f), 7, Vector2(2000.f, 2000.f), Vector2::Zero, 0.15f);
		pAnim->FindAnimation(L"Demian1_attack0_left")->Create(L"Demian1_attack0_left", pAttack0, Vector2(0.f, 5200.f), Vector2(2000.f, 2000.f), 7, Vector2(2000.f, 2000.f), Vector2::Zero, 0.15f);

		pAnim->Create(L"Demian1_attack1_left", pAttack1, Vector2(0.f, 0.f), Vector2(2000.f, 2000.f), 7, Vector2(2000.f, 2000.f), Vector2::Zero, 0.15f);
		pAnim->FindAnimation(L"Demian1_attack1_left")->Create(L"Demian1_attack1_left", pAttack1, Vector2(0.f, 1300.f), Vector2(2000.f, 2000.f), 7, Vector2(2000.f, 2000.f), Vector2::Zero, 0.15f);
		pAnim->FindAnimation(L"Demian1_attack1_left")->Create(L"Demian1_attack1_left", pAttack1, Vector2(0.f, 2600.f), Vector2(2000.f, 2000.f), 7, Vector2(2000.f, 2000.f), Vector2::Zero, 0.15f);
		pAnim->FindAnimation(L"Demian1_attack1_left")->Create(L"Demian1_attack1_left", pAttack1, Vector2(0.f, 3900.f), Vector2(2000.f, 2000.f), 7, Vector2(2000.f, 2000.f), Vector2::Zero, 0.15f);
		pAnim->FindAnimation(L"Demian1_attack1_left")->Create(L"Demian1_attack1_left", pAttack1, Vector2(0.f, 5200.f), Vector2(2000.f, 2000.f), 7, Vector2(2000.f, 2000.f), Vector2::Zero, 0.15f);
		pAnim->FindAnimation(L"Demian1_attack1_left")->Create(L"Demian1_attack1_left", pAttack1, Vector2(0.f, 6500.f), Vector2(2000.f, 2000.f), 6, Vector2(2000.f, 2000.f), Vector2::Zero, 0.15f);

		pAnim->Create(L"Demian1_attack2_left", pAttack2, Vector2(0.f, 0.f), Vector2(2000.f, 2000.f), 7, Vector2(2000.f, 2000.f), Vector2::Zero, 0.15f);
		pAnim->FindAnimation(L"Demian1_attack2_left")->Create(L"Demian1_attack2_left", pAttack2, Vector2(0.f, 1300.f), Vector2(2000.f, 2000.f), 7, Vector2(2000.f, 2000.f), Vector2::Zero, 0.15f);
		pAnim->FindAnimation(L"Demian1_attack2_left")->Create(L"Demian1_attack2_left", pAttack2, Vector2(0.f, 2600.f), Vector2(2000.f, 2000.f), 7, Vector2(2000.f, 2000.f), Vector2::Zero, 0.15f);
		pAnim->FindAnimation(L"Demian1_attack2_left")->Create(L"Demian1_attack2_left", pAttack2, Vector2(0.f, 3900.f), Vector2(2000.f, 2000.f), 7, Vector2(2000.f, 2000.f), Vector2::Zero, 0.15f);
		pAnim->FindAnimation(L"Demian1_attack2_left")->Create(L"Demian1_attack2_left", pAttack2, Vector2(0.f, 5200.f), Vector2(2000.f, 2000.f), 7, Vector2(2000.f, 2000.f), Vector2::Zero, 0.15f);
		pAnim->FindAnimation(L"Demian1_attack2_left")->Create(L"Demian1_attack2_left", pAttack2, Vector2(0.f, 6500.f), Vector2(2000.f, 2000.f), 4, Vector2(2000.f, 2000.f), Vector2::Zero, 0.15f);
	

		pAnim->Create(L"Demian1_attack3_left", pAttack3, Vector2(0.f, 0.f), Vector2(2000.f, 2000.f), 7, Vector2(2000.f, 2000.f), Vector2::Zero, 0.15f);
		pAnim->FindAnimation(L"Demian1_attack3_left")->Create(L"Demian1_attack3_left", pAttack3, Vector2(0.f, 1300.f), Vector2(2000.f, 2000.f), 7, Vector2(2000.f, 2000.f), Vector2::Zero, 0.15f);
		pAnim->FindAnimation(L"Demian1_attack3_left")->Create(L"Demian1_attack3_left", pAttack3, Vector2(0.f, 2600.f), Vector2(2000.f, 2000.f), 7, Vector2(2000.f, 2000.f), Vector2::Zero, 0.15f);
		for (int i = 0; i < 3; ++i)
		{
			//이미지 반복
			for (int j = 0; j < 10; ++j)
				pAnim->FindAnimation(L"Demian1_attack3_left")->Create(L"Demian1_attack3_left", pAttack3, Vector2(8000.f, 2600.f), Vector2(2000.f, 2000.f), 3, Vector2(2000.f, 2000.f), Vector2::Zero, 0.15f);
		}
		pAnim->FindAnimation(L"Demian1_attack3_left")->Create(L"Demian1_attack3_left", pAttack3, Vector2(0.f, 3900.f), Vector2(2000.f, 2000.f), 7, Vector2(2000.f, 2000.f), Vector2::Zero, 0.15f);
		pAnim->FindAnimation(L"Demian1_attack3_left")->Create(L"Demian1_attack3_left", pAttack3, Vector2(0.f, 5200.f), Vector2(2000.f, 2000.f), 7, Vector2(2000.f, 2000.f), Vector2::Zero, 0.15f);

		pAnim->Create(L"Demian1_stand_right", pNormal, Vector2(12000.f, 0.f), Vector2(-2000.f, 2000.f), 7, Vector2(2000.f, 2000.f), Vector2::Zero, 0.15f);
		
		pAnim->Create(L"Demian1_dead_right", pDead, Vector2(12000.f, 0.f), Vector2(12000.f, 1300.f), 7, Vector2(-2000.f, 2000.f), Vector2::Zero, 0.15f);
		pAnim->FindAnimation(L"Demian1_dead_right")->Create(L"Demian1_dead_right", pDead, Vector2(12000.f, 1300.f), Vector2(-2000.f, 2000.f), 6, Vector2(2000.f, 2000.f), Vector2::Zero, 0.15f);
		for (int i = 0; i < 3; ++i)
		{
			pAnim->FindAnimation(L"Demian1_dead_right")->Create(L"Demian1_dead_right", pDead, Vector2(12000.f, 2600.f), Vector2(-2000.f, 2000.f), 7, Vector2(2000.f, 2000.f), Vector2::Zero, 0.15f);
			pAnim->FindAnimation(L"Demian1_dead_right")->Create(L"Demian1_dead_right", pDead, Vector2(12000.f, 3900.f), Vector2(-2000.f, 2000.f), 5, Vector2(2000.f, 2000.f), Vector2::Zero, 0.15f);
		}

		pAnim->Create(L"Demian1_attack0_right", pAttack0, Vector2(12000.f, 0.f), Vector2(-2000.f, 2000.f), 7, Vector2(2000.f, 2000.f), Vector2::Zero, 0.15f);
		pAnim->FindAnimation(L"Demian1_attack0_right")->Create(L"Demian1_attack0_right", pAttack0, Vector2(12000.f, 1300.f), Vector2(-2000.f, 2000.f), 7, Vector2(2000.f, 2000.f), Vector2::Zero, 0.15f);
		pAnim->FindAnimation(L"Demian1_attack0_right")->Create(L"Demian1_attack0_right", pAttack0, Vector2(12000.f, 2600.f), Vector2(-2000.f, 2000.f), 7, Vector2(2000.f, 2000.f), Vector2::Zero, 0.15f);
		pAnim->FindAnimation(L"Demian1_attack0_right")->Create(L"Demian1_attack0_right", pAttack0, Vector2(12000.f, 3900.f), Vector2(-2000.f, 2000.f), 7, Vector2(2000.f, 2000.f), Vector2::Zero, 0.15f);
		pAnim->FindAnimation(L"Demian1_attack0_right")->Create(L"Demian1_attack0_right", pAttack0, Vector2(12000.f, 5200.f), Vector2(-2000.f, 2000.f), 7, Vector2(2000.f, 2000.f), Vector2::Zero, 0.15f);

		pAnim->Create(L"Demian1_attack1_right", pAttack1, Vector2(12000.f, 0.f), Vector2(-2000.f, 2000.f), 7, Vector2(2000.f, 2000.f), Vector2::Zero, 0.15f);
		pAnim->FindAnimation(L"Demian1_attack1_right")->Create(L"Demian1_attack1_right", pAttack1, Vector2(12000.f, 1300.f), Vector2(-2000.f, 2000.f), 7, Vector2(2000.f, 2000.f), Vector2::Zero, 0.15f);
		pAnim->FindAnimation(L"Demian1_attack1_right")->Create(L"Demian1_attack1_right", pAttack1, Vector2(12000.f, 2600.f), Vector2(-2000.f, 2000.f), 7, Vector2(2000.f, 2000.f), Vector2::Zero, 0.15f);
		pAnim->FindAnimation(L"Demian1_attack1_right")->Create(L"Demian1_attack1_right", pAttack1, Vector2(12000.f, 3900.f), Vector2(-2000.f, 2000.f), 7, Vector2(2000.f, 2000.f), Vector2::Zero, 0.15f);
		pAnim->FindAnimation(L"Demian1_attack1_right")->Create(L"Demian1_attack1_right", pAttack1, Vector2(12000.f, 5200.f), Vector2(-2000.f, 2000.f), 7, Vector2(2000.f, 2000.f), Vector2::Zero, 0.15f);
		pAnim->FindAnimation(L"Demian1_attack1_right")->Create(L"Demian1_attack1_right", pAttack1, Vector2(12000.f, 6500.f), Vector2(-2000.f, 2000.f), 6, Vector2(2000.f, 2000.f), Vector2::Zero, 0.15f);
		
		pAnim->Create(L"Demian1_attack2_right", pAttack2, Vector2(12000.f, 0.f), Vector2(-2000.f, 2000.f), 7, Vector2(2000.f, 2000.f), Vector2::Zero, 0.15f);
		pAnim->FindAnimation(L"Demian1_attack2_right")->Create(L"Demian1_attack2_right", pAttack2, Vector2(12000.f, 1300.f), Vector2(-2000.f, 2000.f), 7, Vector2(2000.f, 2000.f), Vector2::Zero, 0.15f);
		pAnim->FindAnimation(L"Demian1_attack2_right")->Create(L"Demian1_attack2_right", pAttack2, Vector2(12000.f, 2600.f), Vector2(-2000.f, 2000.f), 7, Vector2(2000.f, 2000.f), Vector2::Zero, 0.15f);
		pAnim->FindAnimation(L"Demian1_attack2_right")->Create(L"Demian1_attack2_right", pAttack2, Vector2(12000.f, 3900.f), Vector2(-2000.f, 2000.f), 7, Vector2(2000.f, 2000.f), Vector2::Zero, 0.15f);
		pAnim->FindAnimation(L"Demian1_attack2_right")->Create(L"Demian1_attack2_right", pAttack2, Vector2(12000.f, 5200.f), Vector2(-2000.f, 2000.f), 7, Vector2(2000.f, 2000.f), Vector2::Zero, 0.15f);
		pAnim->FindAnimation(L"Demian1_attack2_right")->Create(L"Demian1_attack2_right", pAttack2, Vector2(12000.f, 6500.f), Vector2(-2000.f, 2000.f), 4, Vector2(2000.f, 2000.f), Vector2::Zero, 0.15f);
	

		pAnim->Create(L"Demian1_attack3_right", pAttack3, Vector2(12000.f, 0.f), Vector2(-2000.f, 2000.f), 7, Vector2(2000.f, 2000.f), Vector2::Zero, 0.15f);
		pAnim->FindAnimation(L"Demian1_attack3_right")->Create(L"Demian1_attack3_right", pAttack3, Vector2(12000.f, 1300.f), Vector2(-2000.f, 2000.f), 7, Vector2(2000.f, 2000.f), Vector2::Zero, 0.15f);
		pAnim->FindAnimation(L"Demian1_attack3_right")->Create(L"Demian1_attack3_right", pAttack3, Vector2(12000.f, 2600.f), Vector2(-2000.f, 2000.f), 7, Vector2(2000.f, 2000.f), Vector2::Zero, 0.15f);
		for (int i = 0; i < 3; ++i)
		{
			//이미지 반복
			for (int j = 0; j < 10; ++j)
				pAnim->FindAnimation(L"Demian1_attack3_right")->Create(L"Demian1_attack3_right", pAttack3, Vector2(4000.f, 2600.f), Vector2(-2000.f, 2000.f), 3, Vector2(2000.f, 2000.f), Vector2::Zero, 0.15f);
		}
		pAnim->FindAnimation(L"Demian1_attack3_right")->Create(L"Demian1_attack3_right", pAttack3, Vector2(12000.f, 3900.f), Vector2(-2000.f, 2000.f), 7, Vector2(2000.f, 2000.f), Vector2::Zero, 0.15f);
		pAnim->FindAnimation(L"Demian1_attack3_right")->Create(L"Demian1_attack3_right", pAttack3, Vector2(12000.f, 5200.f), Vector2(-2000.f, 2000.f), 7, Vector2(2000.f, 2000.f), Vector2::Zero, 0.15f);

	}
	Demian::~Demian()
	{
		
	}

	void Demian::Initialize()
	{
		
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
	
}