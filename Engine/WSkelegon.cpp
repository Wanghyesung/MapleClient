#include "WSkelegon.h"
#include "WAnimator.h"
#include "WRigidbody.h"
#include "WResources.h"
#include "WMonsterScript.h"

#include "WMonsterFSM.h"
#include "WMonsterAttack.h"
#include "WMonsterStand.h"
#include "WMonsterMove.h"
#include "WMonsterHit.h"
#include "WSceneManger.h"
#include "WEffect.h"
#include "WMonsterDead.h"

namespace W
{
	Skelegon::Skelegon():
		m_spAttackEffect(nullptr)
	{
		SetName(L"skelegon");

		MeshRenderer* mr = AddComponent<MeshRenderer>();
		mr->SetMesh(Resources::Find<Mesh>(L"RectMesh"));

		std::shared_ptr<Material> pMater = std::make_shared<Material>();
		pMater->SetRenderinMode(eRenderingMode::Transparent);
		pMater->SetShader(Resources::Find<Shader>(L"MonsterShader"));
		Resources::Insert(L"skelegonMater", pMater);

		mr->SetMaterial(pMater);

		Animator* pAnimator = AddComponent<Animator>();
		std::shared_ptr<Texture> pAtlas
			= Resources::Load<Texture>(L"SkelegonTex", L"..\\Resources\\Texture\\Monster\\skelegon.png");
		pAnimator->Create(L"skelegon_stand_left", pAtlas, Vector2(0.0f, 0.0f), Vector2(600.0f, 200.0f), 6, Vector2(600.f, 200.f));
		pAnimator->Create(L"skelegon_move_left", pAtlas, Vector2(0.0f, 200.0f), Vector2(600.0f, 200.0f), 4, Vector2(600.f, 200.f));
		pAnimator->Create(L"skelegon_attack0_left", pAtlas, Vector2(0.0f, 400.0f), Vector2(600.0f, 200.0f), 11, Vector2(600.f, 200.f), Vector2::Zero, 0.2f);
		pAnimator->Create(L"skelegon_dead_left", pAtlas, Vector2(0.0f, 600.0f), Vector2(600.0f, 200.0f), 8, Vector2(600.f, 200.f), Vector2::Zero, 0.15f);
		pAnimator->Create(L"skelegon_hit_left", pAtlas, Vector2(0.0f, 600.0f), Vector2(600.0f, 200.0f), 1, Vector2(600.f, 200.f));

		pAnimator->Create(L"skelegon_stand_right", pAtlas, Vector2(6000.0f, 0.0f), Vector2(-600.0f, 200.0f), 6, Vector2(600.f, 200.f));
		pAnimator->Create(L"skelegon_move_right", pAtlas, Vector2(6000.0f, 200.0f), Vector2(-600.0f, 200.0f), 4, Vector2(600.f, 200.f));
		pAnimator->Create(L"skelegon_attack0_right", pAtlas, Vector2(6000.0f, 400.0f), Vector2(-600.0f, 200.0f), 11, Vector2(600.f, 200.f), Vector2::Zero, 0.2f);
		pAnimator->Create(L"skelegon_dead_right", pAtlas, Vector2(6000.0f, 600.0f), Vector2(-600.0f, 200.0f), 8, Vector2(600.f, 200.f), Vector2::Zero, 0.15f);
		pAnimator->Create(L"skelegon_hit_right", pAtlas, Vector2(6000.0f, 600.0f), Vector2(-600.0f, 200.0f), 1, Vector2(600.f, 200.f));

		m_spAttackEffect = Resources::Load<Texture>(L"sklaserEffect", L"..\\Resources\\Texture\\Monster\\attack1_hit.png");
		Effect* pEffect = new Effect();
		pEffect->SetName(L"sklaserEffect");
		pEffect->CreateAnimation(m_spAttackEffect, Vector2(0.f, 0.f), Vector2(134.f, 97.f), 1, 1, Vector2(100.f, 100.f), Vector2::Zero, 0.2f);

	}

	Skelegon::~Skelegon()
	{

	}
	void Skelegon::Initialize()
	{
		MonsterScript* pSkelegonScript = AddComponent<MonsterScript>();
		pSkelegonScript->Initialize();
		pSkelegonScript->CreateHP();

		tObjectInfo tObjInfo = {};
		//tObjInfo.fAttack = 5.f;
		tObjInfo.fDefense = 5.f;
		tObjInfo.fSpeed = 1.f;
		pSkelegonScript->SetObjectInfo(tObjInfo);


		tMonsterAttack attack = {};
		attack.pFunction = std::bind(&Skelegon::create_laser, this);

		attack.vScale = Vector2(1.8f, 0.5f);
		attack.vOffset = Vector2(1.7f, 0.f);
		attack.tAttackInfo.fAttackDamage = 10.f;

		attack.iStartFrame = 4;
		attack.iEndFrame = 6;
		pSkelegonScript->AddAttack(attack);

		add_skill();

		Collider2D* pCollider = AddComponent<Collider2D>();
		AddComponent<Rigidbody>();
		GetComponent<Transform>()->SetScale(6.f, 2.f, 0.f);
		pCollider->SetSize(Vector2(0.4f / 3.f, 0.4f));


		MonsterFSM* pFSM = new MonsterFSM();
		//m_pFSM->SetPlayer(m_pPlayer);5
		pFSM->SetMonster(this);
		pFSM->AddState(new MonsterStand());
		pFSM->AddState(new MonsterMove());
		pFSM->AddState(new MonsterHit());
		pFSM->AddState(new MonsterAttack());
		pFSM->AddState(new MonsterDead());

		pFSM->SetActiveState(Monster::eMonsterState::stand);
		pSkelegonScript->SetFSM(pFSM);
		pFSM->Initialize();

		//생성될 아이템
		
		std::vector<std::wstring> vecItems = { L"alixir",L"10_weapon"};
		SetCreateCount(2);
		SetItem(vecItems);
	}

	void Skelegon::Update()
	{
		Monster::Update();
	}

	void Skelegon::LateUpdate()
	{
		std::wstring strName = GetName();
		std::wstring strState = GetCurStateName();
		std::wstring strDir;

		int iDir = GetDir();
		if (iDir > 0)
			strDir = L"_right";
		else
			strDir = L"_left";

		if (strState == L"_attack")
		{
			UINT iNumber = GetScript<MonsterScript>()->GetAttackNumber();
			strState += std::to_wstring(iNumber);
		}
		std::wstring strAnimName = GetMonsterAnim();
		std::wstring strCurAnim = strName + strState + strDir;

		if (strAnimName != strCurAnim)
		{
			SetMonsterAnim(strCurAnim);
			GetComponent<Animator>()->Play(strCurAnim, true);
		}

		Monster::LateUpdate();
	}

	void Skelegon::Render()
	{
		Monster::Render();
	}

	void Skelegon::add_skill()
	{
		MonsterAttackObject* pLaser = new MonsterAttackObject();
		pLaser->SetName(L"sklaserEffect");
		AddMonsterSkill(pLaser);
	}

	void Skelegon::create_laser()
	{
		MonsterAttackObject* pLaser = GetMonsterSkill(L"sklaserEffect");
		if (pLaser == nullptr)
			return;

		MonsterScript* pMonsterScript = GetScript<MonsterScript>();
		pMonsterScript->SetMonsterAttack(pLaser);
		pLaser->SetOnwer(this);

		SceneManger::AddGameObject(eLayerType::MonsterAttack, pLaser);
	}
}