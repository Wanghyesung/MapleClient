#include "WWhiggin.h"
#include "WResources.h"
#include "WAnimator.h"
#include "WEffect.h"
#include "WMonsterScript.h"
#include "WBossStand.h"
#include "WMonsterAttack.h"
#include "WMonsterDead.h"
#include "WRenderer.h"
#include "WEventManager.h"
#include "WSceneManger.h"
#include "WBossStart.h"
#include "WMuninStone.h"
namespace W
{
	Whiggin::Whiggin()
	{
		SetName(L"Whiggin");

		MeshRenderer* pRenderer = AddComponent<MeshRenderer>();
		pRenderer->SetMesh(Resources::Find<Mesh>(L"RectMesh"));


		std::shared_ptr<Material> pMater = std::make_shared<Material>();
		pMater->SetRenderinMode(eRenderingMode::Transparent);
		pMater->SetShader(Resources::Find<Shader>(L"MonsterShader"));
		Resources::Insert(L"WhigginMater", pMater);

		pRenderer->SetMaterial(pMater);

		std::shared_ptr<Texture> pAtlas = Resources::Find<Texture>(L"WhigginTex");
		Animator* pAnim = AddComponent<Animator>();
		pAnim->Create(L"Whiggin_stand", pAtlas, Vector2(0.f, 0.f), Vector2(350.f, 500.f), 1, Vector2(1000.f, 1000.f), Vector2::Zero, 0.15f);
		pAnim->Create(L"Whiggin_start", pAtlas, Vector2(0.f, 500.f), Vector2(350.f, 500.f), 11, Vector2(1000.f, 1000.f), Vector2::Zero, 0.15f);
		pAnim->Create(L"Whiggin_attack0", pAtlas, Vector2(0.f, 1000.f), Vector2(350.f, 500.f), 16, Vector2(1000.f, 1000.f), Vector2::Zero, 0.15f);
		pAnim->Create(L"Whiggin_attack1", pAtlas, Vector2(0.f, 1500.f), Vector2(350.f, 500.f), 23, Vector2(1000.f, 1000.f), Vector2::Zero, 0.15f);
		pAnim->Create(L"Whiggin_attack2", pAtlas, Vector2(0.f, 2000.f), Vector2(350.f, 500.f), 15, Vector2(1000.f, 1000.f), Vector2::Zero, 0.15f);
		pAnim->Create(L"Whiggin_attack3", pAtlas, Vector2(0.f, 2500.f), Vector2(350.f, 500.f), 18, Vector2(1000.f, 1000.f), Vector2::Zero, 0.15f);
		pAnim->Create(L"Whiggin_dead", pAtlas, Vector2(0.f, 3000.f), Vector2(350.f, 500.f), 16, Vector2(1000.f, 1000.f), Vector2::Zero, 0.15f);

	}

	void Whiggin::add_skill()
	{
		//1
		MonsterAttackObject* attack1 = new MonsterAttackObject();
		attack1->SetName(L"Whiggin_attack0");
		AddMonsterSkill(attack1);
		//2
		MuninStone* pStone = new MuninStone();
		pStone->SetName(L"Whiggin_attack1");
		pStone->SetOnwer(this);
		AddMonsterSkill(pStone);
	}

	Whiggin::~Whiggin()
	{
		ObjectPoolManager::ReleaseObject(L"Whiggin_attack0");
		ObjectPoolManager::ReleaseObject(L"Whiggin_attack1");

	}
	void Whiggin::Initialize()
	{
		GetComponent<Transform>()->SetScale(10.f, 10.f, 0.f);
		GetComponent<Transform>()->SetPosition(-2.7f, -0.72f, -1.3f);
		Collider2D* pCollider = AddComponent<Collider2D>();
		pCollider->SetSize(Vector2(0.1f, 0.2f));
		pCollider->SetCenter(Vector2(0.f, 0.f));
		pCollider->SetActive(false);

		MonsterScript* Pscript = AddComponent<MonsterScript>();
		Pscript->SetBoss();
		Pscript->Initialize();

		setattack();
		add_skill();

		MonsterFSM* pFSM = new MonsterFSM();
		pFSM->SetMonster(this);
		Pscript->SetFSM(pFSM);


		pFSM->AddState(new BossStand());
		pFSM->AddState(new BossStart());
		pFSM->AddState(new MonsterAttack());
		pFSM->AddState(new MonsterDead());

		pFSM->SetActiveState(Monster::eMonsterState::start);
		pFSM->Initialize();
	}
	void Whiggin::Update()
	{
		GameObject::Update();
	}
	void Whiggin::LateUpdate()
	{
		std::wstring strName = GetName();
		std::wstring strState = GetCurStateName();

		if (strState == L"_attack")
		{
			UINT iNumber = GetScript<MonsterScript>()->GetAttackNumber();
			strState += std::to_wstring(iNumber);
		}

		std::wstring strAnimName = GetMonsterAnim();
		std::wstring strCurAnim = strName + strState;

		if (strAnimName != strCurAnim)
		{
			SetMonsterAnim(strCurAnim);
			GetComponent<Animator>()->Play(strCurAnim, true);
		}

		Monster::LateUpdate();
	}
	void Whiggin::Render()
	{
		renderer::MonsterCB MonsterCB;
		MonsterCB.vMonsterDir.x = 1;

		ConstantBuffer* pConstBuffer = renderer::constantBuffer[(UINT)eCBType::Monster];
		//Vector4 vPosition(m_vPosition.x, m_vPosition.y, m_vPosition.z, 1.f);
		pConstBuffer->SetData(&MonsterCB);
		pConstBuffer->Bind(eShaderStage::PS);

		GameObject::Render();
	}

	void Whiggin::setattack()
	{
		MonsterScript* Pscript = GetComponent<MonsterScript>();
		Vector3 vPosition = GetComponent<Transform>()->GetPosition();

		tMonsterAttack attack1 = {};
		attack1.tTime.fCoolTime = 10.f;
		attack1.pFunction = std::bind(&Whiggin::attack1, this);

		attack1.tAttackInfo.fAttRcnt = 2.f;

		attack1.vPosition = vPosition;
		attack1.vScale = Vector2(6.f, 2.f);
		attack1.vOffset = Vector2(0.f, -0.5f);

		attack1.iStartFrame = 11;
		attack1.iEndFrame = 13;
		attack1.tAttackInfo.fAttackDamage = 10.f;
		Pscript->AddAttack(attack1);

		//2
		tMonsterAttack attack2 = {};
		attack2.tTime.fCoolTime = 11.f;
		attack2.bSkill = true;
		attack2.vScale = Vector2(0.f, 0.f);
		attack2.pFunction = std::bind(&Whiggin::attack2, this);

		attack2.iStartFrame = 13;
		attack2.iEndFrame = 14;

		Pscript->AddAttack(attack2);

		//3
		tMonsterAttack skill = {};
		skill.bSkill = true;
		skill.tTime.fCoolTime = 18.f;

		skill.vScale = Vector2(0.f, 0.f);
		skill.pFunction = std::bind(&Whiggin::attack_reflect, this);

		skill.iStartFrame = 8;
		skill.iEndFrame = 9;
		Pscript->AddAttack(skill);


		tMonsterAttack skill2 = {};
		skill2.bSkill = true;
		skill2.tTime.fCoolTime = 20.f;

		skill2.vScale = Vector2(0.f, 0.f);
		skill2.pFunction = std::bind(&Whiggin::dark, this);

		skill2.iStartFrame = 6;
		skill2.iEndFrame = 7;
		Pscript->AddAttack(skill2);

	}
	void Whiggin::attack1()
	{
		MonsterAttackObject* attack1 = GetMonsterSkill(L"Whiggin_attack0");
		if (attack1 == nullptr)
			return;

		MonsterScript* pMonsterScript = GetScript<MonsterScript>();
		pMonsterScript->SetMonsterAttack(attack1);
		attack1->SetOnwer(this);

		EventManager::CreateObject(attack1, eLayerType::MonsterAttack);
	}
	void Whiggin::attack2()
	{
		GameObject* pPlayer = SceneManger::FindPlayer();
		Vector3 vPosisiton = pPlayer->GetComponent<Transform>()->GetPosition();
		vPosisiton.z -= 0.1f;
		vPosisiton.y += 2.5f;

		MonsterAttackObject* pStone = GetMonsterSkill(L"Whiggin_attack1");
		if (pStone == nullptr)
			return;

		pStone->GetComponent<Transform>()->SetPosition(vPosisiton);
		pStone->Initialize();
		EventManager::CreateObject(pStone, eLayerType::MonsterAttack);
	}

	void Whiggin::dark()
	{

	}
	void Whiggin::attack_reflect()
	{
		BattleManager::Buff_Stat(this, BattleManager::eUpStatType::ReflexAttack, 1.f);
	}
}