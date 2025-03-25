#include "WHorntailLeftHand.h"
#include "WRenderer.h"
#include "WResources.h"
#include "WAnimator.h"
#include "WMonsterAttack.h"
#include "WMonsterFSM.h"
#include "WBossStand.h"
#include "WMonsterScript.h"
#include "WSceneManger.h"
#include "WSpear.h"
#include "WEventManager.h"
#include "WBattleManager.h"
#include "WHorntailDead.h"
namespace W
{
	HorntailLeftHand::HorntailLeftHand(Horntail* _pOwner):
		m_pOwner(_pOwner)
	{
		SetName(L"LeftHand");

		MeshRenderer* pRenderer = AddComponent<MeshRenderer>();
		pRenderer->SetMesh(Resources::Find<Mesh>(L"RectMesh"));


		std::shared_ptr<Material> pMater = std::make_shared<Material>();
		pMater->SetRenderinMode(eRenderingMode::Transparent);
		pMater->SetShader(Resources::Find<Shader>(L"MonsterShader"));
		Resources::Insert(L"horntailLeftHandMater", pMater);

		pRenderer->SetMaterial(pMater);

		std::shared_ptr<Texture> pAtlas = Resources::Find<Texture>(L"LeftHandTex");
		pAtlas->BindShaderResource(eShaderStage::PS, 12);

		Animator* pAnim = AddComponent<Animator>();
		pAnim->Create(L"LeftHand_stand", pAtlas, Vector2(0.f, 0.f), Vector2(500.f, 300.f), 5, Vector2(1000.f, 1000.f), Vector2::Zero, 0.15f);
		pAnim->Create(L"LeftHand_attack0", pAtlas, Vector2(0.f, 300.f), Vector2(500.f, 300.f), 18, Vector2(1000.f, 1000.f), Vector2::Zero, 0.15f);
		pAnim->Create(L"LeftHand_attack1", pAtlas, Vector2(0.f, 600.f), Vector2(500.f, 300.f), 16, Vector2(1000.f, 1000.f), Vector2::Zero, 0.15f);
		pAnim->Create(L"LeftHand_attack2", pAtlas, Vector2(0.f, 900.f), Vector2(500.f, 300.f), 17, Vector2(1000.f, 1000.f), Vector2::Zero, 0.15f);
		pAnim->Create(L"LeftHand_dead", pAtlas, Vector2(0.f, 1200.f), Vector2(500.f, 300.f), 16, Vector2(1000.f, 1000.f), Vector2::Zero, 0.15f);

	}
	HorntailLeftHand::~HorntailLeftHand()
	{
		ObjectPoolManager::ReleaseObject(L"spear");
	}

	void HorntailLeftHand::add_skill()
	{
		//1
		Spear* pSpear = new Spear();
		pSpear->SetName(L"spear");
		AddMonsterSkill(pSpear);
	}

	void HorntailLeftHand::Initialize()
	{
		GetComponent<Transform>()->SetScale(11.f, 11.f, 0.f);
		GetComponent<Transform>()->SetPosition(-4.27f, -0.9f, -1.5f);
		Collider2D* pCollider = AddComponent<Collider2D>();
		pCollider->SetSize(Vector2(0.2f, 0.2f));
		pCollider->SetCenter(Vector2(1.6f,0.f));

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
	void HorntailLeftHand::Update()
	{
		Monster::Update();
	}

	void HorntailLeftHand::LateUpdate()
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

	void HorntailLeftHand::Render()
	{
		renderer::MonsterCB MonsterCB;
		MonsterCB.vMonsterDir.x = 1;

		ConstantBuffer* pConstBuffer = renderer::constantBuffer[(UINT)eCBType::Monster];
		//Vector4 vPosition(m_vPosition.x, m_vPosition.y, m_vPosition.z, 1.f);
		pConstBuffer->SetData(&MonsterCB);
		pConstBuffer->Bind(eShaderStage::PS);

		GameObject::Render();
	}

	void HorntailLeftHand::setAttack()
	{
		MonsterScript* Pscript = GetComponent<MonsterScript>();

		//1
		tMonsterAttack attack = {};
		attack.tTime.fCoolTime = 12.f;
		attack.bSkill = true;
		attack.vScale = Vector2::Zero;

		attack.iStartFrame = 13;
		attack.iEndFrame = 14;
		attack.pFunction = std::bind(&HorntailLeftHand::create_spear, this);

		Pscript->AddAttack(attack);

		//2
		tMonsterAttack attack1 = {};
		attack1.tTime.fCoolTime = 10.f;
		attack1.bSkill = true;
		attack1.vScale = Vector2::Zero;

		attack1.iStartFrame = 11;
		attack1.iEndFrame = 12;

		attack1.pFunction = std::bind(&HorntailLeftHand::temptation, this);
		Pscript->AddAttack(attack1);

		//3
		tMonsterAttack attack2 = {};
		attack2.tTime.fCoolTime = 15.f;
		attack2.bSkill = true;
		attack2.vScale = Vector2::Zero;

		attack2.iStartFrame = 12;
		attack2.iEndFrame = 13;
		attack2.pFunction = std::bind(&HorntailLeftHand::buff_defnes, this);
		Pscript->AddAttack(attack2);
	}

	void HorntailLeftHand::create_spear()
	{
		GameObject* pGameObj = SceneManger::FindPlayer();

		if (pGameObj != nullptr)
		{
			Vector3 pPlayerPos = pGameObj->GetComponent<Transform>()->GetPosition();
			Vector3 pPos = GetComponent<Transform>()->GetPosition();

			pPlayerPos.z = 0;
			pPos.z = 0;

			float fLen = (pPlayerPos - pPos).Length();

			if (fLen <= 3.f)
			{
				MonsterAttackObject* pSpear = GetMonsterSkill(L"spear");
				if (pSpear == nullptr)
					return;
				pSpear->SetOnwer(this);

				pSpear->Initialize();
				SceneManger::AddGameObject(eLayerType::MonsterAttack, pSpear);
			}
		}
	}

	void HorntailLeftHand::temptation()
	{
		BattleManager::HitchAbnormal(BattleManager::eAbnormalType::temptation);
	}

	void HorntailLeftHand::buff_defnes()
	{
		if (m_pBuffFunc)
			m_pBuffFunc();
	}

}