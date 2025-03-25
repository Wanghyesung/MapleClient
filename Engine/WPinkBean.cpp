#include "WPinkBean.h"
#include "WResources.h"
#include "WAnimator.h"
#include "WEffect.h"
#include "WMonsterScript.h"
#include "WMonsterAttack.h"
#include "WMonsterDead.h"
#include "WRenderer.h"
#include "WEventManager.h"
#include "WSceneManger.h"
#include "WMonsterStand.h"
#include "WMonsterMove.h"
#include "WRigidbody.h"
#include "WJenesis.h"
#include "WPinkBeanStone.h"
#include "WRoccatBean.h"
#include "WBossStart.h"
#include "WPinkbeanStand.h"
#include "WMiniBean.h"
#include "WSolomon.h"
#include "WRex.h"
#include "WMunin.h"
#include "WAriel.h"
#include "WWhiggin.h"
#include "WSharHP.h"
namespace W
{
	PinkBean::PinkBean():
		m_bStart(false),
		m_queueMiniBean{},
		m_vecMonster{},
		m_pSharHP(nullptr)
	{
		SetName(L"PinkBean"); 

		MeshRenderer* pRenderer = AddComponent<MeshRenderer>();
		pRenderer->SetMesh(Resources::Find<Mesh>(L"RectMesh"));


		std::shared_ptr<Material> pMater = std::make_shared<Material>();
		pMater->SetRenderinMode(eRenderingMode::Transparent);
		pMater->SetShader(Resources::Find<Shader>(L"MonsterShader"));
		Resources::Insert(L"PinkBeanlMater", pMater);

		pRenderer->SetMaterial(pMater);

		std::shared_ptr<Texture> pAtlas1 = Resources::Find<Texture>(L"PinkBean1");
		std::shared_ptr<Texture> pAtlas2 = Resources::Find<Texture>(L"PinkBean2");

		AddComponent<Rigidbody>();

		Animator* pAnim = AddComponent<Animator>();
		
		pAnim->Create(L"PinkBean_start_left", pAtlas2, Vector2(0.f, 7200.f), Vector2(750.f, 600.f), 4, Vector2(1000.f, 1000.f), Vector2::Zero, 0.15f);
		pAnim->Create(L"PinkBean_start_right", pAtlas2, Vector2(9750.f, 7200.f), Vector2(-750.f, 600.f), 4, Vector2(1000.f, 1000.f), Vector2::Zero, 0.15f);
		//pAnim->StartEvent(L"PinkBean_start_left") = std::bind(&PinkBean::start, this);
		//pAnim->StartEvent(L"PinkBean_start_right") = std::bind(&PinkBean::start, this);

		pAnim->Create(L"PinkBean_stand_left", pAtlas1, Vector2(0.f, 0.f), Vector2(750.f, 600.f), 6, Vector2(1000.f, 1000.f), Vector2::Zero, 0.15f);
		pAnim->Create(L"PinkBean_move_left", pAtlas1, Vector2(0.f, 600.f), Vector2(750.f, 600.f), 8, Vector2(1000.f, 1000.f), Vector2::Zero, 0.15f);
		pAnim->Create(L"PinkBean_attack0_left", pAtlas1,  Vector2(0.f, 1200.f), Vector2(750.f, 600.f), 14, Vector2(1000.f, 1000.f), Vector2::Zero, 0.15f);
		pAnim->Create(L"PinkBean_attack1_left", pAtlas1,  Vector2(0.f, 1800.f), Vector2(750.f, 600.f), 14, Vector2(1000.f, 1000.f), Vector2::Zero, 0.15f);
		pAnim->FindAnimation(L"PinkBean_attack1_left")->Create(L"PinkBean_attack1_left", pAtlas1, Vector2(0.f, 2400.f), Vector2(750.f, 600.f), 10, Vector2(1000.f, 1000.f), Vector2::Zero, 0.15f);
		pAnim->Create(L"PinkBean_attack2_left", pAtlas1,  Vector2(0.f, 3000.f), Vector2(750.f, 600.f), 14, Vector2(1000.f, 1000.f), Vector2::Zero, 0.15f);
		pAnim->FindAnimation(L"PinkBean_attack2_left")->Create(L"PinkBean_attack2_left", pAtlas1, Vector2(0.f, 3600.f), Vector2(750.f, 600.f), 7, Vector2(1000.f, 1000.f), Vector2::Zero, 0.15f);
		pAnim->Create(L"PinkBean_attack3_left", pAtlas1,  Vector2(0.f, 4200.f), Vector2(750.f, 600.f), 14, Vector2(1000.f, 1000.f), Vector2::Zero, 0.15f);
		pAnim->FindAnimation(L"PinkBean_attack3_left")->Create(L"PinkBean_attack3_left", pAtlas1, Vector2(0.f, 4800.f), Vector2(750.f, 600.f), 7, Vector2(1000.f, 1000.f), Vector2::Zero, 0.15f);
		pAnim->Create(L"PinkBean_dead_left", pAtlas1, Vector2(0.f, 5400.f), Vector2(750.f, 600.f), 14, Vector2(1000.f, 1000.f), Vector2::Zero, 0.15f);
		pAnim->FindAnimation(L"PinkBean_dead_left")->Create(L"PinkBean_dead_left", pAtlas1, Vector2(0.f, 6000.f), Vector2(750.f, 600.f),14, Vector2(1000.f, 1000.f), Vector2::Zero, 0.15f);
		pAnim->FindAnimation(L"PinkBean_dead_left")->Create(L"PinkBean_dead_left", pAtlas1, Vector2(0.f, 6600.f), Vector2(750.f, 600.f), 14, Vector2(1000.f, 1000.f), Vector2::Zero, 0.15f);

		pAnim->Create(L"PinkBean_stand_right", pAtlas1, Vector2(9750.f, 0.f), Vector2(-750.f, 600.f), 6, Vector2(1000.f, 1000.f), Vector2::Zero, 0.15f);
		pAnim->Create(L"PinkBean_move_right", pAtlas1, Vector2(9750.f, 600.f), Vector2(-750.f, 600.f), 8, Vector2(1000.f, 1000.f), Vector2::Zero, 0.15f);
		pAnim->Create(L"PinkBean_attack0_right", pAtlas1, Vector2(9750.f, 1200.f), Vector2(-750.f, 600.f), 14, Vector2(1000.f, 1000.f), Vector2::Zero, 0.15f);
		pAnim->Create(L"PinkBean_attack1_right", pAtlas1, Vector2(9750.f, 1800.f), Vector2(-750.f, 600.f), 14, Vector2(1000.f, 1000.f), Vector2::Zero, 0.15f);
		pAnim->FindAnimation(L"PinkBean_attack1_right")->Create(L"PinkBean_attack1_right", pAtlas1, Vector2(9750.f, 2400.f), Vector2(-750.f, 600.f), 10, Vector2(1000.f, 1000.f), Vector2::Zero, 0.15f);
		pAnim->Create(L"PinkBean_attack2_right", pAtlas1, Vector2(9750.f, 3000.f), Vector2(-750.f, 600.f), 14, Vector2(1000.f, 1000.f), Vector2::Zero, 0.15f);
		pAnim->FindAnimation(L"PinkBean_attack2_right")->Create(L"PinkBean_attack2_right", pAtlas1, Vector2(9750.f, 3600.f), Vector2(-750.f, 600.f), 7, Vector2(1000.f, 1000.f), Vector2::Zero, 0.15f);
		pAnim->Create(L"PinkBean_attack3_right", pAtlas1, Vector2(9750.f, 4200.f), Vector2(-750.f, 600.f), 14, Vector2(1000.f, 1000.f), Vector2::Zero, 0.15f);
		pAnim->FindAnimation(L"PinkBean_attack3_right")->Create(L"PinkBean_attack3_right", pAtlas1, Vector2(9750.f, 4800.f), Vector2(-750.f, 600.f), 7, Vector2(1000.f, 1000.f), Vector2::Zero, 0.15f);
		pAnim->Create(L"PinkBean_dead_right", pAtlas1, Vector2(9750.f, 5400.f), Vector2(-750.f, 600.f), 14, Vector2(1000.f, 1000.f), Vector2::Zero, 0.15f);
		pAnim->FindAnimation(L"PinkBean_dead_right")->Create(L"PinkBean_dead_right", pAtlas1, Vector2(9750.f, 6000.f), Vector2(-750.f, 600.f), 14, Vector2(1000.f, 1000.f), Vector2::Zero, 0.15f);
		pAnim->FindAnimation(L"PinkBean_dead_right")->Create(L"PinkBean_dead_right", pAtlas1, Vector2(9750.f, 6600.f), Vector2(-750.f, 600.f), 14, Vector2(1000.f, 1000.f), Vector2::Zero, 0.15f);
		
		//atlas2
		pAnim->Create(L"PinkBean_attack4_left", pAtlas2, Vector2(0.f, 0.f), Vector2(750.f, 600.f), 14, Vector2(1000.f, 1000.f), Vector2::Zero, 0.15f);
		pAnim->FindAnimation(L"PinkBean_attack4_left")->Create(L"PinkBean_attack4_left", pAtlas2, Vector2(0.f, 600.f), Vector2(750.f, 600.f), 3, Vector2(1000.f, 1000.f), Vector2::Zero, 0.15f);
		pAnim->Create(L"PinkBean_attack5_left", pAtlas2, Vector2(0.f, 1200.f), Vector2(750.f, 600.f), 14, Vector2(1000.f, 1000.f), Vector2::Zero, 0.15f);
		pAnim->FindAnimation(L"PinkBean_attack5_left")->Create(L"PinkBean_attack5_left", pAtlas2, Vector2(0.f, 1800.f), Vector2(750.f, 600.f), 7, Vector2(1000.f, 1000.f), Vector2::Zero, 0.15f);
		pAnim->Create(L"PinkBean_attack6_left", pAtlas2, Vector2(0.f, 2400.f), Vector2(750.f, 600.f), 14, Vector2(1000.f, 1000.f), Vector2::Zero, 0.15f);
		pAnim->FindAnimation(L"PinkBean_attack6_left")->Create(L"PinkBean_attack6_left", pAtlas2, Vector2(0.f, 3000.f), Vector2(750.f, 600.f), 11, Vector2(1000.f, 1000.f), Vector2::Zero, 0.15f);
		pAnim->Create(L"PinkBean_attack7_left", pAtlas2, Vector2(0.f, 3600.f), Vector2(750.f, 600.f), 14, Vector2(1000.f, 1000.f), Vector2::Zero, 0.15f);
		pAnim->FindAnimation(L"PinkBean_attack7_left")->Create(L"PinkBean_attack7_left", pAtlas2, Vector2(0.f, 4200.f), Vector2(750.f, 600.f), 14, Vector2(1000.f, 1000.f), Vector2::Zero, 0.15f);
		pAnim->Create(L"PinkBean_attack8_left", pAtlas2, Vector2(0.f, 4800.f), Vector2(750.f, 600.f), 14, Vector2(1000.f, 1000.f), Vector2::Zero, 0.15f);
		pAnim->FindAnimation(L"PinkBean_attack8_left")->Create(L"PinkBean_attack8_left", pAtlas2, Vector2(0.f, 5400.f), Vector2(750.f, 600.f), 14, Vector2(1000.f, 1000.f), Vector2::Zero, 0.15f);
		pAnim->Create(L"PinkBean_attack9_left", pAtlas2, Vector2(0.f, 6000.f), Vector2(750.f, 600.f), 14, Vector2(1000.f, 1000.f), Vector2::Zero, 0.15f);
		pAnim->FindAnimation(L"PinkBean_attack9_left")->Create(L"PinkBean_attack9_left", pAtlas2, Vector2(0.f, 6600.f), Vector2(750.f, 600.f), 14, Vector2(1000.f, 1000.f), Vector2::Zero, 0.15f);
		pAnim->Create(L"PinkBean_attack10_left", pAtlas2, Vector2(0.f, 7200.f), Vector2(750.f, 600.f), 14, Vector2(1000.f, 1000.f), Vector2::Zero, 0.15f);
		
		pAnim->Create(L"PinkBean_attack4_right", pAtlas2, Vector2(9750.f, 0.f), Vector2(-750.f, 600.f), 14, Vector2(1000.f, 1000.f), Vector2::Zero, 0.15f);
		pAnim->FindAnimation(L"PinkBean_attack4_right")->Create(L"PinkBean_attack4_right", pAtlas2, Vector2(9750.f, 600.f), Vector2(-750.f, 600.f), 3, Vector2(1000.f, 1000.f), Vector2::Zero, 0.15f);
		pAnim->Create(L"PinkBean_attack5_right", pAtlas2, Vector2(9750.f, 1200.f), Vector2(-750.f, 600.f), 14, Vector2(1000.f, 1000.f), Vector2::Zero, 0.15f);
		pAnim->FindAnimation(L"PinkBean_attack5_right")->Create(L"PinkBean_attack5_right", pAtlas2, Vector2(9750.f, 1800.f), Vector2(-750.f, 600.f), 7, Vector2(1000.f, 1000.f), Vector2::Zero, 0.15f);
		pAnim->Create(L"PinkBean_attack6_right", pAtlas2, Vector2(9750.f, 2400.f), Vector2(-750.f, 600.f), 14, Vector2(1000.f, 1000.f), Vector2::Zero, 0.15f);
		pAnim->FindAnimation(L"PinkBean_attack6_right")->Create(L"PinkBean_attack6_right", pAtlas2, Vector2(9750.f, 3000.f), Vector2(-750.f, 600.f), 11, Vector2(1000.f, 1000.f), Vector2::Zero, 0.15f);
		pAnim->Create(L"PinkBean_attack7_right", pAtlas2, Vector2(9750.f, 3600.f), Vector2(-750.f, 600.f), 14, Vector2(1000.f, 1000.f), Vector2::Zero, 0.15f);
		pAnim->FindAnimation(L"PinkBean_attack7_right")->Create(L"PinkBean_attack7_right", pAtlas2, Vector2(9750.f, 4200.f), Vector2(-750.f, 600.f), 14, Vector2(1000.f, 1000.f), Vector2::Zero, 0.15f);
		pAnim->Create(L"PinkBean_attack8_right", pAtlas2, Vector2(9750.f, 4800.f), Vector2(-750.f, 600.f), 14, Vector2(1000.f, 1000.f), Vector2::Zero, 0.15f);
		pAnim->FindAnimation(L"PinkBean_attack8_right")->Create(L"PinkBean_attack8_right", pAtlas2, Vector2(9750.f, 5400.f), Vector2(-750.f, 600.f), 14, Vector2(1000.f, 1000.f), Vector2::Zero, 0.15f);
		pAnim->Create(L"PinkBean_attack9_right", pAtlas2, Vector2(9750.f, 6000.f), Vector2(-750.f, 600.f), 14, Vector2(1000.f, 1000.f), Vector2::Zero, 0.15f);
		pAnim->FindAnimation(L"PinkBean_attack9_right")->Create(L"PinkBean_attack9_right", pAtlas2, Vector2(9750.f, 6600.f), Vector2(-750.f, 600.f), 14, Vector2(1000.f, 1000.f), Vector2::Zero, 0.15f);
		pAnim->Create(L"PinkBean_attack10_right", pAtlas2, Vector2(9750.f, 7200.f), Vector2(-750.f, 600.f), 14, Vector2(1000.f, 1000.f), Vector2::Zero, 0.15f);

	}
	PinkBean::~PinkBean()
	{
		while (!m_queueMiniBean.empty())
		{
			MiniBean* pMiniBean = m_queueMiniBean.front();
			m_queueMiniBean.pop();

			delete pMiniBean;
			pMiniBean = nullptr;
		}

		ObjectPoolManager::ReleaseObject(L"PinkBean_attack0");
		ObjectPoolManager::ReleaseObject(L"PinkBean_attack1");
		ObjectPoolManager::ReleaseObject(L"PinkBean_attack2");
		ObjectPoolManager::ReleaseObject(L"PinkBean_attack3");
	}
	void PinkBean::Initialize()
	{
		GetComponent<Transform>()->SetScale(10.f, 10.f, 0.f);
		GetComponent<Transform>()->SetPosition(0.1f, -0.4f, -1.5f);
		Collider2D* pCollider = AddComponent<Collider2D>();
		pCollider->SetSize(Vector2(0.1f, 0.1f));
		pCollider->SetCenter(Vector2(0.f, -0.7f));
		pCollider->SetActive(false);

		MonsterScript* Pscript = AddComponent<MonsterScript>();
		Pscript->SetBoss();
		Pscript->Initialize();

		m_pSharHP = new SharHP();
		SceneManger::AddGameObject(eLayerType::UI, m_pSharHP);
		m_pSharHP->Initialize();

		setattack();
		add_skill();

		MonsterFSM* pFSM = new MonsterFSM();
		pFSM->SetMonster(this);
		Pscript->SetFSM(pFSM);
	
		MonsterStand* pStand = new MonsterStand(); 
		pStand->SetTargetDistance(7.f);
		pStand->SetMinDistance(7.f);

		pFSM->AddState(pStand);
		pFSM->AddState(new PinkbeanStand());
		pFSM->AddState(new MonsterMove());
		pFSM->AddState(new MonsterAttack());
		pFSM->AddState(new MonsterDead());
		pFSM->AddState(new BossStart());

		pFSM->SetActiveState(Monster::eMonsterState::wait);
		pFSM->Initialize();

		set_minibean();
		create_child();
	}
	void PinkBean::Update()
	{
		update_HP();

		GameObject::Update();
	}
	void PinkBean::LateUpdate()
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
	void PinkBean::Render()
	{
		Monster::Render();
	}


	void PinkBean::update_HP()
	{
		float fFinalRatio = 0.f;
		float fRatio = 0.f;

		//핑크빈
		const tObjectInfo& tInfo = GetScript<MonsterScript>()->GetObjectInfo();
		fRatio = (tInfo.fHP / tInfo.fMaxHP) * 100.f;
		if (tInfo.fHP > 0.f)
			fFinalRatio += fRatio / 6.f;

		//석상
		for (UINT i = 0; i < m_vecMonster.size(); ++i)
		{
			if (m_vecMonster[i] == nullptr)
				return;

			const tObjectInfo& tInfo = m_vecMonster[i]->GetScript<MonsterScript>()->GetObjectInfo();
			fRatio = (tInfo.fHP / tInfo.fMaxHP) * 100.f;

			if (tInfo.fHP <= 0.f)
				continue;
			else
				fFinalRatio += fRatio / 6.f;
		}

		if (fFinalRatio <= 100.f/6.f && !m_bStart)
			start();

		m_pSharHP->SetHPValue(fFinalRatio);
	}

	void PinkBean::create_child()
	{
		m_vecMonster.resize(5);

		m_vecMonster[(UINT)ePinkBeanChild::Solomon] = new Solomon();
		m_vecMonster[(UINT)ePinkBeanChild::Solomon]->Initialize();
		SceneManger::AddGameObject(eLayerType::Monster, m_vecMonster[(UINT)ePinkBeanChild::Solomon]);
		
		m_vecMonster[(UINT)ePinkBeanChild::Rex] = new Rex();
		m_vecMonster[(UINT)ePinkBeanChild::Rex]->Initialize();
		SceneManger::AddGameObject(eLayerType::Monster, m_vecMonster[(UINT)ePinkBeanChild::Rex]);
		
		m_vecMonster[(UINT)ePinkBeanChild::Munin] = new Munin();
		m_vecMonster[(UINT)ePinkBeanChild::Munin]->Initialize();
		SceneManger::AddGameObject(eLayerType::Monster, m_vecMonster[(UINT)ePinkBeanChild::Munin]);

		m_vecMonster[(UINT)ePinkBeanChild::Whiggin] = new Whiggin();
		m_vecMonster[(UINT)ePinkBeanChild::Whiggin]->Initialize();
		SceneManger::AddGameObject(eLayerType::Monster, m_vecMonster[(UINT)ePinkBeanChild::Whiggin]);

		m_vecMonster[(UINT)ePinkBeanChild::Ariel] = new Ariel();
		m_vecMonster[(UINT)ePinkBeanChild::Ariel]->Initialize();
		SceneManger::AddGameObject(eLayerType::Monster, m_vecMonster[(UINT)ePinkBeanChild::Ariel]);
	}

	void PinkBean::add_skill()
	{
		//1
		for (int i = 0; i < 4; ++i)
		{
			Jenesis* pJenesis = new Jenesis();
			pJenesis->SetName(L"PinkBean_attack0");
			AddMonsterSkill(pJenesis);
		}
		
		//2
		MonsterAttackObject* attack1 = new MonsterAttackObject();
		attack1->SetName(L"PinkBean_attack1");
		AddMonsterSkill(attack1);

		//3
		for (int i = 0; i < 4; ++i)
		{
			PinkBeanStone* pStone = new PinkBeanStone();
			pStone->SetName(L"PinkBean_attack2");
			AddMonsterSkill(pStone);
		}

		//4
		for (int i = 0; i < 4; ++i)
		{
			RoccatBean* pRoccat = new RoccatBean();
			pRoccat->SetName(L"PinkBean_attack3");
			AddMonsterSkill(pRoccat);
		}
	}

	void PinkBean::set_minibean()
	{
		for (int i = 0; i < 4; ++i)
		{
			MiniBean* pMiniBean = new MiniBean();
			pMiniBean->SetOwner(this);
			pMiniBean->Initialize();
			m_queueMiniBean.push(pMiniBean);
		}
	}

	void PinkBean::setattack()
	{
		MonsterScript* Pscript = GetComponent<MonsterScript>();
		Vector3 vPosition = GetComponent<Transform>()->GetPosition();

		tMonsterAttack attack1 = {};
		attack1.tTime.fCoolTime = 15.f;
		attack1.bSkill = true;
		attack1.vScale = Vector2(0.f, 0.f);
		attack1.pFunction = std::bind(&PinkBean::attack1, this);
		
		attack1.iStartFrame = 10;
		attack1.iEndFrame = 11;
		
		Pscript->AddAttack(attack1);

		//2
		tMonsterAttack attack2 = {};
		attack2.tTime.fCoolTime = 20.f;
		
		attack2.pFunction = std::bind(&PinkBean::attack2, this);
		
		attack2.vPosition = vPosition;
		attack2.vScale = Vector2(8.f, 2.f);
		attack2.vOffset = Vector2(0.f, 0.f);
		attack2.tAttackInfo.fAttackDamage = 10.f;
		
		attack2.iStartFrame = 17;
		attack2.iEndFrame = 18;
		
		Pscript->AddAttack(attack2);
		
		////3
		tMonsterAttack attack3 = {};
		attack3.tTime.fCoolTime = 15.f;
		attack3.bSkill = true;
		attack3.vScale = Vector2(0.f, 0.f);
		attack3.pFunction = std::bind(&PinkBean::attack3, this);

		attack3.iStartFrame = 14;
		attack3.iEndFrame = 15;
		Pscript->AddAttack(attack3);

		//
		//
		tMonsterAttack attack4 = {};
		attack4.bSkill = true;
		attack4.tTime.fCoolTime = 20.f;
		
		attack4.vScale = Vector2(0.f, 0.f);
		attack4.pFunction = std::bind(&PinkBean::attack4, this);
		
		attack4.iStartFrame = 8;
		attack4.iEndFrame = 9;
		Pscript->AddAttack(attack4);

		tMonsterAttack attack5 = {};
		attack5.bSkill = true;
		attack5.tTime.fCoolTime = 10000.f;
		attack5.tTime.fCurTime = 10000.f;

		attack5.pFunction = std::bind(&PinkBean::attack5, this);

		attack5.iStartFrame = 8;
		attack5.iEndFrame = 9;
		Pscript->AddAttack(attack5);

		tMonsterAttack attack6 = {};
		attack6.bSkill = true;
		attack6.tTime.fCoolTime = 25.f;

		attack6.pFunction = std::bind(&PinkBean::attack6, this);

		attack6.iStartFrame = 13;
		attack6.iEndFrame = 14;
		Pscript->AddAttack(attack6);

		tMonsterAttack attack7 = {};
		attack7.bSkill = true;
		attack7.tTime.fCoolTime = 400000.f;

		attack7.pFunction = std::bind(&PinkBean::attack7, this);

		attack7.iStartFrame = 17;
		attack7.iEndFrame = 18;
		Pscript->AddAttack(attack7);

		tMonsterAttack attack8 = {};
		attack8.bSkill = true;
		attack8.tTime.fCoolTime = 21.f;

		attack8.pFunction = std::bind(&PinkBean::attack8, this);

		attack8.iStartFrame = 6;
		attack8.iEndFrame = 7;
		Pscript->AddAttack(attack8);

		tMonsterAttack attack9 = {};
		attack9.bSkill = true;
		attack9.tTime.fCoolTime = 30.f;

		attack9.pFunction = std::bind(&PinkBean::attack9, this);

		attack9.iStartFrame = 8;
		attack9.iEndFrame = 9;
		Pscript->AddAttack(attack9);

		tMonsterAttack attack10 = {};
		attack10.bSkill = true;
		attack10.tTime.fCoolTime = 1000000.f;

		attack10.pFunction = std::bind(&PinkBean::attack10, this);
		
		attack10.iStartFrame = 8;
		attack10.iEndFrame = 9;
		Pscript->AddAttack(attack10);

		tMonsterAttack attack11 = {};
		attack11.bSkill = true;
		attack11.tTime.fCoolTime = 10.f;
		
		attack11.pFunction = std::bind(&PinkBean::attack11, this);
		
		attack11.iStartFrame = 4;
		attack11.iEndFrame = 5;
		Pscript->AddAttack(attack11);
	}
	void PinkBean::attack1()
	{
		Vector3 vStartPos = GetComponent<Transform>()->GetPosition();
		vStartPos.z -= 0.1f;
		vStartPos.y += 1.5f;

		srand(time(NULL));
		for (int i = -2; i < 2; ++i)
		{
			int iIndx = (rand() % 4);

			float fOffsetX = i * 2.3f + vStartPos.x;
			fOffsetX += iIndx * 0.5f;

			MonsterAttackObject* pJenesis = GetMonsterSkill(L"PinkBean_attack0");
			if (pJenesis == nullptr)
				return;
			pJenesis->SetOnwer(this);

			pJenesis->GetComponent<Transform>()->SetPosition(fOffsetX, vStartPos.y, vStartPos.z);
			pJenesis->Initialize();
			EventManager::CreateObject(pJenesis, eLayerType::MonsterAttack);
		}


	}
	void PinkBean::attack2()
	{
		MonsterAttackObject* attack1 = GetMonsterSkill(L"PinkBean_attack1");
		if (attack1 == nullptr)
			return;
		MonsterScript* pMonsterScript = GetScript<MonsterScript>();
		pMonsterScript->SetMonsterAttack(attack1);
		attack1->SetOnwer(this);

		EventManager::CreateObject(attack1, eLayerType::MonsterAttack);
	}
	void PinkBean::attack3()
	{
		Vector3 vStartPos = GetComponent<Transform>()->GetPosition();
		vStartPos.z -= 0.1f;
		vStartPos.y += 1.65f;

		srand(time(NULL));
		for (int i = -2; i < 2; ++i)
		{
			int iIndx = (rand() % 4);

			float fOffsetX = i * 2.3 + vStartPos.x;
			fOffsetX += iIndx * 0.5f;

			MonsterAttackObject* pStone = GetMonsterSkill(L"PinkBean_attack2");
			if (pStone == nullptr)
				return;
			pStone->SetOnwer(this);

			pStone->GetComponent<Transform>()->SetPosition(fOffsetX, vStartPos.y, vStartPos.z);
			pStone->Initialize();
			EventManager::CreateObject(pStone, eLayerType::MonsterAttack);
		}
	}
	void PinkBean::attack4()
	{
		Vector3 vStartPos = GetComponent<Transform>()->GetPosition();
		vStartPos.z -= 0.1f;
		vStartPos.y -= 0.35f;

		srand(time(NULL));
		for (int i = -4; i < 4; i+=2)
		{
			int iIndx = (rand() % 4);

			float fOffsetX = i * 1.f + vStartPos.x;

			MonsterAttackObject* pRoccat = GetMonsterSkill(L"PinkBean_attack3");
			if (pRoccat == nullptr)
				return;
			pRoccat->SetOnwer(this);

			pRoccat->GetComponent<Transform>()->SetPosition(fOffsetX, vStartPos.y, vStartPos.z);
			pRoccat->Initialize();
			EventManager::CreateObject(pRoccat, eLayerType::MonsterAttack);
		}
	}
	void PinkBean::attack5()
	{
		//소환
		srand(time(NULL));
		for (int i = 1; i <= 4; ++i)
		{
			MiniBean* pMiniBean = m_queueMiniBean.front();
			m_queueMiniBean.pop();

			Vector3 vPosition = GetComponent<Transform>()->GetPosition();

			int x = (rand() % 4);
			float fOffsetX = i * 0.15f;

			int y = (rand() % 3) -1.f;
			float fOffsetY = y * 0.3f;

			vPosition.x += fOffsetX;
			vPosition.y += (fOffsetY -0.5f);
			pMiniBean->GetComponent<Transform>()->SetPosition(vPosition);

			EventManager::CreateObject(pMiniBean, eLayerType::Monster);
		}
		
	}

	void PinkBean::attack6()
	{
		//공반
		BattleManager::Buff_Stat(this,BattleManager::eUpStatType::ReflexAttack,1.f);
	}
	void PinkBean::attack7()
	{
		//언데드
		BattleManager::HitchAbnormal(BattleManager::eAbnormalType::Undead);
	}
	void PinkBean::attack8()
	{
		//유혹
		BattleManager::HitchAbnormal(BattleManager::eAbnormalType::temptation);
	}
	void PinkBean::attack9()
	{
		//혼란
		BattleManager::HitchAbnormal(BattleManager::eAbnormalType::Confusion);
	}
	void PinkBean::attack10()
	{
		//변신
		BattleManager::HitchAbnormal(BattleManager::eAbnormalType::Variation);
	}
	void PinkBean::attack11()
	{
		GameObject* pObj = SceneManger::FindPlayer();
		Vector3 vTargetPos = pObj->GetComponent<Transform>()->GetPosition();
		Vector3 vPosition = GetComponent<Transform>()->GetPosition();

		Vector3 vDiff = vTargetPos - vPosition;
		vPosition.x += vDiff.x;
		GetComponent<Transform>()->SetPosition(vPosition);
		//텔포
	}
	void PinkBean::start()
	{
		m_bStart = true;

		Vector3 vPosition = GetComponent<Transform>()->GetPosition();
		vPosition.y = -1.46;
		GetComponent<Transform>()->SetPosition(vPosition);

		GetComponent<Collider2D>()->SetActive(true);
	}
}