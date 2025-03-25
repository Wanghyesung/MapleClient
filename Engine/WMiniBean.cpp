#include "WMiniBean.h"
#include "WResources.h"
#include "WRigidbody.h"
#include "WAnimator.h"
#include "WMonsterScript.h"
#include "WMonsterFSM.h"
#include "WMonsterDead.h"
#include "WMonsterAttack.h"
#include "WBossStart.h"
#include "WBattleManager.h"
#include "WSceneManger.h"
#include "WPinkBean.h"
#include "WMonsterMove.h"
#include "WMonsterStand.h"
#include "WEffect.h"
#include "WEventManager.h"
#include "WMiniBeanAttack.h"
namespace W
{
	MiniBean::MiniBean():
		//m_vDir(Vector2::Zero),
		m_pOwner(nullptr)
	{
		SetName(L"MiniBean");

		MeshRenderer* pRenderer = AddComponent<MeshRenderer>();
		pRenderer->SetMesh(Resources::Find<Mesh>(L"RectMesh"));


		std::shared_ptr<Material> pMater = std::make_shared<Material>();
		pMater->SetRenderinMode(eRenderingMode::Transparent);
		pMater->SetShader(Resources::Find<Shader>(L"MonsterShader"));
		Resources::Insert(L"MiniBeanlMater", pMater);

		pRenderer->SetMaterial(pMater);

		AddComponent<Rigidbody>();

		Animator* pAnim = AddComponent<Animator>();

		std::shared_ptr<Texture> pminiBean = Resources::Find<Texture>(L"miniBean");

		pAnim->Create(L"MiniBean_start_left", pminiBean, Vector2(0.f, 0.f), Vector2(320.f, 250.f), 6, Vector2(350.f, 350.f), Vector2::Zero, 0.15f);
		pAnim->Create(L"MiniBean_stand_left", pminiBean, Vector2(0.f, 250.f), Vector2(320.f, 250.f), 4, Vector2(350.f, 350.f), Vector2::Zero, 0.15f);
		pAnim->Create(L"MiniBean_move_left", pminiBean, Vector2(0.f, 250.f), Vector2(320.f, 250.f), 4, Vector2(350.f, 350.f), Vector2::Zero, 0.15f);
		pAnim->Create(L"MiniBean_attack0_left", pminiBean, Vector2(0.f, 500.f), Vector2(320.f, 250.f), 10, Vector2(350.f, 350.f), Vector2::Zero, 0.15f);
		pAnim->Create(L"MiniBean_attack1_left", pminiBean, Vector2(0.f, 750.f), Vector2(320.f, 250.f), 9, Vector2(350.f, 350.f), Vector2::Zero, 0.15f);
		pAnim->Create(L"MiniBean_dead_left", pminiBean, Vector2(0.f, 1000.f), Vector2(320.f, 250.f), 10, Vector2(350.f, 350.f), Vector2::Zero, 0.15f);
						
		pAnim->Create(L"MiniBean_start_right", pminiBean, Vector2(2880, 0.f), Vector2(-320.f, 250.f), 6, Vector2(350.f, 350.f), Vector2::Zero, 0.15f);
		pAnim->Create(L"MiniBean_stand_right", pminiBean, Vector2(2880, 250.f), Vector2(-320.f, 250.f), 4, Vector2(350.f, 350.f), Vector2::Zero, 0.15f);
		pAnim->Create(L"MiniBean_move_right", pminiBean, Vector2(2880, 250.f), Vector2(-320.f, 250.f), 4, Vector2(350.f, 350.f), Vector2::Zero, 0.15f);
		pAnim->Create(L"MiniBean_attack0_right", pminiBean, Vector2(2880, 500.f), Vector2(-320.f, 250.f), 10, Vector2(350.f, 350.f), Vector2::Zero, 0.15f);
		pAnim->Create(L"MiniBean_attack1_right", pminiBean, Vector2(2880, 750.f), Vector2(-320.f, 250.f), 9, Vector2(350.f, 350.f), Vector2::Zero, 0.15f);
		pAnim->Create(L"MiniBean_dead_right", pminiBean, Vector2(2880, 1000.f), Vector2(-320.f, 250.f), 10, Vector2(350.f, 350.f), Vector2::Zero, 0.15f);

	}
	MiniBean::~MiniBean()
	{
		ObjectPoolManager::ReleaseObject(L"MiniBean_attack0");
	}
	void MiniBean::Initialize()
	{
		//get_dir();

		GetComponent<Transform>()->SetScale(3.f, 3.f, 0.f);
		//GetComponent<Transform>()->SetPosition(0.1f, -0.4f, -1.5f);
		Collider2D* pCollider = AddComponent<Collider2D>();
		pCollider->SetSize(Vector2(0.2f, 0.2f));
		pCollider->SetCenter(Vector2(0.f, 0.f));
		pCollider->SetActive(false);

		MonsterScript* Pscript = AddComponent<MonsterScript>();
		Pscript->SetBoss();
		Pscript->Initialize();

		setattack();

		MonsterFSM* pFSM = new MonsterFSM();
		pFSM->SetMonster(this);
		Pscript->SetFSM(pFSM);

		MonsterStand* pStand = new MonsterStand();
		std::random_device rDiv;
		std::mt19937 en(rDiv());
		std::uniform_int_distribution<int> dis(1, 4);
		float fDis = (float)dis(en);
		pStand->SetMinDistance(fDis);
		pFSM->AddState(pStand);

		std::uniform_int_distribution<int> speed(1, 3);
		Pscript->SetSpeed((float)speed(en) / 5.f);

		pFSM->AddState(new MonsterMove());
		pFSM->AddState(new MonsterAttack());
		pFSM->AddState(new MonsterDead());
		pFSM->AddState(new BossStart());

		pFSM->SetActiveState(Monster::eMonsterState::start);
		pFSM->Initialize();
	}
	void MiniBean::Update()
	{


		Monster::Update();
	}
	void MiniBean::LateUpdate()
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
	void MiniBean::Render()
	{
		Monster::Render();
	}
	void MiniBean::setattack()
	{
		MonsterScript* Pscript = GetComponent<MonsterScript>();
		Vector3 vPosition = GetComponent<Transform>()->GetPosition();

		//2
		std::random_device rDiv;
		std::mt19937 en(rDiv());
		std::uniform_int_distribution<int> dis(5, 8);
		float fTime = (float)dis(en);
		tMonsterAttack attack1 = {};
		attack1.tTime.fCoolTime = fTime;
		attack1.tTime.fCoolTime = fTime;

		attack1.bSkill = true;
		attack1.pFunction = std::bind(&MiniBean::attack0, this);

		attack1.iStartFrame = 6;
		attack1.iEndFrame = 7;

		Pscript->AddAttack(attack1);

		tMonsterAttack attack2 = {};
		attack2.tTime.fCoolTime = 50.f;
		attack2.tTime.fCurTime = 50.f;
		attack2.bSkill = true;
		attack2.vScale = Vector2(0.f, 0.f);
		attack2.pFunction = std::bind(&MiniBean::attack1, this);
		
		attack2.iStartFrame = 4;
		attack2.iEndFrame = 5;

		Pscript->AddAttack(attack2);
	}
	void MiniBean::attack0()
	{
		GameObject* pGameObj = SceneManger::FindPlayer();

		if (pGameObj != nullptr)
		{
			Vector3 pPlayerPos = pGameObj->GetComponent<Transform>()->GetPosition();
			Vector3 pPos = GetComponent<Transform>()->GetPosition();

			pPlayerPos.z = 0;
			pPos.z = 0;

			float fLen = (pPlayerPos - pPos).Length();

			if (fLen <= 4.f)
			{
				MiniBeanAttack* attack1 = new MiniBeanAttack();
				attack1->SetOnwer(this);
				attack1->Initialize();
				attack1->SetName(L"MiniBean_attack0");

				MonsterScript* pMonsterScript = GetScript<MonsterScript>();
				pMonsterScript->SetMonsterAttack(attack1);
				attack1->SetOnwer(this);

				EventManager::CreateObject(attack1, eLayerType::MonsterAttack);
			}
		}
	}
	void MiniBean::attack1()
	{
		BattleManager::Buff_Stat(this, BattleManager::eUpStatType::Ignore, 1);
	}
	
}