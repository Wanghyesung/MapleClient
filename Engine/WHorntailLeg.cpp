#include "WHorntailLeg.h"
#include "WResources.h"
#include "WAnimator.h"
#include "WMonsterScript.h"
#include "WMonsterFSM.h"
#include "WBossStand.h"
#include "WMonsterAttack.h"
#include "WRenderer.h"
#include "WEffect.h"
#include "WSceneManger.h"
#include "WHorntailDead.h"
#include "WEventManager.h"
namespace W
{
	HorntailLeg::HorntailLeg(Horntail* _pOwner):
		m_pOwner(_pOwner)
	{
		SetName(L"Leg");

		MeshRenderer* pRenderer = AddComponent<MeshRenderer>();
		pRenderer->SetMesh(Resources::Find<Mesh>(L"RectMesh"));


		std::shared_ptr<Material> pMater = std::make_shared<Material>();
		pMater->SetRenderinMode(eRenderingMode::Transparent);
		pMater->SetShader(Resources::Find<Shader>(L"MonsterShader"));
		Resources::Insert(L"horntailLegMater", pMater);

		pRenderer->SetMaterial(pMater);

		std::shared_ptr<Texture> pAtlas =
			Resources::Find<Texture>(L"LegTex");
		pAtlas->BindShaderResource(eShaderStage::PS, 12);

		Animator* pAnim = AddComponent<Animator>();
		pAnim->Create(L"Leg_stand", pAtlas, Vector2(0.f, 0.f), Vector2(600.f, 300.f), 1, Vector2(1000.f, 1000.f), Vector2::Zero, 0.15f);
		pAnim->Create(L"Leg_attack0", pAtlas, Vector2(0.f, 300.f), Vector2(600.f, 300.f), 14, Vector2(1000.f, 1000.f), Vector2::Zero, 0.15f);
		pAnim->Create(L"Leg_attack1", pAtlas, Vector2(0.f, 600.f), Vector2(600.f, 300.f), 18, Vector2(1000.f, 1000.f), Vector2::Zero, 0.15f);
		pAnim->Create(L"Leg_dead", pAtlas, Vector2(0.f, 900.f), Vector2(600.f, 300.f), 14, Vector2(1000.f, 1000.f), Vector2::Zero, 0.15f);

	}
	HorntailLeg::~HorntailLeg()
	{
		ObjectPoolManager::ReleaseObject(L"legattack1");
		ObjectPoolManager::ReleaseObject(L"legattack2");

	}

	void HorntailLeg::add_skill()
	{
		//1
		MonsterAttackObject* attack1 = new MonsterAttackObject();
		attack1->SetName(L"legattack1");
		AddMonsterSkill(attack1);

		//2
		MonsterAttackObject* attack2 = new MonsterAttackObject();
		attack2->SetName(L"legattack2");
		AddMonsterSkill(attack2);
	}

	void HorntailLeg::Initialize()
	{
		GetComponent<Transform>()->SetScale(11.f, 11.f, 0.f);
		GetComponent<Transform>()->SetPosition(-1.53f, -2.1f, -1.4f);
		Collider2D* pCollider = AddComponent<Collider2D>();
		pCollider->SetSize(Vector2(0.4f, 0.2f));
		pCollider->SetCenter(Vector2(0.f, -1.f));

		//보스 등록
		MonsterScript* Pscript = AddComponent<MonsterScript>();
		Pscript->SetBoss();
		Pscript->Initialize();

		setAttack();
		add_skill();

		MonsterFSM* pFSM = new MonsterFSM();
		pFSM->SetMonster(this);
		Pscript->SetFSM(pFSM);

		BossStand* pHorntailStand = new BossStand();
		pFSM->AddState(pHorntailStand);
		MonsterAttack* pMonsterAttack = new MonsterAttack();
		pFSM->AddState(pMonsterAttack);
		HorntailDead* pDead = new HorntailDead();
		pFSM->AddState(pDead);

		pFSM->SetActiveState(Monster::eMonsterState::stand);
		pFSM->Initialize();
	}
	void HorntailLeg::Update()
	{
		Monster::Update();

	}
	void HorntailLeg::LateUpdate()
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
	void HorntailLeg::Render()
	{
		renderer::MonsterCB MonsterCB;
		MonsterCB.vMonsterDir.x = 1;

		ConstantBuffer* pConstBuffer = renderer::constantBuffer[(UINT)eCBType::Monster];
		//Vector4 vPosition(m_vPosition.x, m_vPosition.y, m_vPosition.z, 1.f);
		pConstBuffer->SetData(&MonsterCB);
		pConstBuffer->Bind(eShaderStage::PS);

		GameObject::Render();
	}
	void HorntailLeg::setAttack()
	{
		MonsterScript* Pscript = GetComponent<MonsterScript>();
		Vector3 vPosition = GetComponent<Transform>()->GetPosition();

		//1
		tMonsterAttack attack0 = {};
		attack0.tTime.fCoolTime = 5.f;

		attack0.pFunction = std::bind(&HorntailLeg::attack1, this);

		attack0.vPosition = vPosition;
		attack0.vScale = Vector2(3.3f, 2.f);
		attack0.vOffset = Vector2(3.4f, -1.f);

		attack0.iStartFrame = 7;
		attack0.iEndFrame = 10;
		attack0.tAttackInfo.fAttackDamage = 10.f;
		Pscript->AddAttack(attack0);

		//2
		tMonsterAttack attack1 = {};
		attack1.tTime.fCoolTime = 5.f;

		attack1.pFunction = std::bind(&HorntailLeg::attack2, this);

		attack1.vPosition = vPosition;
		attack1.vScale = Vector2(3.3f, 2.f);
		attack1.vOffset = Vector2(-3.f, -1.f);

		attack1.iStartFrame = 12;
		attack1.iEndFrame = 14;
		attack1.tAttackInfo.fAttackDamage = 15.f;
		Pscript->AddAttack(attack1);

	}
	void HorntailLeg::attack1()
	{
		MonsterAttackObject* attack1 = GetMonsterSkill(L"legattack1");
		if (attack1 == nullptr)
			return;
		
		MonsterScript* pMonsterScript = GetScript<MonsterScript>();
		pMonsterScript->SetMonsterAttack(attack1);
		attack1->SetOnwer(this);
		
		
		EventManager::CreateObject(attack1, eLayerType::MonsterAttack);
	}

	void HorntailLeg::attack2()
	{
		MonsterAttackObject* attack2 = GetMonsterSkill(L"legattack2");
		if (attack2 == nullptr)
			return;

		MonsterScript* pMonsterScript = GetScript<MonsterScript>();
		pMonsterScript->SetMonsterAttack(attack2);
		attack2->SetOnwer(this);

		EventManager::CreateObject(attack2, eLayerType::MonsterAttack);
	}
}