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

/*pAttack20->BindShaderResource(eShaderStage::PS, 12);
	pAttack21->BindShaderResource(eShaderStage::PS, 12);
	pAttack22->BindShaderResource(eShaderStage::PS, 12);
	pAttack23->BindShaderResource(eShaderStage::PS, 12);
	pAttack24->BindShaderResource(eShaderStage::PS, 12);
	pAttack25->BindShaderResource(eShaderStage::PS, 12);
	pDead2->BindShaderResource(eShaderStage::PS, 12);*/

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
	
		Animator* pAnim = AddComponent<Animator>();
	
		GetComponent<Transform>()->SetScale(18.f, 18.f, 0.f);

		pAnim->Create(L"Demian2_stand_left", nullptr, Vector2(0.f, 0.f), Vector2(2000.f, 2000.f), 7, Vector2(2000.f, 2000.f), Vector2::Zero, Vector2(14000.f, 1300.f),0.15f);

		pAnim->Create(L"Demian2_dead_left", nullptr, Vector2(0.f, 0.f), Vector2(2000.f, 2000.f), 7, Vector2(2000.f, 2000.f), Vector2::Zero, Vector2(14000.f, 5200.f), 0.15f);
		pAnim->FindAnimation(L"Demian2_dead_left")->Create(L"Demian2_dead_left", nullptr, Vector2(0.f, 1300.f), Vector2(2000.f, 2000.f), 7, Vector2(2000.f, 2000.f), Vector2::Zero, Vector2(14000.f, 5200.f), 0.15f);
		pAnim->FindAnimation(L"Demian2_dead_left")->Create(L"Demian2_dead_left", nullptr, Vector2(0.f, 2600.f), Vector2(2000.f, 2000.f), 7, Vector2(2000.f, 2000.f), Vector2::Zero, Vector2(14000.f, 5200.f), 0.15f);
		pAnim->FindAnimation(L"Demian2_dead_left")->Create(L"Demian2_dead_left", nullptr, Vector2(0.f, 3900.f), Vector2(2000.f, 2000.f), 5, Vector2(2000.f, 2000.f), Vector2::Zero, Vector2(14000.f, 5200.f), 0.15f);


		pAnim->Create(L"Demian2_attack0_left", nullptr, Vector2(0.f, 0.f), Vector2(2000.f, 2000.f), 7, Vector2(2000.f, 2000.f), Vector2::Zero, Vector2(14000.f, 2600.f), 0.15f);
		pAnim->FindAnimation(L"Demian2_attack0_left")->Create(L"Demian2_attack0_left", nullptr, Vector2(0.f, 1300.f), Vector2(2000.f, 2000.f), 7, Vector2(2000.f, 2000.f), Vector2::Zero, Vector2(14000.f, 2600.f), 0.15f);

		pAnim->Create(L"Demian2_attack1_left", nullptr, Vector2(0.f, 0.f), Vector2(2000.f, 2000.f), 7, Vector2(2000.f, 2000.f), Vector2::Zero, Vector2(14000.f, 3900.f), 0.15f);
		for (int i = 0; i < 8; ++i)
			pAnim->FindAnimation(L"Demian2_attack1_left")->Create(L"Demian2_attack1_left", nullptr, Vector2(0.f, 1300.f), Vector2(2000.f, 2000.f), 7, Vector2(2000.f, 2000.f), Vector2::Zero, Vector2(14000.f, 3900.f), 0.15f);
		pAnim->FindAnimation(L"Demian2_attack1_left")->Create(L"Demian2_attack1_left", nullptr, Vector2(0.f, 2600.f), Vector2(2000.f, 2000.f), 3, Vector2(2000.f, 2000.f), Vector2::Zero, Vector2(14000.f, 3900.f), 0.15f);

		pAnim->Create(L"Demian2_attack2_left", nullptr, Vector2(0.f, 0.f), Vector2(2000.f, 2000.f), 7, Vector2(2000.f, 2000.f), Vector2::Zero, Vector2(14000.f, 9100.f), 0.12f);
		pAnim->FindAnimation(L"Demian2_attack2_left")->Create(L"Demian2_attack2_left", nullptr, Vector2(0.f, 1300.f), Vector2(2000.f, 2000.f), 7, Vector2(2000.f, 2000.f), Vector2::Zero, Vector2(14000.f, 9100.f), 0.12f);
		pAnim->FindAnimation(L"Demian2_attack2_left")->Create(L"Demian2_attack2_left", nullptr, Vector2(0.f, 2600.f), Vector2(2000.f, 2000.f), 7, Vector2(2000.f, 2000.f), Vector2::Zero, Vector2(14000.f, 9100.f), 0.12f);
		pAnim->FindAnimation(L"Demian2_attack2_left")->Create(L"Demian2_attack2_left", nullptr, Vector2(0.f, 3900.f), Vector2(2000.f, 2000.f), 7, Vector2(2000.f, 2000.f), Vector2::Zero, Vector2(14000.f, 9100.f), 0.12f);
		pAnim->FindAnimation(L"Demian2_attack2_left")->Create(L"Demian2_attack2_left", nullptr, Vector2(0.f, 5200.f), Vector2(2000.f, 2000.f), 7, Vector2(2000.f, 2000.f), Vector2::Zero, Vector2(14000.f, 9100.f), 0.12f);
		pAnim->FindAnimation(L"Demian2_attack2_left")->Create(L"Demian2_attack2_left", nullptr, Vector2(0.f, 6500.f), Vector2(2000.f, 2000.f), 7, Vector2(2000.f, 2000.f), Vector2::Zero, Vector2(14000.f, 9100.f), 0.12f);
		pAnim->FindAnimation(L"Demian2_attack2_left")->Create(L"Demian2_attack2_left", nullptr, Vector2(0.f, 7800.f), Vector2(2000.f, 2000.f), 7, Vector2(2000.f, 2000.f), Vector2::Zero, Vector2(14000.f, 9100.f), 0.12f);

		pAnim->Create(L"Demian2_attack3_left", nullptr, Vector2(0.f, 0.f), Vector2(2000.f, 2000.f), 7, Vector2(2000.f, 2000.f), Vector2::Zero, Vector2(14000.f, 9100.f), 0.15f);
		pAnim->FindAnimation(L"Demian2_attack3_left")->Create(L"Demian2_attack3_left", nullptr, Vector2(0.f, 1300.f), Vector2(2000.f, 2000.f), 7, Vector2(2000.f, 2000.f), Vector2::Zero, Vector2(14000.f, 9100.f), 0.15f);
		pAnim->FindAnimation(L"Demian2_attack3_left")->Create(L"Demian2_attack3_left", nullptr, Vector2(0.f, 2600.f), Vector2(2000.f, 2000.f), 7, Vector2(2000.f, 2000.f), Vector2::Zero, Vector2(14000.f, 9100.f), 0.15f);
		pAnim->FindAnimation(L"Demian2_attack3_left")->Create(L"Demian2_attack3_left", nullptr, Vector2(0.f, 3900.f), Vector2(2000.f, 2000.f), 7, Vector2(2000.f, 2000.f), Vector2::Zero, Vector2(14000.f, 9100.f), 0.15f);
		pAnim->FindAnimation(L"Demian2_attack3_left")->Create(L"Demian2_attack3_left", nullptr, Vector2(0.f, 5200.f), Vector2(2000.f, 2000.f), 7, Vector2(2000.f, 2000.f), Vector2::Zero, Vector2(14000.f, 9100.f), 0.15f);
		pAnim->FindAnimation(L"Demian2_attack3_left")->Create(L"Demian2_attack3_left", nullptr, Vector2(0.f, 6500.f), Vector2(2000.f, 2000.f), 7, Vector2(2000.f, 2000.f), Vector2::Zero, Vector2(14000.f, 9100.f), 0.15f);
		pAnim->FindAnimation(L"Demian2_attack3_left")->Create(L"Demian2_attack3_left", nullptr, Vector2(0.f, 7800.f), Vector2(2000.f, 2000.f), 7, Vector2(2000.f, 2000.f), Vector2::Zero, Vector2(14000.f, 9100.f), 0.15f);

		pAnim->Create(L"Demian2_attack4_left", nullptr, Vector2(0.f, 0.f), Vector2(2000.f, 2000.f), 7, Vector2(2000.f, 2000.f), Vector2::Zero, Vector2(14000.f, 9100.f), 0.15f);
		pAnim->FindAnimation(L"Demian2_attack4_left")->Create(L"Demian2_attack4_left", nullptr, Vector2(0.f, 1300.f), Vector2(2000.f, 2000.f), 7, Vector2(2000.f, 2000.f), Vector2::Zero, Vector2(14000.f, 9100.f), 0.15f);
		for(int i = 0; i<8; ++i)
			pAnim->FindAnimation(L"Demian2_attack4_left")->Create(L"Demian2_attack4_left", nullptr, Vector2(0.f, 2600.f), Vector2(2000.f, 2000.f), 7, Vector2(2000.f, 2000.f), Vector2::Zero, Vector2(14000.f, 9100.f), 0.15f);
		pAnim->FindAnimation(L"Demian2_attack4_left")->Create(L"Demian2_attack4_left", nullptr, Vector2(0.f, 3900.f), Vector2(2000.f, 2000.f), 7, Vector2(2000.f, 2000.f), Vector2::Zero, Vector2(14000.f, 9100.f),0.15f);
		pAnim->FindAnimation(L"Demian2_attack4_left")->Create(L"Demian2_attack4_left", nullptr, Vector2(0.f, 5200.f), Vector2(2000.f, 2000.f), 7, Vector2(2000.f, 2000.f), Vector2::Zero, Vector2(14000.f, 9100.f),0.15f);
		pAnim->FindAnimation(L"Demian2_attack4_left")->Create(L"Demian2_attack4_left", nullptr, Vector2(0.f, 6500.f), Vector2(2000.f, 2000.f), 7, Vector2(2000.f, 2000.f), Vector2::Zero, Vector2(14000.f, 9100.f),0.15f);
		pAnim->FindAnimation(L"Demian2_attack4_left")->Create(L"Demian2_attack4_left", nullptr, Vector2(0.f, 7800.f), Vector2(2000.f, 2000.f), 3, Vector2(2000.f, 2000.f), Vector2::Zero, Vector2(14000.f, 9100.f),0.15f);

		pAnim->Create(L"Demian2_attack5_left", nullptr, Vector2(0.f, 0.f), Vector2(2000.f, 2000.f), 7, Vector2(2000.f, 2000.f), Vector2::Zero, Vector2(14000.f, 9100.f), 0.15f);
		for (int i = 0; i < 6; ++i)
			pAnim->FindAnimation(L"Demian2_attack5_left")->Create(L"Demian2_attack5_left", nullptr, Vector2(0.f, 1300.f), Vector2(2000.f, 2000.f), 7, Vector2(2000.f, 2000.f), Vector2::Zero, Vector2(14000.f, 9100.f), 0.15f);
		pAnim->FindAnimation(L"Demian2_attack5_left")->Create(L"Demian2_attack5_left", nullptr, Vector2(0.f, 2600.f), Vector2(2000.f, 2000.f), 7, Vector2(2000.f, 2000.f), Vector2::Zero, Vector2(14000.f, 9100.f), 0.15f);
		pAnim->FindAnimation(L"Demian2_attack5_left")->Create(L"Demian2_attack5_left", nullptr, Vector2(0.f, 3900.f), Vector2(2000.f, 2000.f), 7, Vector2(2000.f, 2000.f), Vector2::Zero, Vector2(14000.f, 9100.f), 0.15f);
		pAnim->FindAnimation(L"Demian2_attack5_left")->Create(L"Demian2_attack5_left", nullptr, Vector2(0.f, 5200.f), Vector2(2000.f, 2000.f), 7, Vector2(2000.f, 2000.f), Vector2::Zero, Vector2(14000.f, 9100.f), 0.15f);
		pAnim->FindAnimation(L"Demian2_attack5_left")->Create(L"Demian2_attack5_left", nullptr, Vector2(0.f, 6500.f), Vector2(2000.f, 2000.f), 7, Vector2(2000.f, 2000.f), Vector2::Zero, Vector2(14000.f, 9100.f), 0.15f);
		pAnim->FindAnimation(L"Demian2_attack5_left")->Create(L"Demian2_attack5_left", nullptr, Vector2(0.f, 7800.f), Vector2(2000.f, 2000.f), 7, Vector2(2000.f, 2000.f), Vector2::Zero, Vector2(14000.f, 9100.f), 0.15f);

		pAnim->Create(L"Demian2_stand_right", nullptr, Vector2(12000.f, 0.f), Vector2(-2000.f, 2000.f), 7, Vector2(2000.f, 2000.f), Vector2::Zero, Vector2(14000.f, 1300.f), 0.15f);

		pAnim->Create(L"Demian2_dead_right", nullptr, Vector2(12000.f, 0.f), Vector2(-2000.f, 2000.f), 7, Vector2(2000.f, 2000.f), Vector2::Zero, Vector2(14000.f, 5200.f), 0.15f);
		pAnim->FindAnimation(L"Demian2_dead_right")->Create(L"Demian2_dead_right", nullptr, Vector2(12000.f, 1300.f), Vector2(-2000.f, 2000.f), 7, Vector2(2000.f, 2000.f), Vector2::Zero, Vector2(14000.f, 5200.f), 0.15f);
		pAnim->FindAnimation(L"Demian2_dead_right")->Create(L"Demian2_dead_right", nullptr, Vector2(12000.f, 2600.f), Vector2(-2000.f, 2000.f), 7, Vector2(2000.f, 2000.f), Vector2::Zero, Vector2(14000.f, 5200.f), 0.15f);
		pAnim->FindAnimation(L"Demian2_dead_right")->Create(L"Demian2_dead_right", nullptr, Vector2(12000.f, 3900.f), Vector2(-2000.f, 2000.f), 5, Vector2(2000.f, 2000.f), Vector2::Zero, Vector2(14000.f, 5200.f), 0.15f);


		pAnim->Create(L"Demian2_attack0_right", nullptr, Vector2(12000.f, 0.f), Vector2(-2000.f, 2000.f), 7, Vector2(2000.f, 2000.f), Vector2::Zero, Vector2(14000.f, 2600.f), 0.15f);
		pAnim->FindAnimation(L"Demian2_attack0_right")->Create(L"Demian2_attack0_right", nullptr, Vector2(12000.f, 1300.f), Vector2(-2000.f, 2000.f), 7, Vector2(2000.f, 2000.f), Vector2::Zero, Vector2(14000.f, 2600.f), 0.15f);

		pAnim->Create(L"Demian2_attack1_right", nullptr, Vector2(12000.f, 0.f), Vector2(-2000.f, 2000.f), 7, Vector2(2000.f, 2000.f), Vector2::Zero, Vector2(14000.f, 3900.f), 0.15f);
		for (int i = 0; i < 8; ++i)
			pAnim->FindAnimation(L"Demian2_attack1_right")->Create(L"Demian2_attack1_right", nullptr, Vector2(12000.f, 1300.f), Vector2(-2000.f, 2000.f), 7, Vector2(2000.f, 2000.f), Vector2::Zero, Vector2(14000.f, 3900.f), 0.15f);
		pAnim->FindAnimation(L"Demian2_attack1_right")->Create(L"Demian2_attack1_right", nullptr, Vector2(12000.f, 2600.f), Vector2(-2000.f, 2000.f), 3, Vector2(2000.f, 2000.f), Vector2::Zero, Vector2(14000.f, 3900.f), 0.15f);

		pAnim->Create(L"Demian2_attack2_right", nullptr, Vector2(12000.f, 0.f), Vector2(-2000.f, 2000.f), 7, Vector2(2000.f, 2000.f), Vector2::Zero, Vector2(14000.f, 9100.f), 0.12f);
		pAnim->FindAnimation(L"Demian2_attack2_right")->Create(L"Demian2_attack2_right", nullptr, Vector2(12000.f, 1300.f), Vector2(-2000.f, 2000.f), 7, Vector2(2000.f, 2000.f), Vector2::Zero, Vector2(14000.f, 9100.f), 0.12f);
		pAnim->FindAnimation(L"Demian2_attack2_right")->Create(L"Demian2_attack2_right", nullptr, Vector2(12000.f, 2600.f), Vector2(-2000.f, 2000.f), 7, Vector2(2000.f, 2000.f), Vector2::Zero, Vector2(14000.f, 9100.f), 0.12f);
		pAnim->FindAnimation(L"Demian2_attack2_right")->Create(L"Demian2_attack2_right", nullptr, Vector2(12000.f, 3900.f), Vector2(-2000.f, 2000.f), 7, Vector2(2000.f, 2000.f), Vector2::Zero, Vector2(14000.f, 9100.f), 0.12f);
		pAnim->FindAnimation(L"Demian2_attack2_right")->Create(L"Demian2_attack2_right", nullptr, Vector2(12000.f, 5200.f), Vector2(-2000.f, 2000.f), 7, Vector2(2000.f, 2000.f), Vector2::Zero, Vector2(14000.f, 9100.f), 0.12f);
		pAnim->FindAnimation(L"Demian2_attack2_right")->Create(L"Demian2_attack2_right", nullptr, Vector2(12000.f, 6500.f), Vector2(-2000.f, 2000.f), 7, Vector2(2000.f, 2000.f), Vector2::Zero, Vector2(14000.f, 9100.f), 0.12f);
		pAnim->FindAnimation(L"Demian2_attack2_right")->Create(L"Demian2_attack2_right", nullptr, Vector2(12000.f, 7800.f), Vector2(-2000.f, 2000.f), 7, Vector2(2000.f, 2000.f), Vector2::Zero, Vector2(14000.f, 9100.f), 0.12f);

		pAnim->Create(L"Demian2_attack3_right", nullptr, Vector2(12000.f, 0.f), Vector2(-2000.f, 2000.f), 7, Vector2(2000.f, 2000.f), Vector2::Zero, Vector2(14000.f, 9100.f), 0.15f);
		pAnim->FindAnimation(L"Demian2_attack3_right")->Create(L"Demian2_attack3_right", nullptr, Vector2(12000.f, 1300.f), Vector2(-2000.f, 2000.f), 7, Vector2(2000.f, 2000.f), Vector2::Zero, Vector2(14000.f, 9100.f), 0.15f);
		pAnim->FindAnimation(L"Demian2_attack3_right")->Create(L"Demian2_attack3_right", nullptr, Vector2(12000.f, 2600.f), Vector2(-2000.f, 2000.f), 7, Vector2(2000.f, 2000.f), Vector2::Zero, Vector2(14000.f, 9100.f), 0.15f);
		pAnim->FindAnimation(L"Demian2_attack3_right")->Create(L"Demian2_attack3_right", nullptr, Vector2(12000.f, 3900.f), Vector2(-2000.f, 2000.f), 7, Vector2(2000.f, 2000.f), Vector2::Zero, Vector2(14000.f, 9100.f), 0.15f);
		pAnim->FindAnimation(L"Demian2_attack3_right")->Create(L"Demian2_attack3_right", nullptr, Vector2(12000.f, 5200.f), Vector2(-2000.f, 2000.f), 7, Vector2(2000.f, 2000.f), Vector2::Zero, Vector2(14000.f, 9100.f), 0.15f);
		pAnim->FindAnimation(L"Demian2_attack3_right")->Create(L"Demian2_attack3_right", nullptr, Vector2(12000.f, 6500.f), Vector2(-2000.f, 2000.f), 7, Vector2(2000.f, 2000.f), Vector2::Zero, Vector2(14000.f, 9100.f), 0.15f);
		pAnim->FindAnimation(L"Demian2_attack3_right")->Create(L"Demian2_attack3_right", nullptr, Vector2(12000.f, 7800.f), Vector2(-2000.f, 2000.f), 7, Vector2(2000.f, 2000.f), Vector2::Zero, Vector2(14000.f, 9100.f), 0.15f);
	

		pAnim->Create(L"Demian2_attack4_right", nullptr, Vector2(12000.f, 0.f), Vector2(-2000.f, 2000.f), 7, Vector2(2000.f, 2000.f), Vector2::Zero, Vector2(14000.f, 9100.f), 0.15f);
		pAnim->FindAnimation(L"Demian2_attack4_right")->Create(L"Demian2_attack4_right", nullptr, Vector2(12000.f, 1300.f), Vector2(-2000.f, 2000.f), 7, Vector2(2000.f, 2000.f), Vector2::Zero, Vector2(14000.f, 9100.f), 0.15f);
		for(int i = 0; i<9; ++i)
			pAnim->FindAnimation(L"Demian2_attack4_right")->Create(L"Demian2_attack4_right", nullptr, Vector2(12000.f, 2600.f), Vector2(-2000.f, 2000.f), 7, Vector2(2000.f, 2000.f), Vector2::Zero, Vector2(14000.f, 9100.f), 0.15f);
		pAnim->FindAnimation(L"Demian2_attack4_right")->Create(L"Demian2_attack4_right", nullptr, Vector2(12000.f, 3900.f), Vector2(-2000.f, 2000.f), 7, Vector2(2000.f, 2000.f), Vector2::Zero, Vector2(14000.f, 9100.f), 0.15f);
		pAnim->FindAnimation(L"Demian2_attack4_right")->Create(L"Demian2_attack4_right", nullptr, Vector2(12000.f, 5200.f), Vector2(-2000.f, 2000.f), 7, Vector2(2000.f, 2000.f), Vector2::Zero, Vector2(14000.f, 9100.f), 0.15f);
		pAnim->FindAnimation(L"Demian2_attack4_right")->Create(L"Demian2_attack4_right", nullptr, Vector2(12000.f, 6500.f), Vector2(-2000.f, 2000.f), 7, Vector2(2000.f, 2000.f), Vector2::Zero, Vector2(14000.f, 9100.f), 0.15f);
		pAnim->FindAnimation(L"Demian2_attack4_right")->Create(L"Demian2_attack4_right", nullptr, Vector2(12000.f, 7800.f), Vector2(-2000.f, 2000.f), 3, Vector2(2000.f, 2000.f), Vector2::Zero, Vector2(14000.f, 9100.f), 0.15f);

		pAnim->Create(L"Demian2_attack5_right", nullptr, Vector2(12000.f, 0.f), Vector2(-2000.f, 2000.f), 7, Vector2(2000.f, 2000.f), Vector2::Zero, Vector2(14000.f, 9100.f), 0.15f);
		for(int i = 0; i<6; ++i)
			pAnim->FindAnimation(L"Demian2_attack5_right")->Create(L"Demian2_attack5_right", nullptr, Vector2(12000.f, 1300.f), Vector2(-2000.f, 2000.f), 7, Vector2(2000.f, 2000.f), Vector2::Zero, Vector2(14000.f, 9100.f), 0.15f);
		pAnim->FindAnimation(L"Demian2_attack5_right")->Create(L"Demian2_attack5_right", nullptr, Vector2(12000.f, 2600.f), Vector2(-2000.f, 2000.f), 7, Vector2(2000.f, 2000.f), Vector2::Zero, Vector2(14000.f, 9100.f), 0.15f);
		pAnim->FindAnimation(L"Demian2_attack5_right")->Create(L"Demian2_attack5_right", nullptr, Vector2(12000.f, 3900.f), Vector2(-2000.f, 2000.f), 7, Vector2(2000.f, 2000.f), Vector2::Zero, Vector2(14000.f, 9100.f), 0.15f);
		pAnim->FindAnimation(L"Demian2_attack5_right")->Create(L"Demian2_attack5_right", nullptr, Vector2(12000.f, 5200.f), Vector2(-2000.f, 2000.f), 7, Vector2(2000.f, 2000.f), Vector2::Zero, Vector2(14000.f, 9100.f), 0.15f);
		pAnim->FindAnimation(L"Demian2_attack5_right")->Create(L"Demian2_attack5_right", nullptr, Vector2(12000.f, 6500.f), Vector2(-2000.f, 2000.f), 7, Vector2(2000.f, 2000.f), Vector2::Zero, Vector2(14000.f, 9100.f), 0.15f);
		pAnim->FindAnimation(L"Demian2_attack5_right")->Create(L"Demian2_attack5_right", nullptr, Vector2(12000.f, 7800.f), Vector2(-2000.f, 2000.f), 7, Vector2(2000.f, 2000.f), Vector2::Zero, Vector2(14000.f, 9100.f), 0.15f);


		SpawnMonsterAttack* pSpawnObj = new SpawnMonsterAttack();
		pSpawnObj->SetName(L"SpawnObj");
		ObjectPoolManager::AddObjectPool(pSpawnObj->GetName(), pSpawnObj);

		MonsterMoveAttack* pAttack0 = new MonsterMoveAttack();
		pAttack0->SetName(L"Demian2_attack0");
		ObjectPoolManager::AddObjectPool(pAttack0->GetName(), pAttack0);

		for (int i = 0; i < 20; ++i)
		{
			DemianFire1* pAttack1 = new DemianFire1();
			pAttack1->SetName(L"Demian2_attack1");
			ObjectPoolManager::AddObjectPool(pAttack1->GetName(), pAttack1);
		}

		for (int i = 0; i < 2; ++i)
		{
			DemianSpear0* pAttack2 = new DemianSpear0();
			pAttack2->SetName(L"Demian2_attack2");
			ObjectPoolManager::AddObjectPool(pAttack2->GetName(), pAttack2);
		}

		DemianSpear1* pAttack2_1 = new DemianSpear1();
		pAttack2_1->SetName(L"Demian2_attack2");
		ObjectPoolManager::AddObjectPool(pAttack2_1->GetName(), pAttack2_1);


		MonsterAttackObject* pAttack3 = new MonsterAttackObject();
		pAttack3->SetName(L"Demian2_attack3");
		ObjectPoolManager::AddObjectPool(pAttack3->GetName(), pAttack3);

		for (int i = 0; i < 30; ++i)
		{
			DemianFire2* pAttack4 = new DemianFire2();
			pAttack4->SetName(L"Demian2_attack4");
			ObjectPoolManager::AddObjectPool(pAttack4->GetName(), pAttack4);
		}

		DemianVine* pDemianVine = new DemianVine();
		pDemianVine->SetName(L"Demian2_attack5");
		ObjectPoolManager::AddObjectPool(pDemianVine->GetName(), pDemianVine);
	}
	DemianPhase2::~DemianPhase2()
	{
		
	}
	void DemianPhase2::Initialize()
	{
		std::shared_ptr<Texture> pNormal2 = Resources::Find<Texture>(L"Demian2Normal");
		std::shared_ptr<Texture> pDead2 = Resources::Find<Texture>(L"Demian2Dead");
		std::shared_ptr<Texture> pAttack20 = Resources::Find<Texture>(L"Demian2_attack0");
		std::shared_ptr<Texture> pAttack21 = Resources::Find<Texture>(L"Demian2_attack1");
		std::shared_ptr<Texture> pAttack22 = Resources::Find<Texture>(L"Demian2_attack2");
		std::shared_ptr<Texture> pAttack23 = Resources::Find<Texture>(L"Demian2_attack3");
		std::shared_ptr<Texture> pAttack24 = Resources::Find<Texture>(L"Demian2_attack4");
		std::shared_ptr<Texture> pAttack25 = Resources::Find<Texture>(L"Demian2_attack5");

		Animator* pAnim = GetComponent<Animator>();
		pAnim->SetTextureBothDir(L"Demian2_stand", pNormal2);
		pAnim->SetTextureBothDir(L"Demian2_dead", pDead2);
		pAnim->SetTextureBothDir(L"Demian2_attack0", pAttack20);
		pAnim->SetTextureBothDir(L"Demian2_attack1", pAttack21);
		pAnim->SetTextureBothDir(L"Demian2_attack2", pAttack22);
		pAnim->SetTextureBothDir(L"Demian2_attack3", pAttack23);
		pAnim->SetTextureBothDir(L"Demian2_attack4", pAttack24);
		pAnim->SetTextureBothDir(L"Demian2_attack5", pAttack25);
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

	void DemianPhase2::UpdateState(const wstring& _strStateName, int _iState)
	{
		Monster::UpdateState(_strStateName, _iState);
	}
	
	
}