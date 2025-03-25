#include "WMegnus.h"
#include "WResources.h"
#include "WRigidbody.h"
#include "WAnimator.h"
#include "WEffect.h"
#include "WMonsterScript.h"
#include "WMonsterStand.h"
#include "WMonsterMove.h"
#include "WMonsterAttack.h"
#include "WMonsterDead.h"
#include "WMegnusStone.h"
#include "WCloneMegnus.h"
#include "WMonsterMoveAttack.h"
#include "WMobZone.h"
#include "WSceneManger.h"
#include "WEventManager.h"
#include "WMegnusAttack.h"
#include "WTime.h"
#include "WSleepGas.h"
namespace W
{
	Megnus::Megnus() :
		m_pZone(nullptr),
		m_pGas(nullptr),
		m_fCreateTime(1.25f),
		m_fCurCreateTime(0.f),
		m_fGasTime(15.f),
		m_fCurGasTime(0.f),
		m_iCurLevel(0)
	{
		SetName(L"Megnus");

		MeshRenderer* pRenderer = AddComponent<MeshRenderer>();
		pRenderer->SetMesh(Resources::Find<Mesh>(L"RectMesh"));


		std::shared_ptr<Material> pMater = std::make_shared<Material>();
		pMater->SetRenderinMode(eRenderingMode::Transparent);
		pMater->SetShader(Resources::Find<Shader>(L"MonsterShader"));
		Resources::Insert(L"MegnuslMater", pMater);

		pRenderer->SetMaterial(pMater);

		std::shared_ptr<Texture> pAtlas1 = Resources::Find<Texture>(L"Megnus1");
		std::shared_ptr<Texture> pAtlas2 = Resources::Find<Texture>(L"Megnus2");

		AddComponent<Rigidbody>();

		Animator* pAnim = AddComponent<Animator>();

		pAnim->Create(L"Megnus_stand_left", pAtlas1, Vector2(0.f, 0.f), Vector2(1100.f, 550.f), 8, Vector2(1100.f, 1100.f), Vector2::Zero, 0.15f);
		pAnim->Create(L"Megnus_move_left", pAtlas1, Vector2(0.f, 550.f), Vector2(1100.f, 550.f), 8, Vector2(1100.f, 1100.f), Vector2::Zero, 0.15f);
		pAnim->Create(L"Megnus_attack0_left", pAtlas1, Vector2(0.f, 1100.f), Vector2(1100.f, 550.f), 9, Vector2(1100.f, 1100.f), Vector2::Zero, 0.15f);
		pAnim->FindAnimation(L"Megnus_attack0_left")->Create(L"Megnus_attack0_left", pAtlas1, Vector2(0.f, 1650.f), Vector2(1100.f, 550.f), 9, Vector2(1100.f, 1100.f), Vector2::Zero, 0.15f);
		pAnim->FindAnimation(L"Megnus_attack0_left")->Create(L"Megnus_attack0_left", pAtlas1, Vector2(0.f, 2200.f), Vector2(1100.f, 550.f), 7, Vector2(1100.f, 1100.f), Vector2::Zero, 0.15f);
		pAnim->Create(L"Megnus_attack1_left", pAtlas1, Vector2(0.f, 2750.f), Vector2(1100, 550.f), 9, Vector2(1100.f, 1100.f), Vector2::Zero, 0.15f);
		pAnim->FindAnimation(L"Megnus_attack1_left")->Create(L"Megnus_attack1_left", pAtlas1, Vector2(0.f, 3300), Vector2(1100.f, 550.f), 8, Vector2(1100.f, 1100.f), Vector2::Zero, 0.15f);
		pAnim->Create(L"Megnus_attack2_left", pAtlas1, Vector2(0.f, 3850), Vector2(1100.f, 550.f), 9, Vector2(1100.f, 1100.f), Vector2::Zero, 0.15f);
		pAnim->FindAnimation(L"Megnus_attack2_left")->Create(L"Megnus_attack2_left", pAtlas1, Vector2(0.f, 4400.f), Vector2(1100.f, 550.f), 9, Vector2(1100.f, 1100.f), Vector2::Zero, 0.15f);
		pAnim->FindAnimation(L"Megnus_attack2_left")->Create(L"Megnus_attack2_left", pAtlas1, Vector2(0.f, 4950.f), Vector2(1100.f, 550.f), 6, Vector2(1100.f, 1100.f), Vector2::Zero, 0.15f);
		pAnim->Create(L"Megnus_attack3_left", pAtlas1, Vector2(0.f, 5500.f), Vector2(1100.f, 550.f), 9, Vector2(1100.f, 1100.f), Vector2::Zero, 0.15f);
		pAnim->FindAnimation(L"Megnus_attack3_left")->Create(L"Megnus_attack3_left", pAtlas1, Vector2(0.f, 6050), Vector2(1100.f, 550.f), 9, Vector2(1100.f, 1100.f), Vector2::Zero, 0.15f);
		pAnim->FindAnimation(L"Megnus_attack3_left")->Create(L"Megnus_attack3_left", pAtlas1, Vector2(0.f, 6600.f), Vector2(1100.f, 550.f), 9, Vector2(1100.f, 1100.f), Vector2::Zero, 0.15f);
		pAnim->FindAnimation(L"Megnus_attack3_left")->Create(L"Megnus_attack3_left", pAtlas1, Vector2(0.f, 7150.f), Vector2(1100.f, 550.f), 9, Vector2(1100.f, 1100.f), Vector2::Zero, 0.15f);
		pAnim->FindAnimation(L"Megnus_attack3_left")->Create(L"Megnus_attack3_left", pAtlas1, Vector2(0.f, 7700), Vector2(1100.f, 550.f), 6, Vector2(1100.f, 1100.f), Vector2::Zero, 0.15f);

		pAnim->Create(L"Megnus_stand_right", pAtlas1, Vector2(8800.f, 0.f), Vector2(-1100.f, 550.f), 8, Vector2(1100.f, 1100.f), Vector2::Zero, 0.15f);
		pAnim->Create(L"Megnus_move_right", pAtlas1, Vector2(8800.f, 550.f), Vector2(-1100.f, 550.f), 8, Vector2(1100.f, 1100.f), Vector2::Zero, 0.15f);
		pAnim->Create(L"Megnus_attack0_right", pAtlas1, Vector2(8800.f, 1100.f), Vector2(-1100.f, 550.f), 9, Vector2(1100.f, 1100.f), Vector2::Zero, 0.15f);
		pAnim->FindAnimation(L"Megnus_attack0_right")->Create(L"Megnus_attack0_right", pAtlas1, Vector2(8800.f, 1650.f), Vector2(-1100.f, 550.f), 9, Vector2(1100.f, 1100.f), Vector2::Zero, 0.15f);
		pAnim->FindAnimation(L"Megnus_attack0_right")->Create(L"Megnus_attack0_right", pAtlas1, Vector2(8800.f, 2200.f), Vector2(-1100.f, 550.f), 7, Vector2(1100.f, 1100.f), Vector2::Zero, 0.15f);
		pAnim->Create(L"Megnus_attack1_right", pAtlas1, Vector2(8800.f, 2750.f), Vector2(-1100, 550.f), 9, Vector2(1100.f, 1100.f), Vector2::Zero, 0.15f);
		pAnim->FindAnimation(L"Megnus_attack1_right")->Create(L"Megnus_attack1_right", pAtlas1, Vector2(8800.f, 3300), Vector2(-1100.f, 550.f), 8, Vector2(1100.f, 1100.f), Vector2::Zero, 0.15f);
		pAnim->Create(L"Megnus_attack2_right", pAtlas1, Vector2(8800.f, 3850), Vector2(-1100.f, 550.f), 9, Vector2(1100.f, 1100.f), Vector2::Zero, 0.15f);
		pAnim->FindAnimation(L"Megnus_attack2_right")->Create(L"Megnus_attack2_right", pAtlas1, Vector2(8800.f, 4400.f), Vector2(-1100.f, 550.f), 9, Vector2(1100.f, 1100.f), Vector2::Zero, 0.15f);
		pAnim->FindAnimation(L"Megnus_attack2_right")->Create(L"Megnus_attack2_right", pAtlas1, Vector2(8800.f, 4950.f), Vector2(-1100.f, 550.f), 6, Vector2(1100.f, 1100.f), Vector2::Zero, 0.15f);
		pAnim->Create(L"Megnus_attack3_right", pAtlas1, Vector2(8800.f, 5500), Vector2(-1100.f, 550.f), 9, Vector2(1100.f, 1100.f), Vector2::Zero, 0.15f);
		pAnim->FindAnimation(L"Megnus_attack3_right")->Create(L"Megnus_attack3_right", pAtlas1, Vector2(8800.f, 6050.f), Vector2(-1100.f, 550.f), 9, Vector2(1100.f, 1100.f), Vector2::Zero, 0.15f);
		pAnim->FindAnimation(L"Megnus_attack3_right")->Create(L"Megnus_attack3_right", pAtlas1, Vector2(8800.f, 6600.f), Vector2(-1100.f, 550.f), 9, Vector2(1100.f, 1100.f), Vector2::Zero, 0.15f);
		pAnim->FindAnimation(L"Megnus_attack3_right")->Create(L"Megnus_attack3_right", pAtlas1, Vector2(8800.f, 7150.f), Vector2(-1100.f, 550.f), 9, Vector2(1100.f, 1100.f), Vector2::Zero, 0.15f);
		pAnim->FindAnimation(L"Megnus_attack3_right")->Create(L"Megnus_attack3_right", pAtlas1, Vector2(8800.f, 7700.f), Vector2(-1100.f, 550.f), 6, Vector2(1100.f, 1100.f), Vector2::Zero, 0.15f);

		pAnim->Create(L"Megnus_attack4_left", pAtlas2, Vector2(0.f, 0.f), Vector2(1100.f, 550.f), 9, Vector2(1100.f, 1100.f), Vector2::Zero, 0.15f);
		pAnim->FindAnimation(L"Megnus_attack4_left")->Create(L"Megnus_attack4_left", pAtlas2, Vector2(0.f, 550.f), Vector2(1100.f, 550.f), 9, Vector2(1100.f, 1100.f), Vector2::Zero, 0.15f);
		pAnim->FindAnimation(L"Megnus_attack4_left")->Create(L"Megnus_attack4_left", pAtlas2, Vector2(0.f, 1100.f), Vector2(1100.f, 550.f), 9, Vector2(1100.f, 1100.f), Vector2::Zero, 0.15f);
		pAnim->FindAnimation(L"Megnus_attack4_left")->Create(L"Megnus_attack4_left", pAtlas2, Vector2(0.f, 1650.f), Vector2(1100.f, 550.f), 8, Vector2(1100.f, 1100.f), Vector2::Zero, 0.15f);
		pAnim->Create(L"Megnus_attack5_left", pAtlas2, Vector2(0.f, 2200.f), Vector2(1100.f, 550.f), 9, Vector2(1100.f, 1100.f), Vector2::Zero, 0.15f);
		pAnim->FindAnimation(L"Megnus_attack5_left")->Create(L"Megnus_attack5_left", pAtlas2, Vector2(0.f, 2750.f), Vector2(1100.f, 550.f), 9, Vector2(1100.f, 1100.f), Vector2::Zero, 0.15f);
		pAnim->Create(L"Megnus_attack6_left", pAtlas2, Vector2(0.f, 3300.f), Vector2(1100.f, 550.f), 9, Vector2(1100.f, 1100.f), Vector2::Zero, 0.15f);
		pAnim->FindAnimation(L"Megnus_attack6_left")->Create(L"Megnus_attack6_left", pAtlas2, Vector2(0.f, 3850.f), Vector2(1100.f, 550.f), 9, Vector2(1100.f, 1100.f), Vector2::Zero, 0.15f);
		pAnim->Create(L"Megnus_dead_left", pAtlas2, Vector2(0.f, 4400.f), Vector2(1100.f, 550.f), 9, Vector2(1100.f, 1100.f), Vector2::Zero, 0.15f);
		pAnim->FindAnimation(L"Megnus_dead_left")->Create(L"Megnus_dead_left", pAtlas2, Vector2(0.f, 4950.f), Vector2(1100.f, 550.f), 9, Vector2(1100.f, 1100.f), Vector2::Zero, 0.15f);
		pAnim->FindAnimation(L"Megnus_dead_left")->Create(L"Megnus_dead_left", pAtlas2, Vector2(0.f, 5500.f), Vector2(1100.f, 550.f), 8, Vector2(1100.f, 1100.f), Vector2::Zero, 0.15f);

		pAnim->Create(L"Megnus_attack4_right", pAtlas2, Vector2(8800.f, 0.f), Vector2(-1100.f, 550.f), 9, Vector2(1100.f, 1100.f), Vector2::Zero, 0.15f);
		pAnim->FindAnimation(L"Megnus_attack4_right")->Create(L"Megnus_attack4_right", pAtlas2, Vector2(8800.f, 550.f), Vector2(-1100.f, 550.f), 9, Vector2(1100.f, 1100.f), Vector2::Zero, 0.15f);
		pAnim->FindAnimation(L"Megnus_attack4_right")->Create(L"Megnus_attack4_right", pAtlas2, Vector2(8800.f, 1100.f), Vector2(-1100.f, 550.f), 9, Vector2(1100.f, 1100.f), Vector2::Zero, 0.15f);
		pAnim->FindAnimation(L"Megnus_attack4_right")->Create(L"Megnus_attack4_right", pAtlas2, Vector2(8800.f, 1650.f), Vector2(-1100.f, 550.f), 8, Vector2(1100.f, 1100.f), Vector2::Zero, 0.15f);
		pAnim->Create(L"Megnus_attack5_right", pAtlas2, Vector2(8800.f, 2200.f), Vector2(-1100.f, 550.f), 9, Vector2(1100.f, 1100.f), Vector2::Zero, 0.15f);
		pAnim->FindAnimation(L"Megnus_attack5_right")->Create(L"Megnus_attack5_right", pAtlas2, Vector2(8800.f, 2750.f), Vector2(-1100.f, 550.f), 9, Vector2(1100.f, 1100.f), Vector2::Zero, 0.15f);
		pAnim->Create(L"Megnus_attack6_right", pAtlas2, Vector2(8800.f, 3300.f), Vector2(-1100.f, 550.f), 9, Vector2(1100.f, 1100.f), Vector2::Zero, 0.15f);
		pAnim->FindAnimation(L"Megnus_attack6_right")->Create(L"Megnus_attack6_right", pAtlas2, Vector2(8800.f, 3850.f), Vector2(-1100.f, 550.f), 9, Vector2(1100.f, 1100.f), Vector2::Zero, 0.15f);
		pAnim->Create(L"Megnus_dead_right", pAtlas2, Vector2(8800.f, 4400.f), Vector2(-1100.f, 550.f), 9, Vector2(1100.f, 1100.f), Vector2::Zero, 0.15f);
		pAnim->FindAnimation(L"Megnus_dead_right")->Create(L"Megnus_dead_right", pAtlas2, Vector2(8800.f, 4950.f), Vector2(1100.f, 550.f), 9, Vector2(1100.f, 1100.f), Vector2::Zero, 0.15f);
		pAnim->FindAnimation(L"Megnus_dead_right")->Create(L"Megnus_dead_right", pAtlas2, Vector2(8800.f, 5500.f), Vector2(1100.f, 550.f), 8, Vector2(1100.f, 1100.f), Vector2::Zero, 0.15f);

	}
	Megnus::~Megnus()
	{
		ObjectPoolManager::ReleaseObject(L"Megnus_Stone");
		ObjectPoolManager::ReleaseObject(L"Megnus_attack0");
		ObjectPoolManager::ReleaseObject(L"Megnus_attack1");
		ObjectPoolManager::ReleaseObject(L"Megnus_attack2");
		ObjectPoolManager::ReleaseObject(L"Megnus_attack3");
		ObjectPoolManager::ReleaseObject(L"Megnus_attack4");
	}
	void Megnus::Initialize()
	{
		GetComponent<Transform>()->SetScale(10.f, 10.f, 0.f);
		GetComponent<Transform>()->SetPosition(0.1f, -1.f, -1.5f);
		Collider2D* pCollider = AddComponent<Collider2D>();
		pCollider->SetSize(Vector2(0.16f, 0.16f));
		pCollider->SetCenter(Vector2(0.f, -0.7f));

		MonsterScript* Pscript = AddComponent<MonsterScript>();
		Pscript->SetBoss();
		Pscript->Initialize();
		Pscript->CreateHP();

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
	void Megnus::Update()
	{
		check_time();
		check_HP();

		Monster::Update();
	}
	void Megnus::LateUpdate()
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
	void Megnus::Render()
	{
		Monster::Render();
	}
	void Megnus::add_skill()
	{
		//운석
		for (int i = 0; i < 30; ++i)
		{
			MegnusStone* pStone = new MegnusStone();
			pStone->SetName(L"Megnus_Stone");
			AddMonsterSkill(pStone);
		}

		//mobzone
		m_pZone = new MobZone();
		m_pZone->SetOwner(this);
		m_pZone->Initialize();
		SceneManger::AddGameObject(eLayerType::Object, m_pZone);


		//attack0
		MonsterAttackObject* pAttack0 = new MonsterAttackObject();
		pAttack0->SetName(L"Megnus_attack0");
		AddMonsterSkill(pAttack0);

		//attack1
		for (int i = 0; i < 7; ++i)
		{
			CloneMegnus* pMegnusClone = new CloneMegnus();
			pMegnusClone->SetName(L"Megnus_attack1");
			AddMonsterSkill(pMegnusClone);
		}

		//attack2
		MonsterMoveAttack* attack2 = new MonsterMoveAttack();
		attack2->SetName(L"Megnus_attack2");
		AddMonsterSkill(attack2);

		//attack3
		for (int i = -1; i <= 1; i += 2)
		{
			MegnusAttack* attack3 = new MegnusAttack();
			attack3->SetDir(i);
			//애니메이션 공격 끝나는 프레임
			attack3->SetName(L"Megnus_attack3");
			AddMonsterSkill(attack3);
		}

		MonsterAttackObject* attack4 = new MonsterAttackObject();
		attack4->SetName(L"Megnus_attack4");
		AddMonsterSkill(attack4);

		//가스
		m_pGas = new SleepGas();
		m_pGas->SetOnwer(this);
		m_pGas->GetComponent<Transform>()->SetPosition(10.f, -1.95f, -1.5f);
		SceneManger::AddGameObject(eLayerType::MonsterAttack, m_pGas);
	}
	void Megnus::setattack()
	{
		MonsterScript* Pscript = GetComponent<MonsterScript>();
		Vector3 vPosition = GetComponent<Transform>()->GetPosition();

		tMonsterAttack attack1 = {};
		attack1.tTime.fCoolTime = 15.f;

		attack1.vScale = Vector2(2.5f, 1.f);
		attack1.vOffset = Vector2(0.f, -1.5f);
		attack1.vPosition = vPosition;
		attack1.tAttackInfo.fAttackDamage = 10.f;
		attack1.pFunction = std::bind(&Megnus::attack0, this);

		attack1.iStartFrame = 18;
		attack1.iEndFrame = 23;

		Pscript->AddAttack(attack1);

		//2
		tMonsterAttack attack2 = {};
		attack2.bSkill = true;

		attack2.tTime.fCoolTime = 20.f;
		attack2.vScale = Vector2(3.f, 3.f);

		attack2.pFunction = std::bind(&Megnus::attack1, this);

		attack2.iStartFrame = 12;
		attack2.iEndFrame = 13;

		Pscript->AddAttack(attack2);

		////3
		tMonsterAttack attack3 = {};
		attack3.vPosition = vPosition;
		attack3.vScale = Vector2(3.f, 2.f);
		attack3.vOffset = Vector2(0.f, -1.f);
		attack3.tTime.fCoolTime = 10.f;

		attack3.pFunction = std::bind(&Megnus::attack2, this);

		attack3.iStartFrame = 15;
		attack3.iEndFrame = 18;
		Pscript->AddAttack(attack3);

		//
		//
		tMonsterAttack attack4 = {};
		attack4.bSkill = true;
		attack4.tTime.fCoolTime = 15.f;
		//attack4.tTime.fCurTime = 5.f;

		attack4.vScale = Vector2(0.f, 0.f);
		attack4.pFunction = std::bind(&Megnus::attack3, this);

		attack4.iStartFrame = 27;
		attack4.iEndFrame = 37;
		Pscript->AddAttack(attack4);

		tMonsterAttack attack5 = {};
		attack5.tTime.fCoolTime = 20.f;
		//attack5.tTime.fCurTime = 20.f;
		attack5.vScale = Vector2(3.f, 3.f);
		attack5.vOffset = Vector2(0.f, -0.7f);
		attack5.vPosition = vPosition;
		attack5.tAttackInfo.fAttackDamage = 10.f;

		attack5.pFunction = std::bind(&Megnus::attack4, this);

		attack5.iStartFrame = 28;
		attack5.iEndFrame = 30;
		Pscript->AddAttack(attack5);

		tMonsterAttack attack6 = {};
		attack6.bSkill = true;
		attack6.tTime.fCoolTime = 40.f;
		attack6.tTime.fCurTime = 40.f;

		attack6.pFunction = std::bind(&Megnus::attack5, this);

		attack6.iStartFrame = 10;
		attack6.iEndFrame = 11;
		Pscript->AddAttack(attack6);

		tMonsterAttack attack7 = {};
		attack7.bSkill = true;
		attack7.tTime.fCoolTime = 30.f;
		//attack7.tTime.fCurTime = 30.f;
		attack7.pFunction = std::bind(&Megnus::attack6, this);

		attack7.iStartFrame = 10;
		attack7.iEndFrame = 11;
		Pscript->AddAttack(attack7);
	}
	void Megnus::attack0()
	{
		MonsterAttackObject* attack0 = GetMonsterSkill(L"Megnus_attack0");
		if (attack0 == nullptr)
			return;
		MonsterScript* pMonsterScript = GetScript<MonsterScript>();
		pMonsterScript->SetMonsterAttack(attack0);
		attack0->SetOnwer(this);

		EventManager::CreateObject(attack0, eLayerType::MonsterAttack);
	}
	void Megnus::attack1()
	{
		Vector3 vStartPos = GetComponent<Transform>()->GetPosition();
		vStartPos.z -= 0.1f;
		vStartPos.y -= 0.5f;
		srand(time(NULL));
		for (int i = -3; i < 4; ++i)
		{
			int iIndx = (rand() % 4);

			float fOffsetX = i * 3.f + vStartPos.x;
			fOffsetX += iIndx * 0.5f;

			MonsterAttackObject* clone = GetMonsterSkill(L"Megnus_attack1");
			if (clone == nullptr)
				return;
			clone->SetOnwer(this);

			clone->GetComponent<Transform>()->SetPosition(fOffsetX, vStartPos.y, vStartPos.z);
			clone->Initialize();
			EventManager::CreateObject(clone, eLayerType::MonsterAttack);
		}
	}
	void Megnus::attack2()
	{
		MonsterAttackObject* attack2 = GetMonsterSkill(L"Megnus_attack2");
		if (attack2 == nullptr)
			return;
		MonsterScript* pMonsterScript = GetScript<MonsterScript>();
		pMonsterScript->SetMonsterAttack(attack2);
		attack2->SetOnwer(this);

		EventManager::CreateObject(attack2, eLayerType::MonsterAttack);
	}
	void Megnus::attack3()
	{
		for (int i = 0; i < 2; ++i)
		{
			MonsterAttackObject* attack3 = GetMonsterSkill(L"Megnus_attack3");
			if (attack3 == nullptr)
				return;

			Vector3 vPosition = GetComponent<Transform>()->GetPosition();
			attack3->GetComponent<Transform>()->SetPosition(vPosition);
			attack3->SetOnwer(this);
			attack3->Initialize();

			EventManager::CreateObject(attack3, eLayerType::MonsterAttack);
		}
	}
	void Megnus::attack4()
	{
		MonsterAttackObject* attack4 = GetMonsterSkill(L"Megnus_attack4");
		if (attack4 == nullptr)
			return;

		MonsterScript* pMonsterScript = GetScript<MonsterScript>();
		pMonsterScript->SetMonsterAttack(attack4);
		attack4->SetOnwer(this);

		EventManager::CreateObject(attack4, eLayerType::MonsterAttack);
	}
	void Megnus::attack5()
	{
		//슬로우
		BattleManager::HitchAbnormal(BattleManager::eAbnormalType::Slow, -1.2f);
	}
	void Megnus::attack6()
	{
		//언데드화
		BattleManager::HitchAbnormal(BattleManager::eAbnormalType::Undead);
	}
	void Megnus::create_stone()
	{
		MonsterAttackObject* pObj = GetMonsterSkill(L"Megnus_Stone");
		if (pObj == nullptr)
			return;

		std::random_device rDiv;
		std::mt19937 en(rDiv());
		std::uniform_int_distribution<int> disX(-13, 13);
		std::uniform_int_distribution<int> disY(2, 4);
		float fPosX = (float)disX(en);
		float fPosY = (float)disY(en);
		Vector3 vPosition = Vector3(fPosX, fPosY, -1.5f);

		pObj->GetComponent<Transform>()->SetPosition(vPosition);
		pObj->SetOnwer(this);
		pObj->Initialize();

		EventManager::CreateObject(pObj, eLayerType::MonsterAttack);

	}

	void Megnus::create_gas()
	{
		
		std::random_device rDiv;
		std::mt19937 en(rDiv());
		std::uniform_int_distribution<int> disX(-13, 12);
		float fPosX = (float)disX(en);

		if((fPosX >= 0))
			fPosX = 10.f;
		else
			fPosX = -10.f;

		Vector3 vPosition = Vector3(fPosX, -1.95f, -1.5f);
		
		m_pGas->GetComponent<Transform>()->SetPosition(vPosition);

		m_pGas->start();
	}

	void Megnus::check_time()
	{
		if (!m_pGas->m_bStart)
		{
			m_fCurGasTime += Time::DeltaTime();
			if (m_fCurGasTime >= m_fGasTime)
			{
				m_fCurGasTime = 0.f;
				create_gas();
			}
		}


		m_fCurCreateTime += Time::DeltaTime();
		if (m_fCurCreateTime >= m_fCreateTime)
		{
			m_fCurCreateTime = 0.f;
			create_stone();
		}

	}

	void Megnus::check_HP()
	{
		const tObjectInfo& tInfo = GetScript<MonsterScript>()->GetObjectInfo();
		float fRatio = tInfo.fHP/ tInfo.fMaxHP;
		
		UINT iLevel = 0;
		if (fRatio < 0.75f && fRatio>0.5f)
			iLevel = 1;

		else if (fRatio < 0.5f && fRatio>.25f)
			iLevel = 2;

		else if (fRatio < 0.25f && fRatio > 0.f)
			iLevel = 3;

		else if (fRatio <= 0.f)
			iLevel = 4;

		if (m_iCurLevel != iLevel)
		{
			m_iCurLevel = iLevel;
			m_pZone->SetLevel(m_iCurLevel);

			//더 빨리 생성하게
			m_fCreateTime -= 0.15f;
			m_fGasTime -= 0.15f;
		}
	}

}