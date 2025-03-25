#include "WDemian.h"
#include "WResources.h"
#include "WRigidbody.h"
#include "WMonsterScript.h"
#include "WMonsterMove.h"
#include "WMonsterStand.h"
#include "WMonsterAttack.h"
#include "WMonsterFSM.h"
#include "WMonsterDead.h"
#include "WRigidbody.h"
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
#include "WMonsterAttackScript.h"
#include "WTime.h"
namespace W
{
	Demian::Demian():
		m_fCreateTime(20.f),
		m_fCurCreateTime(0.f)
	{
		SetName(L"Demian1");

		MeshRenderer* pRenderer = AddComponent<MeshRenderer>();
		pRenderer->SetMesh(Resources::Find<Mesh>(L"RectMesh"));


		std::shared_ptr<Material> pMater = std::make_shared<Material>();
		pMater->SetRenderinMode(eRenderingMode::Transparent);
		pMater->SetShader(Resources::Find<Shader>(L"MonsterShader"));
		Resources::Insert(L"DemianMater", pMater);

		pRenderer->SetMaterial(pMater);
		AddComponent<Rigidbody>();

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

		pAnim->EndEvent(L"Demian1_attack2_left") = std::bind(&Demian::move, this);
		pAnim->EndEvent(L"Demian1_attack2_right") = std::bind(&Demian::move, this);


	}
	Demian::~Demian()
	{
		ObjectPoolManager::ReleaseObject(L"demianSword");
		ObjectPoolManager::ReleaseObject(L"SwordExplode");
		ObjectPoolManager::ReleaseObject(L"KeyAttackObj");
		ObjectPoolManager::ReleaseObject(L"SpawnObj");
		ObjectPoolManager::ReleaseObject(L"Demian_attack0");
		ObjectPoolManager::ReleaseObject(L"Demian_attack1");
		ObjectPoolManager::ReleaseObject(L"Demian_attack2");
		ObjectPoolManager::ReleaseObject(L"Demian_attack3");
	}

	void Demian::Initialize()
	{
		//위치 내리기
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
	void Demian::Update()
	{
		check_time();

		Monster::Update();
	}
	void Demian::LateUpdate()
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
	void Demian::Render()
	{
		Monster::Render();
	}
	void Demian::add_skill()
	{
		DemianSword* pSword = new DemianSword();
		pSword->SetOnwer(this);
		pSword->Initialize();
		pSword->SetName(L"demianSword");
		AddMonsterSkill(pSword);
		SceneManger::AddGameObject(eLayerType::MonsterAttack, GetMonsterSkill(L"demianSword"));
		
		SwordExplode* pExplode = new SwordExplode();
		pExplode->SetSword(pSword);
		pExplode->SetOnwer(this);
		pExplode->Initialize();
		pExplode->SetName(L"SwordExplode");
		AddMonsterSkill(pExplode);


		//키입력 오브젝트
		for (int i = 0; i < 5; ++i)
		{
			DemianKeyAttack* pKeyAttack = new DemianKeyAttack();
			pKeyAttack->SetName(L"KeyAttackObj");
			pKeyAttack->SetOnwer(this);
			AddMonsterSkill(pKeyAttack);
		}

		//데미안 불덩이들 소환 오브젝트
		SpawnMonsterAttack* pSpawnObj = new SpawnMonsterAttack();
		pSpawnObj->SetName(L"SpawnObj");
		pSpawnObj->SetOnwer(this);
		AddMonsterSkill(pSpawnObj);

		for (int i = 0; i < 4; ++i)
		{
			DemianExplode* pAttack0 = new DemianExplode();
			pAttack0->SetName(L"Demian_attack0");
			pAttack0->GetScript<MonsterAttackScript>()->SeteAbnormalType(BattleManager::eAbnormalType::Stigma);
			pAttack0->SetOnwer(this);
			AddMonsterSkill(pAttack0);
		}

		MonsterAttackObject* pAttack1 = new MonsterAttackObject();
		pAttack1->GetScript<MonsterAttackScript>()->SeteAbnormalType(BattleManager::eAbnormalType::Stigma);
		pAttack1->SetName(L"Demian_attack1");
		pAttack1->SetOnwer(this);
		AddMonsterSkill(pAttack1);

		MonsterAttackObject* pAttack2 = new MonsterAttackObject();
		pAttack2->GetScript<MonsterAttackScript>()->SeteAbnormalType(BattleManager::eAbnormalType::Stigma);
		pAttack2->SetName(L"Demian_attack2");
		pAttack2->SetOnwer(this);
		AddMonsterSkill(pAttack2);

		for (int i = 0; i < 20; ++i)
		{
			DemianFire0* pAttack3 = new DemianFire0();
			pAttack3->SetName(L"Demian_attack3");
			pAttack3->SetOnwer(this);
			AddMonsterSkill(pAttack3);
		}

	}
	void Demian::setattack()
	{
		MonsterScript* Pscript = GetComponent<MonsterScript>();
		Vector3 vPosition = GetComponent<Transform>()->GetPosition();

		tMonsterAttack attack0 = {};
		attack0.bSkill = true;
		
		attack0.tTime.fCoolTime = 30.f;
		
		attack0.pFunction = std::bind(&Demian::attack0, this);
		
		attack0.iStartFrame = 4;
		attack0.iEndFrame = 5;
		
		Pscript->AddAttack(attack0);
		
		//2
		tMonsterAttack attack1 = {};
		
		attack1.tTime.fCoolTime = 18.f;
		attack1.vPosition = vPosition;
		attack1.vScale = Vector2(4.f, 2.f);
		attack1.vOffset = Vector2(3.5f, 0.f);
		attack1.tAttackInfo.fAttackDamage = BattleManager::GetMaxDamage();
		
		attack1.pFunction = std::bind(&Demian::attack1, this);
		
		attack1.iStartFrame = 28;
		attack1.iEndFrame = 30;
		
		Pscript->AddAttack(attack1);
		
		////3
		tMonsterAttack attack2 = {};
		attack2.vPosition = vPosition;
		attack2.vScale = Vector2(3.f, 2.f);
		attack2.vOffset = Vector2(3.5f, 0.f);
		attack2.tAttackInfo.fAttackDamage = BattleManager::GetMaxDamage();
		attack2.tTime.fCoolTime = 16.f;
		
		attack2.pFunction = std::bind(&Demian::attack2, this);
		
		attack2.iStartFrame = 32;
		attack2.iEndFrame = 34;
		Pscript->AddAttack(attack2);
		
		//
		//
		tMonsterAttack attack3 = {};
		attack3.bSkill = true;
		attack3.tTime.fCoolTime = 30.f;
		
		attack3.pFunction = std::bind(&Demian::attack3, this);
		
		attack3.iStartFrame = 18;
		attack3.iEndFrame = 113;
		Pscript->AddAttack(attack3);

	}

	void Demian::attack0()
	{
		Vector3 vStartPos = GetComponent<Transform>()->GetPosition();
		vStartPos.z -= 0.1f;
		vStartPos.y += 1.f;
		srand(time(NULL));
		for (int i = -2; i < 2; ++i)
		{
			int iIndx = (rand() % 4);

			float fOffsetX = i * 4.3f + vStartPos.x;
			fOffsetX += iIndx * 0.7f;

			
			MonsterAttackObject* attack0 = GetMonsterSkill(L"Demian_attack0");
			if (attack0 == nullptr)
				return;

			attack0->GetComponent<Transform>()->SetPosition(fOffsetX, vStartPos.y, vStartPos.z);
			EventManager::CreateObject(attack0, eLayerType::MonsterAttack);
			
			attack0->Initialize();
		}
	}
	void Demian::attack1()
	{
		MonsterAttackObject* attack1 = GetMonsterSkill(L"Demian_attack1");
		if (attack1 == nullptr)
			return;
		MonsterScript* pMonsterScript = GetScript<MonsterScript>();
		pMonsterScript->SetMonsterAttack(attack1);

		EventManager::CreateObject(attack1, eLayerType::MonsterAttack);
	}

	void Demian::attack2()
	{
		MonsterAttackObject* attack2 = GetMonsterSkill(L"Demian_attack2");
		if (attack2 == nullptr)
			return;
		MonsterScript* pMonsterScript = GetScript<MonsterScript>();
		pMonsterScript->SetMonsterAttack(attack2);

		EventManager::CreateObject(attack2, eLayerType::MonsterAttack);
	}

	void Demian::attack3()
	{
		MonsterAttackObject* attack2 = GetMonsterSkill(L"SpawnObj");
		if (attack2 == nullptr)
			return;
		SpawnMonsterAttack* pSpawn = dynamic_cast<SpawnMonsterAttack*>(attack2);
	
		pSpawn->SetOnwer(this);

		//위치 초기화
		Vector3 vPosition =GetComponent<Transform>()->GetPosition();
		vPosition.y += 3.4;
		pSpawn->GetComponent<Transform>()->SetPosition(vPosition);

		pSpawn->Initialize();
		
		//속도 설정
		Vector2 vLook[5] = { Vector2{0.7f,-0.7f}, Vector2{0.5f,-0.5f} , Vector2{0,-1.f},
			Vector2{-0.5f,-0.5f},Vector2{-0.7f,-0.7f} };
		for (int i = 0; i < 5; ++i)
			pSpawn->SetVelocity(vLook[i]);

		//spawn 객체에서 몬스터 기술 가져오기
		pSpawn->SetTime(2.f);
		pSpawn->SetAttackName(L"Demian_attack3");
		pSpawn->SetCreateCount(5);
		pSpawn->SetEndFrame(113);
		EventManager::CreateObject(pSpawn, eLayerType::MonsterAttack);

	}

	void Demian::move()
	{
		Vector3 vPosition = GetComponent<Transform>()->GetPosition();
		vPosition.x += (GetDir() * 4.38f);
		GetComponent<Transform>()->SetPosition(vPosition);
	}
	void Demian::check_time()
	{
		m_fCurCreateTime += Time::DeltaTime();
		if (m_fCurCreateTime >= m_fCreateTime)
		{
			m_fCurCreateTime = 0.f;
			create();
		}
	}

	void Demian::create()
	{
		Vector3 vStartPos = GetComponent<Transform>()->GetPosition();
		vStartPos.z -= 0.1f;
		vStartPos.y += 1.f;
		srand(time(NULL));
		for (int i = -2; i < 3; ++i)
		{
			int iIndx = (rand() % 4);

			float fOffsetX = i * 3.f + vStartPos.x;
			fOffsetX += iIndx * 0.7f;

			MonsterAttackObject* attack0 = GetMonsterSkill(L"KeyAttackObj");
			if (attack0 == nullptr)
				return;

			DemianKeyAttack* pAttack = dynamic_cast<DemianKeyAttack*>(attack0);

			std::random_device rDiv;
			std::mt19937 en(rDiv());
			std::uniform_int_distribution<int> time(4, 8);
			float fTime = (float)time(en);
			pAttack->SetTime(fTime);

			attack0->GetComponent<Transform>()->SetPosition(fOffsetX, vStartPos.y, vStartPos.z);
			EventManager::CreateObject(attack0, eLayerType::MonsterAttack);

			attack0->Initialize();
		}
		
	}
}