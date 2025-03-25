#include "WHorntailHeadA.h"
#include "WResources.h"
#include "WAnimator.h"
#include "WMonsterScript.h"
#include "WRenderer.h"
#include "WBossStand.h"
#include "WMonsterAttack.h"
#include "WMonsterFSM.h"
#include "WIce.h"
#include "WSceneManger.h"
#include "WEffect.h"
#include "WBattleManager.h"
#include "WHorntailDead.h"
#include "WEventManager.h"

namespace W
{
	HorntailHeadA::HorntailHeadA(Horntail* _pOwner):
		m_pOwner(_pOwner)
	{
		SetName(L"HeadA");

		MeshRenderer* pRenderer = AddComponent<MeshRenderer>();
		pRenderer->SetMesh(Resources::Find<Mesh>(L"RectMesh"));


		std::shared_ptr<Material> pMater = std::make_shared<Material>();
		pMater->SetRenderinMode(eRenderingMode::Transparent);
		pMater->SetShader(Resources::Find<Shader>(L"MonsterShader"));
		Resources::Insert(L"horntailMater", pMater);

		pRenderer->SetMaterial(pMater);

		std::shared_ptr<Texture> pAtlas = Resources::Find<Texture>(L"HeadATex");
		Animator* pAnim = AddComponent<Animator>();
		pAnim->Create(L"HeadA_stand", pAtlas, Vector2(0.f, 0.f), Vector2(550.f, 650.f), 10, Vector2(1000.f, 1000.f), Vector2::Zero, 0.15f);
		pAnim->Create(L"HeadA_attack0", pAtlas, Vector2(0.f, 650.f), Vector2(550.f, 650.f), 21, Vector2(1000.f, 1000.f), Vector2::Zero, 0.15f);
		pAnim->Create(L"HeadA_attack1", pAtlas, Vector2(0.f, 1300.f), Vector2(550.f, 650.f), 17, Vector2(1000.f, 1000.f), Vector2::Zero, 0.15f);
		pAnim->Create(L"HeadA_attack2", pAtlas, Vector2(0.f, 1950.f), Vector2(550.f, 650.f), 16, Vector2(1000.f, 1000.f), Vector2::Zero, 0.15f);
		pAnim->Create(L"HeadA_dead", pAtlas, Vector2(0.f, 2600.f), Vector2(550.f, 650.f), 15, Vector2(1000.f, 1000.f), Vector2::Zero, 0.15f);

		pAnim->Play(L"HeadA_stand", true);
	}

	HorntailHeadA::~HorntailHeadA()
	{
		ObjectPoolManager::ReleaseObject(L"icebreath");
		ObjectPoolManager::ReleaseObject(L"ice");
	}

	void HorntailHeadA::add_skill()
	{
		//1
		MonsterAttackObject* breath = new MonsterAttackObject();
		breath->SetName(L"icebreath");
		AddMonsterSkill(breath);
		//2
		for (int i = 0; i < 5; ++i)
		{
			Ice* pIce = new Ice();
			pIce->SetName(L"ice");
			AddMonsterSkill(pIce);
		}
		//3
	}

	void HorntailHeadA::Initialize()
	{
		GetComponent<Transform>()->SetScale(11.f, 11.f, 0.f);
		GetComponent<Transform>()->SetPosition(-4.145f, -1.14f ,-1.3f);
		Collider2D* pCollider = AddComponent<Collider2D>();
		pCollider->SetSize(Vector2(0.2f, 0.2f));
		pCollider->SetCenter(Vector2(1.4f, 2.f));
		

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

	void HorntailHeadA::Update()
	{
		Monster::Update();
		
	}

	void HorntailHeadA::LateUpdate()
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

	void HorntailHeadA::Render()
	{
		renderer::MonsterCB MonsterCB;
		MonsterCB.vMonsterDir.x = 1;

		ConstantBuffer* pConstBuffer = renderer::constantBuffer[(UINT)eCBType::Monster];
		//Vector4 vPosition(m_vPosition.x, m_vPosition.y, m_vPosition.z, 1.f);
		pConstBuffer->SetData(&MonsterCB);
		pConstBuffer->Bind(eShaderStage::PS);

		GameObject::Render();
	}
	void HorntailHeadA::setAttack()
	{
		MonsterScript* Pscript = GetComponent<MonsterScript>();
		Vector3 vPosition = GetComponent<Transform>()->GetPosition();
		//1
		
		tMonsterAttack breath = {};
		breath.tTime.fCoolTime = 6.f;
		breath.pFunction = std::bind(&HorntailHeadA::create_breath, this);

		breath.vPosition = vPosition;
		breath.vScale = Vector2(4.f, 2.f);
		breath.vOffset = Vector2(-1.7f, -0.7f);
		breath.vRoatate = Vector3(0.f, 0.f, XM_PI / 6.f);

		breath.iStartFrame = 11;
		breath.iEndFrame = 13;
		breath.tAttackInfo.fAttackDamage = 10.f;
		Pscript->AddAttack(breath);


		//2
		tMonsterAttack summons = {};
		summons.bSkill = true;
		summons.tTime.fCoolTime = 10.f;

		summons.vScale = Vector2(0.f, 0.f);
		summons.pFunction = std::bind(&HorntailHeadA::create_ice, this);
		
		summons.iStartFrame = 11;
		summons.iEndFrame = 13;
		
		Pscript->AddAttack(summons);

		//3
		tMonsterAttack skill = {};
		skill.bSkill = true;
		skill.tTime.fCoolTime = 15.f;

		skill.vScale = Vector2(0.f, 0.f);
		skill.pFunction = std::bind(&HorntailHeadA::physics_ignore, this);

		skill.iStartFrame = 8;
		skill.iEndFrame = 9;

		Pscript->AddAttack(skill);
	}

	void HorntailHeadA::create_breath()
	{
		MonsterAttackObject* breath = GetMonsterSkill(L"icebreath");
		if (breath == nullptr)
			return;

		MonsterScript* pMonsterScript = GetScript<MonsterScript>();
		pMonsterScript->SetMonsterAttack(breath);
		breath->SetOnwer(this);

		EventManager::CreateObject(breath, eLayerType::MonsterAttack);
	}

	void HorntailHeadA::create_ice()
	{	
		//맵 시작부터 끝
		Vector3 vStartPos = Vector3(-6.5f, -2.64f, -1.9f);

		for (UINT i = 0; i < 5; ++i)
		{
			float fOffsetX = i * 2 + vStartPos.x;
			
			MonsterAttackObject* pIce = GetMonsterSkill(L"ice");
			if (pIce == nullptr)
				return;
			pIce->SetOnwer(this);

			pIce->GetComponent<Transform>()->SetPosition(fOffsetX, vStartPos.y, vStartPos.z);
			pIce->Initialize();
			EventManager::CreateObject(pIce, eLayerType::MonsterAttack);
		}
	}
	void HorntailHeadA::physics_ignore()
	{
		BattleManager::Buff_Stat(this, BattleManager::eUpStatType::Ignore, 1);
	}
}