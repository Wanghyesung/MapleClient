#include "WDemianPhase2.h"
#include "WAnimator.h"
#include "WRigidbody.h"
#include "WResources.h"
#include "WMonsterDead.h"
#include "WMonsterFSM.h"
#include "WMonsterStand.h"
#include "WMonsterAttack.h"
#include "WMonsterMove.h"
#include "WMonsterScript.h"
#include "WSpawnMonsterAttack.h"
#include "WBattleManager.h"
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
#include "WMonsterAttackScript.h"
namespace W
{
	DemianPhase2::DemianPhase2():
		m_bGroggy(false),
		m_iSpearCount(0),
		m_iAttackCallCount(1),
		m_iCircleLevel(-1)
	{
		SetName(L"Demian2");

		MeshRenderer* pRenderer = AddComponent<MeshRenderer>();
		pRenderer->SetMesh(Resources::Find<Mesh>(L"RectMesh"));


		std::shared_ptr<Material> pMater = std::make_shared<Material>();
		pMater->SetRenderinMode(eRenderingMode::Transparent);
		pMater->SetShader(Resources::Find<Shader>(L"MonsterShader"));
		Resources::Insert(L"DemianMater", pMater);

		pRenderer->SetMaterial(pMater);
		AddComponent<Rigidbody>();

		std::shared_ptr<Texture> pNormal2 = Resources::Find<Texture>(L"Demian2Normal");
		std::shared_ptr<Texture> pDead2 = Resources::Find<Texture>(L"Demian2Dead");
		std::shared_ptr<Texture> pAttack20 = Resources::Find<Texture>(L"Demian2_attack0");
		std::shared_ptr<Texture> pAttack21 = Resources::Find<Texture>(L"Demian2_attack1");
		std::shared_ptr<Texture> pAttack22 = Resources::Find<Texture>(L"Demian2_attack2");
		std::shared_ptr<Texture> pAttack23 = Resources::Find<Texture>(L"Demian2_attack3");
		std::shared_ptr<Texture> pAttack24 = Resources::Find<Texture>(L"Demian2_attack4");
		std::shared_ptr<Texture> pAttack25 = Resources::Find<Texture>(L"Demian2_attack5");

		Animator* pAnim = AddComponent<Animator>();
		//////////////////페이즈 2///////////////////////
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

		//데미안 창 공격
		set_effect();
	
		//공격 후 이동
		pAnim->EndEvent(L"Demian2_attack3_right") = std::bind(&DemianPhase2::move, this);
		pAnim->EndEvent(L"Demian2_attack3_left") = std::bind(&DemianPhase2::move, this);

		pAnim->Play(L"Demian2_stand_left", true);
	}
	DemianPhase2::~DemianPhase2()
	{
		for(int i = 0; i<m_vecCircle.size(); ++i)
		{
			if (m_vecCircle[i]->IsActive())
				continue;

			delete m_vecCircle[i];;
			m_vecCircle[i] = nullptr;
		}

		ObjectPoolManager::ReleaseObject(L"SpawnObj");
		ObjectPoolManager::ReleaseObject(L"Demian2_attack0");
		ObjectPoolManager::ReleaseObject(L"Demian2_attack1");
		ObjectPoolManager::ReleaseObject(L"Demian2_attack2");
		ObjectPoolManager::ReleaseObject(L"Demian2_attack3");
		ObjectPoolManager::ReleaseObject(L"Demian2_attack4");
		ObjectPoolManager::ReleaseObject(L"Demian2_attack5");
	}
	void DemianPhase2::Initialize()
	{
		GetComponent<Transform>()->SetScale(18.f, 18.f, 0.f);
		GetComponent<Transform>()->SetPosition(0.1f, -1.75f, -1.5f);
		Collider2D* pCollider = AddComponent<Collider2D>();
		pCollider->SetSize(Vector2(0.06f, 0.06f));
		pCollider->SetCenter(Vector2(0.f, -0.4f));

		MonsterScript* Pscript = AddComponent<MonsterScript>();
		Pscript->SetBoss();
		Pscript->Initialize();
		Pscript->SetHP(300.f);
		//Pscript->CreateHP();

		setattack();
		add_skill();

		MonsterFSM* pFSM = new MonsterFSM();
		pFSM->SetMonster(this);
		Pscript->SetFSM(pFSM);

		MonsterStand* pStand = new MonsterStand();
		pStand->SetTargetDistance(15.f);
		pStand->SetMinDistance(15.f);
		pFSM->AddState(pStand);

		pFSM->AddState(new MonsterMove());
		pFSM->AddState(new MonsterAttack());
		pFSM->AddState(new MonsterDead());
		pFSM->SetActiveState(eMonsterState::stand);
	}
	void DemianPhase2::Update()
	{
		check_HP();

		Monster::Update();
	}
	void DemianPhase2::LateUpdate()
	{
		std::wstring strName = GetName();
		std::wstring strState = GetCurStateName();
		std::wstring strDir;

		if (strState == L"_attack")
		{
			UINT iNumber = GetScript<MonsterScript>()->GetAttackNumber();
			strState += std::to_wstring(iNumber);
		}
		int iDir = GetDir();


		if (iDir > 0)
			strDir = L"_right";
		else
			strDir = L"_left";

		std::wstring strCurAnim = strName + strState + strDir;
		std::wstring strAnimName = GetMonsterAnim();

		if (strAnimName != strCurAnim)
		{
			SetMonsterAnim(strCurAnim);
			GetComponent<Animator>()->Play(strCurAnim, true);
		}

		Monster::LateUpdate();
	}
	void DemianPhase2::Render()
	{
		Monster::Render();
	}
	void DemianPhase2::add_skill()
	{
		for (int i = 0; i < 2; ++i)
		{
			DemianCircle* pDemianCircle = new DemianCircle();
			pDemianCircle->SetName(L"DemianCircle");
			pDemianCircle->Initialize();
			m_vecCircle.push_back(pDemianCircle);
		}

		SpawnMonsterAttack* pSpawnObj = new SpawnMonsterAttack();
		pSpawnObj->SetName(L"SpawnObj");
		pSpawnObj->SetOnwer(this);
		AddMonsterSkill(pSpawnObj);

		MonsterMoveAttack* pAttack0 = new MonsterMoveAttack();
		pAttack0->SetName(L"Demian2_attack0");
		pAttack0->GetScript<MonsterAttackScript>()->SeteAbnormalType(BattleManager::eAbnormalType::Stigma);
		pAttack0->SetOnwer(this);
		AddMonsterSkill(pAttack0);

		for (int i = 0; i < 20; ++i)
		{
			DemianFire1* pAttack1 = new DemianFire1();
			pAttack1->SetName(L"Demian2_attack1");
			pAttack1->SetOnwer(this);
			AddMonsterSkill(pAttack1);
		}
		
		DemianSpear0* pAttack2 = new DemianSpear0();
		pAttack2->SetName(L"Demian2_attack2");
		pAttack2->GetScript<MonsterAttackScript>()->SeteAbnormalType(BattleManager::eAbnormalType::Stigma);
		pAttack2->SetOnwer(this);
		AddMonsterSkill(pAttack2);

		DemianSpear1* pAttack2_1 = new DemianSpear1();
		pAttack2_1->SetName(L"Demian2_attack2");
		pAttack2_1->GetScript<MonsterAttackScript>()->SeteAbnormalType(BattleManager::eAbnormalType::Stigma);
		pAttack2_1->SetOnwer(this);
		AddMonsterSkill(pAttack2_1);

		pAttack2 = new DemianSpear0();
		pAttack2->SetName(L"Demian2_attack2");
		pAttack2->GetScript<MonsterAttackScript>()->SeteAbnormalType(BattleManager::eAbnormalType::Stigma);
		pAttack2->SetOnwer(this);
		AddMonsterSkill(pAttack2);

		MonsterAttackObject* pAttack3 = new MonsterAttackObject();
		pAttack3->SetName(L"Demian2_attack3");
		pAttack3->GetScript<MonsterAttackScript>()->SeteAbnormalType(BattleManager::eAbnormalType::Stigma);
		pAttack3->SetOnwer(this);
		AddMonsterSkill(pAttack3);


		for (int i = 0; i < 30; ++i)
		{
			DemianFire2* pAttack4 = new DemianFire2();
			pAttack4->SetName(L"Demian2_attack4");
			pAttack4->SetOnwer(this);
			AddMonsterSkill(pAttack4);
		}

		DemianVine* pDemianVine = new DemianVine();
		pDemianVine->SetName(L"Demian2_attack5");
		pDemianVine->SetOnwer(this);
		AddMonsterSkill(pDemianVine);
	}
	void DemianPhase2::setattack()
	{
		MonsterScript* Pscript = GetComponent<MonsterScript>();
		Vector3 vPosition = GetComponent<Transform>()->GetPosition();

		tMonsterAttack attack0 = {};
		attack0.vPosition = vPosition;
		attack0.vScale = Vector2(2.f, 2.f);
		attack0.vOffset = Vector2(0.f, 0.f);

		attack0.tAttackInfo.fAttackDamage = 30.f;
		attack0.tAttackInfo.eAttType = eAttackType::SuperKnockback;
		attack0.tAttackInfo.fAttUpperRcnt = 0.f;
		attack0.tAttackInfo.fAttRigidityTime = 0.7f;
		attack0.tAttackInfo.fAttRcnt = 3.f;
	
		attack0.tTime.fCoolTime = 10.f;

		attack0.pFunction = std::bind(&DemianPhase2::attack0, this);
	
		attack0.iStartFrame = 6;
		attack0.iEndFrame = 9;

		Pscript->AddAttack(attack0);

		//2
		tMonsterAttack attack1 = {};
		attack1.bSkill = true;
		
		attack1.tTime.fCoolTime = 20.f;
		attack1.tAttackInfo.fAttackDamage = BattleManager::GetMaxDamage();
		
		attack1.pFunction = std::bind(&DemianPhase2::attack1, this);
		
		attack1.iStartFrame = 7;
		attack1.iEndFrame = 64;
		
		Pscript->AddAttack(attack1);
		
		//3
		tMonsterAttack attack2 = {};
		attack2.bSkill = true;
		
		attack2.tTime.fCoolTime = 20.f;
		
		attack2.pFunction = std::bind(&DemianPhase2::attack2, this);
		
		attack2.iStartFrame = 11;
		attack2.iEndFrame = 12;
		Pscript->AddAttack(attack2);
		
		////
		////
		tMonsterAttack attack3 = {};
		attack3.vPosition = vPosition;
		attack3.vScale = Vector2(3.f, 2.f);
		attack3.vOffset = Vector2(4.f, 0.f);
		attack3.tAttackInfo.fAttackDamage = BattleManager::GetMaxDamage();
		attack3.tTime.fCoolTime = 30.f;
		
		attack3.pFunction = std::bind(&DemianPhase2::attack3, this);
		
		attack3.iStartFrame = 35;
		attack3.iEndFrame = 39;
		Pscript->AddAttack(attack3);

		tMonsterAttack attack4 = {};
		attack4.bSkill = true;
		attack4.tTime.fCoolTime = 25.f;
		//attack4.tAttackInfo.fAttackDamage = BattleManager::GetMaxDamage();
		
		attack4.pFunction = std::bind(&DemianPhase2::attack4, this);
		
		attack4.iStartFrame = 11;
		attack4.iEndFrame = 64;
		Pscript->AddAttack(attack4);
		//
		//
		tMonsterAttack attack5 = {};
		attack5.bSkill = true;
		attack5.tTime.fCoolTime = 999999999.f;
		
		attack5.pFunction = std::bind(&DemianPhase2::attack5, this);
		attack5.iStartFrame = 7;
		//attack5.iEndFrame = 113;
		Pscript->AddAttack(attack5);
	}
	void DemianPhase2::attack0()
	{
		Effect* pEffect =  BattleManager::GetEffect(L"DemianAttack0Effect");
		EventManager::CreateObject(pEffect, eLayerType::Effect);
		pEffect->SetActive(true);
		pEffect->StartEffect(GetDir());
		Vector3 vPosition = GetComponent<Transform>()->GetPosition();
		pEffect->GetComponent<Transform>()->SetPosition(vPosition);

		MonsterAttackObject* attack0 = GetMonsterSkill(L"Demian2_attack0");
		if (attack0 == nullptr)
			return;
		MonsterScript* pMonsterScript = GetScript<MonsterScript>();
		pMonsterScript->SetMonsterAttack(attack0);
		EventManager::CreateObject(attack0, eLayerType::MonsterAttack);
	}
	void DemianPhase2::attack1()
	{
		MonsterAttackObject* attack1 = GetMonsterSkill(L"SpawnObj");
		if (attack1 == nullptr)
			return;
		SpawnMonsterAttack* pSpawn = dynamic_cast<SpawnMonsterAttack*>(attack1);

		pSpawn->SetOnwer(this);

		//위치 초기화
		Vector3 vPosition = GetComponent<Transform>()->GetPosition();
		pSpawn->GetComponent<Transform>()->SetPosition(vPosition);

		pSpawn->Initialize();

		//속도, 생성 위치 설정
		Vector2 vLook[4] = { Vector2{3.f, 0.f},Vector2{3.f, 0.f},Vector2{-3.f, 0.f},
		Vector2{-3.f, 0.f} };
		Vector3 vOffset[4] = { Vector3{0.f, 0.7f,0.f},Vector3{0.f, -0.3f,0.f},Vector3{0.f, 0.7f,0.f},
		Vector3{0.f, -0.3f,0.f} };

		for (int i = 0; i < 4; ++i)
			pSpawn->SetVelocity(vLook[i], vOffset[i]);
			

		//spawn 객체에서 몬스터 기술 가져오기
		pSpawn->SetTime(1.5f);
		pSpawn->SetAttackName(L"Demian2_attack1");
		pSpawn->SetCreateCount(4);
		pSpawn->SetEndFrame(64);

		EventManager::CreateObject(pSpawn, eLayerType::MonsterAttack);
	}
	void DemianPhase2::attack2()
	{
		Effect* pEffect = BattleManager::GetEffect(L"DemianClone0");
		EventManager::CreateObject(pEffect, eLayerType::Effect);
		pEffect->SetActive(true);
		pEffect->StartEffect(GetDir());

		//재귀
		Vector3 vPosition = GetComponent<Transform>()->GetPosition();
		vPosition.x += (m_iSpearCount * GetDir());
		pEffect->GetComponent<Transform>()->SetPosition(vPosition);
	}
	void DemianPhase2::attack3()
	{
		MonsterAttackObject* attack2 = GetMonsterSkill(L"Demian2_attack3");
		if (attack2 == nullptr)
			return;
		MonsterScript* pMonsterScript = GetScript<MonsterScript>();
		pMonsterScript->SetMonsterAttack(attack2);

		EventManager::CreateObject(attack2, eLayerType::MonsterAttack);
	}
	void DemianPhase2::attack4()
	{
		MonsterAttackObject* attack2 = GetMonsterSkill(L"SpawnObj");
		if (attack2 == nullptr)
			return;
		SpawnMonsterAttack* pSpawn = dynamic_cast<SpawnMonsterAttack*>(attack2);

		pSpawn->SetOnwer(this);

		Vector3 vPosition = GetComponent<Transform>()->GetPosition();
		vPosition.y += 3.4;
		pSpawn->GetComponent<Transform>()->SetPosition(vPosition);

		pSpawn->Initialize();

		//속도 설정
		Vector2 vLook[5] = { Vector2{0.8f,-0.8f}, Vector2{0.45f,-0.45f} , Vector2{0,-1.f},
			Vector2{-0.5f,-0.5f},Vector2{-0.8f,-0.8f} };
		for (int i = 0; i < 5; ++i)
			pSpawn->SetVelocity(vLook[i]);

		//spawn 객체에서 몬스터 기술 가져오기
		pSpawn->SetTime(1.7f);
		pSpawn->SetAttackName(L"Demian2_attack4");
		pSpawn->SetCreateCount(5);
		pSpawn->SetEndFrame(70);
		EventManager::CreateObject(pSpawn, eLayerType::MonsterAttack);
	}

	void DemianPhase2::attack5()
	{
		m_iAttackCallCount = 0;

		BattleManager::HitchAbnormal(BattleManager::eAbnormalType::DemianStop);

		MonsterAttackObject* attack5 = GetMonsterSkill(L"Demian2_attack5");
		if (attack5 == nullptr)
			return;
		attack5->Initialize();
	
		EventManager::CreateObject(attack5, eLayerType::MonsterAttack);
	}

	void DemianPhase2::check_HP()
	{

		MonsterScript* pScript = GetScript<MonsterScript>();
		const tObjectInfo& tInfo = pScript->GetObjectInfo();

		//세계수
		if (tInfo.fHP / tInfo.fMaxHP <= 0.15f &&
			m_iAttackCallCount == 1)
		{
			m_iAttackCallCount = 0;
			pScript->AciveAttack(5);
		}
			

		//구 크기
		if (tInfo.fHP / tInfo.fMaxHP <= 1.0f)
		{
			int iLevel = 0;
			if (tInfo.fHP / tInfo.fMaxHP <= 0.20f)
				iLevel = 2;

			else if(tInfo.fHP / tInfo.fMaxHP <= 0.40f)
					iLevel = 1;
			
			if (m_iCircleLevel != iLevel)
			{

				m_iCircleLevel = iLevel;
				if (m_iCircleLevel == 1 || m_iCircleLevel == 0)
				{
					EventManager::CreateObject(m_vecCircle[m_iCircleLevel], eLayerType::MonsterAttack);
					m_vecCircle[m_iCircleLevel]->SetActive(true);
					m_vecCircle[m_iCircleLevel]->SetSpeed((m_iCircleLevel + 1.f)/2.f);
				}

				for (int i = 0; i < m_vecCircle.size(); ++i)
				{
					m_vecCircle[i]->LevelUp(m_iCircleLevel);
				}
			}
		}
			

		if (tInfo.fHP / tInfo.fMaxHP <= 0.f)
		{
			for (int i = 0; i < 2; ++i)
			{
				SceneManger::Erase(m_vecCircle[i]);
				m_vecCircle[i]->SetActive(false);
			}
		}
	}
	void DemianPhase2::create_spear0()
	{
		//위
		++m_iSpearCount;
		MonsterAttackObject* attack2 = GetMonsterSkill(L"Demian2_attack2");
		if (attack2 == nullptr)
			return;
		MonsterScript* pMonsterScript = GetScript<MonsterScript>();
		EventManager::CreateObject(attack2, eLayerType::MonsterAttack);

		//spear
		Vector3 vSpearPosition = GetComponent<Transform>()->GetPosition();
		vSpearPosition.x += (m_iSpearCount * GetDir() / 0.5f);
		attack2->GetComponent<Transform>()->SetPosition(vSpearPosition);
		attack2->Initialize();

		//clone 생성
		if (m_iSpearCount >= 3)
		{
			m_iSpearCount = 0;
			return;
		}
		Effect* pEffect = BattleManager::GetEffect(L"DemianClone1");
		EventManager::CreateObject(pEffect, eLayerType::Effect);
		pEffect->SetActive(true);
		pEffect->StartEffect(GetDir());

		Vector3 vPosition = GetComponent<Transform>()->GetPosition();
		vPosition.x += (m_iSpearCount * GetDir());
		pEffect->GetComponent<Transform>()->SetPosition(vPosition);
	}

	void DemianPhase2::create_spear1()
	{
		//아래
		++m_iSpearCount;

		MonsterAttackObject* attack2 = GetMonsterSkill(L"Demian2_attack2");
		if (attack2 == nullptr)
			return;
		MonsterScript* pMonsterScript = GetScript<MonsterScript>();
		EventManager::CreateObject(attack2, eLayerType::MonsterAttack);

		Vector3 vSpearPosition = GetComponent<Transform>()->GetPosition();
		vSpearPosition.x += (m_iSpearCount * GetDir() / 0.5f);
		attack2->GetComponent<Transform>()->SetPosition(vSpearPosition);
		attack2->Initialize();

		//clone 생성
		if (m_iSpearCount >= 3)
		{
			m_iSpearCount = 0;
			return;
		}

		Effect* pEffect = BattleManager::GetEffect(L"DemianClone0");
		EventManager::CreateObject(pEffect, eLayerType::Effect);
		pEffect->SetActive(true);
		pEffect->StartEffect(GetDir());

		Vector3 vPosition = GetComponent<Transform>()->GetPosition();
		vPosition.x += (m_iSpearCount * GetDir());
		pEffect->GetComponent<Transform>()->SetPosition(vPosition);

	}
	void DemianPhase2::set_effect()
	{
		for (int i = 0; i < 2; ++i)
		{
			Effect* pClone1 = BattleManager::GetEffect(L"DemianClone0");
			pClone1->SetFunction(std::bind(&DemianPhase2::create_spear0, this), 1);
			BattleManager::PushEffect(pClone1);
		}
		
		Effect* pClone2 = BattleManager::GetEffect(L"DemianClone1");
		pClone2->SetFunction(std::bind(&DemianPhase2::create_spear1, this), 1);
		BattleManager::PushEffect(pClone2);
	}

	void DemianPhase2::move()
	{
		Vector3 vPosition = GetComponent<Transform>()->GetPosition();
		vPosition.x += (GetDir() * 4.38f);
		GetComponent<Transform>()->SetPosition(vPosition);
	}
	
}