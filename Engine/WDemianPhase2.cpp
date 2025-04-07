#include "WDemianPhase2.h"
#include "WAnimator.h"
#include "WResources.h"
#include "WSpawnMonsterAttack.h"
#include "WDemianFire1.h"
#include "WDemianFire2.h"
#include "WEffect.h"
#include "WEventManager.h"
#include "WMonsterMoveAttack.h"
#include "WDemianSpear0.h"
#include "WDemianSpear1.h"
#include "WDemianVine.h"
#include "WDemianCircle.h"
#include "WSceneManger.h"

namespace W
{
	DemianPhase2::DemianPhase2()
	{
		SetName(L"Demian2");

		MeshRenderer* pRenderer = AddComponent<MeshRenderer>();
		pRenderer->SetMesh(Resources::Find<Mesh>(L"RectMesh"));


		std::shared_ptr<Material> pMater = std::make_shared<Material>();
		pMater->SetRenderinMode(eRenderingMode::Transparent);
		pMater->SetShader(Resources::Find<Shader>(L"MonsterShader"));
		Resources::Insert(L"DemianMater", pMater);

		pRenderer->SetMaterial(pMater);
	
		std::shared_ptr<Texture> pNormal2 = Resources::Find<Texture>(L"Demian2Normal");
		std::shared_ptr<Texture> pDead2 = Resources::Find<Texture>(L"Demian2Dead");
		std::shared_ptr<Texture> pAttack20 = Resources::Find<Texture>(L"Demian2_attack0");
		std::shared_ptr<Texture> pAttack21 = Resources::Find<Texture>(L"Demian2_attack1");
		std::shared_ptr<Texture> pAttack22 = Resources::Find<Texture>(L"Demian2_attack2");
		std::shared_ptr<Texture> pAttack23 = Resources::Find<Texture>(L"Demian2_attack3");
		std::shared_ptr<Texture> pAttack24 = Resources::Find<Texture>(L"Demian2_attack4");
		std::shared_ptr<Texture> pAttack25 = Resources::Find<Texture>(L"Demian2_attack5");

		Animator* pAnim = AddComponent<Animator>();
		//////////////////ÆäÀÌÁî 2///////////////////////
		pAnim->Create(L"Demian2_stand_left", pNormal2, Vector2(0.f, 0.f), Vector2(2000.f, 2000.f), 7, Vector2(2000.f, 2000.f), Vector2::Zero, 0.15f);

		pAnim->Create(L"Demian2_dead_left", pDead2, Vector2(0.f, 0.f), Vector2(2000.f, 2000.f), 7, Vector2(2000.f, 2000.f), Vector2::Zero, 0.15f);
		pAnim->FindAnimation(L"Demian2_dead_left")->Create(L"Demian2_dead_left", pDead2, Vector2(0.f, 1300.f), Vector2(2000.f, 2000.f), 7, Vector2(2000.f, 2000.f), Vector2::Zero, 0.15f);
		pAnim->FindAnimation(L"Demian2_dead_left")->Create(L"Demian2_dead_left", pDead2, Vector2(0.f, 2600.f), Vector2(2000.f, 2000.f), 7, Vector2(2000.f, 2000.f), Vector2::Zero, 0.15f);
		pAnim->FindAnimation(L"Demian2_dead_left")->Create(L"Demian2_dead_left", pDead2, Vector2(0.f, 3900.f), Vector2(2000.f, 2000.f), 5, Vector2(2000.f, 2000.f), Vector2::Zero, 0.15f);


		pAnim->Create(L"Demian2_attack0_left", pAttack20, Vector2(0.f, 0.f), Vector2(2000.f, 2000.f), 7, Vector2(2000.f, 2000.f), Vector2::Zero, 0.15f);
		pAnim->FindAnimation(L"Demian2_attack0_left")->Create(L"Demian2_attack0_left", pAttack20, Vector2(0.f, 1300.f), Vector2(2000.f, 2000.f), 7, Vector2(2000.f, 2000.f), Vector2::Zero, 0.15f);

		pAnim->Create(L"Demian2_attack1_left", pAttack21, Vector2(0.f, 0.f), Vector2(2000.f, 2000.f), 7, Vector2(2000.f, 2000.f), Vector2::Zero, 0.15f);
		for (int i = 0; i < 8; ++i)
			pAnim->FindAnimation(L"Demian2_attack1_left")->Create(L"Demian2_attack1_left", pAttack21, Vector2(0.f, 1300.f), Vector2(2000.f, 2000.f), 7, Vector2(2000.f, 2000.f), Vector2::Zero, 0.15f);
		pAnim->FindAnimation(L"Demian2_attack1_left")->Create(L"Demian2_attack1_left", pAttack21, Vector2(0.f, 2600.f), Vector2(2000.f, 2000.f), 3, Vector2(2000.f, 2000.f), Vector2::Zero, 0.15f);

		pAnim->Create(L"Demian2_attack2_left", pAttack22, Vector2(0.f, 0.f), Vector2(2000.f, 2000.f), 7, Vector2(2000.f, 2000.f), Vector2::Zero, 0.12f);
		pAnim->FindAnimation(L"Demian2_attack2_left")->Create(L"Demian2_attack2_left", pAttack22, Vector2(0.f, 1300.f), Vector2(2000.f, 2000.f), 7, Vector2(2000.f, 2000.f), Vector2::Zero, 0.12f);
		pAnim->FindAnimation(L"Demian2_attack2_left")->Create(L"Demian2_attack2_left", pAttack22, Vector2(0.f, 2600.f), Vector2(2000.f, 2000.f), 7, Vector2(2000.f, 2000.f), Vector2::Zero, 0.12f);
		pAnim->FindAnimation(L"Demian2_attack2_left")->Create(L"Demian2_attack2_left", pAttack22, Vector2(0.f, 3900.f), Vector2(2000.f, 2000.f), 7, Vector2(2000.f, 2000.f), Vector2::Zero, 0.12f);
		pAnim->FindAnimation(L"Demian2_attack2_left")->Create(L"Demian2_attack2_left", pAttack22, Vector2(0.f, 5200.f), Vector2(2000.f, 2000.f), 7, Vector2(2000.f, 2000.f), Vector2::Zero, 0.12f);
		pAnim->FindAnimation(L"Demian2_attack2_left")->Create(L"Demian2_attack2_left", pAttack22, Vector2(0.f, 6500.f), Vector2(2000.f, 2000.f), 7, Vector2(2000.f, 2000.f), Vector2::Zero, 0.12f);
		pAnim->FindAnimation(L"Demian2_attack2_left")->Create(L"Demian2_attack2_left", pAttack22, Vector2(0.f, 7800.f), Vector2(2000.f, 2000.f), 7, Vector2(2000.f, 2000.f), Vector2::Zero, 0.12f);

		pAnim->Create(L"Demian2_attack3_left", pAttack23, Vector2(0.f, 0.f), Vector2(2000.f, 2000.f), 7, Vector2(2000.f, 2000.f), Vector2::Zero, 0.15f);
		pAnim->FindAnimation(L"Demian2_attack3_left")->Create(L"Demian2_attack3_left", pAttack23, Vector2(0.f, 1300.f), Vector2(2000.f, 2000.f), 7, Vector2(2000.f, 2000.f), Vector2::Zero, 0.15f);
		pAnim->FindAnimation(L"Demian2_attack3_left")->Create(L"Demian2_attack3_left", pAttack23, Vector2(0.f, 2600.f), Vector2(2000.f, 2000.f), 7, Vector2(2000.f, 2000.f), Vector2::Zero, 0.15f);
		pAnim->FindAnimation(L"Demian2_attack3_left")->Create(L"Demian2_attack3_left", pAttack23, Vector2(0.f, 3900.f), Vector2(2000.f, 2000.f), 7, Vector2(2000.f, 2000.f), Vector2::Zero, 0.15f);
		pAnim->FindAnimation(L"Demian2_attack3_left")->Create(L"Demian2_attack3_left", pAttack23, Vector2(0.f, 5200.f), Vector2(2000.f, 2000.f), 7, Vector2(2000.f, 2000.f), Vector2::Zero, 0.15f);
		pAnim->FindAnimation(L"Demian2_attack3_left")->Create(L"Demian2_attack3_left", pAttack23, Vector2(0.f, 6500.f), Vector2(2000.f, 2000.f), 7, Vector2(2000.f, 2000.f), Vector2::Zero, 0.15f);
		pAnim->FindAnimation(L"Demian2_attack3_left")->Create(L"Demian2_attack3_left", pAttack23, Vector2(0.f, 7800.f), Vector2(2000.f, 2000.f), 7, Vector2(2000.f, 2000.f), Vector2::Zero, 0.15f);

		pAnim->Create(L"Demian2_attack4_left", pAttack24, Vector2(0.f, 0.f), Vector2(2000.f, 2000.f), 7, Vector2(2000.f, 2000.f), Vector2::Zero, 0.15f);
		pAnim->FindAnimation(L"Demian2_attack4_left")->Create(L"Demian2_attack4_left", pAttack24, Vector2(0.f, 1300.f), Vector2(2000.f, 2000.f), 7, Vector2(2000.f, 2000.f), Vector2::Zero, 0.15f);
		for(int i = 0; i<8; ++i)
			pAnim->FindAnimation(L"Demian2_attack4_left")->Create(L"Demian2_attack4_left", pAttack24, Vector2(0.f, 2600.f), Vector2(2000.f, 2000.f), 7, Vector2(2000.f, 2000.f), Vector2::Zero, 0.15f);
		pAnim->FindAnimation(L"Demian2_attack4_left")->Create(L"Demian2_attack4_left", pAttack24, Vector2(0.f, 3900.f), Vector2(2000.f, 2000.f), 7, Vector2(2000.f, 2000.f), Vector2::Zero, 0.15f);
		pAnim->FindAnimation(L"Demian2_attack4_left")->Create(L"Demian2_attack4_left", pAttack24, Vector2(0.f, 5200.f), Vector2(2000.f, 2000.f), 7, Vector2(2000.f, 2000.f), Vector2::Zero, 0.15f);
		pAnim->FindAnimation(L"Demian2_attack4_left")->Create(L"Demian2_attack4_left", pAttack24, Vector2(0.f, 6500.f), Vector2(2000.f, 2000.f), 7, Vector2(2000.f, 2000.f), Vector2::Zero, 0.15f);
		pAnim->FindAnimation(L"Demian2_attack4_left")->Create(L"Demian2_attack4_left", pAttack24, Vector2(0.f, 7800.f), Vector2(2000.f, 2000.f), 3, Vector2(2000.f, 2000.f), Vector2::Zero, 0.15f);

		pAnim->Create(L"Demian2_attack5_left", pAttack25, Vector2(0.f, 0.f), Vector2(2000.f, 2000.f), 7, Vector2(2000.f, 2000.f), Vector2::Zero, 0.15f);
		for (int i = 0; i < 6; ++i)
			pAnim->FindAnimation(L"Demian2_attack5_left")->Create(L"Demian2_attack5_left", pAttack25, Vector2(0.f, 1300.f), Vector2(2000.f, 2000.f), 7, Vector2(2000.f, 2000.f), Vector2::Zero, 0.15f);
		pAnim->FindAnimation(L"Demian2_attack5_left")->Create(L"Demian2_attack5_left", pAttack25, Vector2(0.f, 2600.f), Vector2(2000.f, 2000.f), 7, Vector2(2000.f, 2000.f), Vector2::Zero, 0.15f);
		pAnim->FindAnimation(L"Demian2_attack5_left")->Create(L"Demian2_attack5_left", pAttack25, Vector2(0.f, 3900.f), Vector2(2000.f, 2000.f), 7, Vector2(2000.f, 2000.f), Vector2::Zero, 0.15f);
		pAnim->FindAnimation(L"Demian2_attack5_left")->Create(L"Demian2_attack5_left", pAttack25, Vector2(0.f, 5200.f), Vector2(2000.f, 2000.f), 7, Vector2(2000.f, 2000.f), Vector2::Zero, 0.15f);
		pAnim->FindAnimation(L"Demian2_attack5_left")->Create(L"Demian2_attack5_left", pAttack25, Vector2(0.f, 6500.f), Vector2(2000.f, 2000.f), 7, Vector2(2000.f, 2000.f), Vector2::Zero, 0.15f);
		pAnim->FindAnimation(L"Demian2_attack5_left")->Create(L"Demian2_attack5_left", pAttack25, Vector2(0.f, 7800.f), Vector2(2000.f, 2000.f), 7, Vector2(2000.f, 2000.f), Vector2::Zero, 0.15f);

		pAnim->Create(L"Demian2_stand_right", pNormal2, Vector2(12000.f, 0.f), Vector2(-2000.f, 2000.f), 7, Vector2(2000.f, 2000.f), Vector2::Zero, 0.15f);

		pAnim->Create(L"Demian2_dead_right", pDead2, Vector2(12000.f, 0.f), Vector2(-2000.f, 2000.f), 7, Vector2(2000.f, 2000.f), Vector2::Zero, 0.15f);
		pAnim->FindAnimation(L"Demian2_dead_right")->Create(L"Demian2_dead_right", pDead2, Vector2(12000.f, 1300.f), Vector2(-2000.f, 2000.f), 7, Vector2(2000.f, 2000.f), Vector2::Zero, 0.15f);
		pAnim->FindAnimation(L"Demian2_dead_right")->Create(L"Demian2_dead_right", pDead2, Vector2(12000.f, 2600.f), Vector2(-2000.f, 2000.f), 7, Vector2(2000.f, 2000.f), Vector2::Zero, 0.15f);
		pAnim->FindAnimation(L"Demian2_dead_right")->Create(L"Demian2_dead_right", pDead2, Vector2(12000.f, 3900.f), Vector2(-2000.f, 2000.f), 5, Vector2(2000.f, 2000.f), Vector2::Zero, 0.15f);


		pAnim->Create(L"Demian2_attack0_right", pAttack20, Vector2(12000.f, 0.f), Vector2(-2000.f, 2000.f), 7, Vector2(2000.f, 2000.f), Vector2::Zero, 0.15f);
		pAnim->FindAnimation(L"Demian2_attack0_right")->Create(L"Demian2_attack0_right", pAttack20, Vector2(12000.f, 1300.f), Vector2(-2000.f, 2000.f), 7, Vector2(2000.f, 2000.f), Vector2::Zero, 0.15f);

		pAnim->Create(L"Demian2_attack1_right", pAttack21, Vector2(12000.f, 0.f), Vector2(-2000.f, 2000.f), 7, Vector2(2000.f, 2000.f), Vector2::Zero, 0.15f);
		for (int i = 0; i < 8; ++i)
			pAnim->FindAnimation(L"Demian2_attack1_right")->Create(L"Demian2_attack1_right", pAttack21, Vector2(12000.f, 1300.f), Vector2(-2000.f, 2000.f), 7, Vector2(2000.f, 2000.f), Vector2::Zero, 0.15f);
		pAnim->FindAnimation(L"Demian2_attack1_right")->Create(L"Demian2_attack1_right", pAttack21, Vector2(12000.f, 2600.f), Vector2(-2000.f, 2000.f), 3, Vector2(2000.f, 2000.f), Vector2::Zero, 0.15f);

		pAnim->Create(L"Demian2_attack2_right", pAttack22, Vector2(12000.f, 0.f), Vector2(-2000.f, 2000.f), 7, Vector2(2000.f, 2000.f), Vector2::Zero, 0.12f);
		pAnim->FindAnimation(L"Demian2_attack2_right")->Create(L"Demian2_attack2_right", pAttack22, Vector2(12000.f, 1300.f), Vector2(-2000.f, 2000.f), 7, Vector2(2000.f, 2000.f), Vector2::Zero, 0.12f);
		pAnim->FindAnimation(L"Demian2_attack2_right")->Create(L"Demian2_attack2_right", pAttack22, Vector2(12000.f, 2600.f), Vector2(-2000.f, 2000.f), 7, Vector2(2000.f, 2000.f), Vector2::Zero, 0.12f);
		pAnim->FindAnimation(L"Demian2_attack2_right")->Create(L"Demian2_attack2_right", pAttack22, Vector2(12000.f, 3900.f), Vector2(-2000.f, 2000.f), 7, Vector2(2000.f, 2000.f), Vector2::Zero, 0.12f);
		pAnim->FindAnimation(L"Demian2_attack2_right")->Create(L"Demian2_attack2_right", pAttack22, Vector2(12000.f, 5200.f), Vector2(-2000.f, 2000.f), 7, Vector2(2000.f, 2000.f), Vector2::Zero, 0.12f);
		pAnim->FindAnimation(L"Demian2_attack2_right")->Create(L"Demian2_attack2_right", pAttack22, Vector2(12000.f, 6500.f), Vector2(-2000.f, 2000.f), 7, Vector2(2000.f, 2000.f), Vector2::Zero, 0.12f);
		pAnim->FindAnimation(L"Demian2_attack2_right")->Create(L"Demian2_attack2_right", pAttack22, Vector2(12000.f, 7800.f), Vector2(-2000.f, 2000.f), 7, Vector2(2000.f, 2000.f), Vector2::Zero, 0.12f);

		pAnim->Create(L"Demian2_attack3_right", pAttack23, Vector2(12000.f, 0.f), Vector2(-2000.f, 2000.f), 7, Vector2(2000.f, 2000.f), Vector2::Zero, 0.15f);
		pAnim->FindAnimation(L"Demian2_attack3_right")->Create(L"Demian2_attack3_right", pAttack23, Vector2(12000.f, 1300.f), Vector2(-2000.f, 2000.f), 7, Vector2(2000.f, 2000.f), Vector2::Zero, 0.15f);
		pAnim->FindAnimation(L"Demian2_attack3_right")->Create(L"Demian2_attack3_right", pAttack23, Vector2(12000.f, 2600.f), Vector2(-2000.f, 2000.f), 7, Vector2(2000.f, 2000.f), Vector2::Zero, 0.15f);
		pAnim->FindAnimation(L"Demian2_attack3_right")->Create(L"Demian2_attack3_right", pAttack23, Vector2(12000.f, 3900.f), Vector2(-2000.f, 2000.f), 7, Vector2(2000.f, 2000.f), Vector2::Zero, 0.15f);
		pAnim->FindAnimation(L"Demian2_attack3_right")->Create(L"Demian2_attack3_right", pAttack23, Vector2(12000.f, 5200.f), Vector2(-2000.f, 2000.f), 7, Vector2(2000.f, 2000.f), Vector2::Zero, 0.15f);
		pAnim->FindAnimation(L"Demian2_attack3_right")->Create(L"Demian2_attack3_right", pAttack23, Vector2(12000.f, 6500.f), Vector2(-2000.f, 2000.f), 7, Vector2(2000.f, 2000.f), Vector2::Zero, 0.15f);
		pAnim->FindAnimation(L"Demian2_attack3_right")->Create(L"Demian2_attack3_right", pAttack23, Vector2(12000.f, 7800.f), Vector2(-2000.f, 2000.f), 7, Vector2(2000.f, 2000.f), Vector2::Zero, 0.15f);
	

		pAnim->Create(L"Demian2_attack4_right", pAttack24, Vector2(12000.f, 0.f), Vector2(-2000.f, 2000.f), 7, Vector2(2000.f, 2000.f), Vector2::Zero, 0.15f);
		pAnim->FindAnimation(L"Demian2_attack4_right")->Create(L"Demian2_attack4_right", pAttack24, Vector2(12000.f, 1300.f), Vector2(-2000.f, 2000.f), 7, Vector2(2000.f, 2000.f), Vector2::Zero, 0.15f);
		for(int i = 0; i<9; ++i)
			pAnim->FindAnimation(L"Demian2_attack4_right")->Create(L"Demian2_attack4_right", pAttack24, Vector2(12000.f, 2600.f), Vector2(-2000.f, 2000.f), 7, Vector2(2000.f, 2000.f), Vector2::Zero, 0.15f);
		pAnim->FindAnimation(L"Demian2_attack4_right")->Create(L"Demian2_attack4_right", pAttack24, Vector2(12000.f, 3900.f), Vector2(-2000.f, 2000.f), 7, Vector2(2000.f, 2000.f), Vector2::Zero, 0.15f);
		pAnim->FindAnimation(L"Demian2_attack4_right")->Create(L"Demian2_attack4_right", pAttack24, Vector2(12000.f, 5200.f), Vector2(-2000.f, 2000.f), 7, Vector2(2000.f, 2000.f), Vector2::Zero, 0.15f);
		pAnim->FindAnimation(L"Demian2_attack4_right")->Create(L"Demian2_attack4_right", pAttack24, Vector2(12000.f, 6500.f), Vector2(-2000.f, 2000.f), 7, Vector2(2000.f, 2000.f), Vector2::Zero, 0.15f);
		pAnim->FindAnimation(L"Demian2_attack4_right")->Create(L"Demian2_attack4_right", pAttack24, Vector2(12000.f, 7800.f), Vector2(-2000.f, 2000.f), 3, Vector2(2000.f, 2000.f), Vector2::Zero, 0.15f);

		pAnim->Create(L"Demian2_attack5_right", pAttack25, Vector2(12000.f, 0.f), Vector2(-2000.f, 2000.f), 7, Vector2(2000.f, 2000.f), Vector2::Zero, 0.15f);
		for(int i = 0; i<6; ++i)
			pAnim->FindAnimation(L"Demian2_attack5_right")->Create(L"Demian2_attack5_right", pAttack25, Vector2(12000.f, 1300.f), Vector2(-2000.f, 2000.f), 7, Vector2(2000.f, 2000.f), Vector2::Zero, 0.15f);
		pAnim->FindAnimation(L"Demian2_attack5_right")->Create(L"Demian2_attack5_right", pAttack25, Vector2(12000.f, 2600.f), Vector2(-2000.f, 2000.f), 7, Vector2(2000.f, 2000.f), Vector2::Zero, 0.15f);
		pAnim->FindAnimation(L"Demian2_attack5_right")->Create(L"Demian2_attack5_right", pAttack25, Vector2(12000.f, 3900.f), Vector2(-2000.f, 2000.f), 7, Vector2(2000.f, 2000.f), Vector2::Zero, 0.15f);
		pAnim->FindAnimation(L"Demian2_attack5_right")->Create(L"Demian2_attack5_right", pAttack25, Vector2(12000.f, 5200.f), Vector2(-2000.f, 2000.f), 7, Vector2(2000.f, 2000.f), Vector2::Zero, 0.15f);
		pAnim->FindAnimation(L"Demian2_attack5_right")->Create(L"Demian2_attack5_right", pAttack25, Vector2(12000.f, 6500.f), Vector2(-2000.f, 2000.f), 7, Vector2(2000.f, 2000.f), Vector2::Zero, 0.15f);
		pAnim->FindAnimation(L"Demian2_attack5_right")->Create(L"Demian2_attack5_right", pAttack25, Vector2(12000.f, 7800.f), Vector2(-2000.f, 2000.f), 7, Vector2(2000.f, 2000.f), Vector2::Zero, 0.15f);

		pAttack20->BindShaderResource(eShaderStage::PS, 12);
		pAttack21->BindShaderResource(eShaderStage::PS, 12);
		pAttack22->BindShaderResource(eShaderStage::PS, 12);
		pAttack23->BindShaderResource(eShaderStage::PS, 12);
		pAttack24->BindShaderResource(eShaderStage::PS, 12);
		pAttack25->BindShaderResource(eShaderStage::PS, 12);
		pDead2->BindShaderResource(eShaderStage::PS, 12);

	
		pAnim->Play(L"Demian2_stand_left", true);
	}
	DemianPhase2::~DemianPhase2()
	{
		
	}
	void DemianPhase2::Initialize()
	{
		
	}
	void DemianPhase2::Update()
	{
		
	}
	void DemianPhase2::LateUpdate()
	{
		
		Monster::LateUpdate();
	}
	void DemianPhase2::Render()
	{
		Monster::Render();
	}
	
	
}