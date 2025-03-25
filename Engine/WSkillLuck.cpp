#include "WSkillLuck.h"
#include "WPlayer.h"
#include "WPlayerBody.h",
#include "WAnimator.h"
#include "WPlayerSkill.h"
#include "WEffect.h"
#include "WEffect.h"
#include "WResources.h"
#include "WShuriken.h"
#include "WPlayerScript.h"
#include "WAttackScript.h"
#include "WSceneManger.h"
#include "WSkillManager.h"
#include "WEventManager.h"
#include "WShadow.h"
#include "WBattleManager.h"
namespace W
{
	SkillLuck::SkillLuck():
		m_iCallStack(1),
		m_iCreateCnt(0),
		m_iMaxCnt(0)
	{
		SetSkillType(Player::ePlayerSkill::luck);
		SetStateName(L"_swing1");

		tSkillTime tTime = {};
		tTime.fCoolTime = 0.f;
		tTime.fCurTime = 0.f;
		SetCoolTime(tTime);

		m_pEffectAtlas = Resources::Load<Texture>(L"luckeffect", L"..\\Resources\\Texture\\Player\\skill\\effect.png");
		m_pHitEffectAtlas = Resources::Load<Texture>(L"luckhit", L"..\\Resources\\Texture\\Player\\skill\\hit.png");

		for (int i = 0; i < 8; ++i)
		{
			CreateEffet(m_pHitEffectAtlas, L"luck", Vector2(0.f, 0.f), Vector2(74.f, 74.f), 4, 1,
				Vector2(90.f, 90.f), Vector2::Zero, 0.1f);
		}

		CreateEffet(m_pEffectAtlas, L"luckeffect", Vector2(0.f, 0.f), Vector2(112.f, 52.f), 5, 1,
			Vector2(110.f, 110.f), Vector2(0.4f, 0.f), 0.1f);


		SetSound(Resources::Load<AudioClip>(L"lucksound", L"..\\Resources\\sound\\skill\\luck.mp3"),false);
	}
	SkillLuck::~SkillLuck()
	{

	}
	void SkillLuck::Update()
	{
		Player* pPlayer = GetPlayer();
		PlayerBody* pBody = pPlayer->GetPlayerChild<PlayerBody>();
		Animation* pBodyAnim = pBody->GetComponent<Animator>()->GetActiveAnimation();

		int iAnimIndex = pBodyAnim->GetCurIndex();

		bool bComplete = pBodyAnim->IsComplete();
		if (bComplete)
			Exit();

		if (iAnimIndex == 2 && m_iCallStack == 1)
		{
			m_iCallStack = 0;
			activeskill_luck();
		}
	}

	void SkillLuck::Initialize()
	{
		PlayerScript* pScript = GetPlayer()->GetScript<PlayerScript>();
		for (int i = 0; i < 12; ++i)
		{
			Shuriken* pShuriken = pScript->CreateShuriken();
			pShuriken->SetName(L"luck");
			pScript->AddPlayerSkill(pShuriken);
		}
	}

	void SkillLuck::Enter()
	{
		if (GetPlayer()->GetCurPlayerState() == Player::ePlayerState::ladder)
		{
			Exit();
			return;
		}

		SkillState::Enter();

		m_iCallStack = 1;

		UINT iAttackNumber = rand() % 2;
		if (iAttackNumber == 0)
			GetPlayer()->SetCurStateName(L"_swing1");
		else
			GetPlayer()->SetCurStateName(L"_swing2");

		Effect* pEffect = BattleManager::GetEffect(L"luckeffect");
		StartEffect(pEffect);

	}
	void SkillLuck::Exit()
	{
		SkillState::Exit();
	}

	void SkillLuck::activeskill_luck()
	{
		Player* pPlayer = GetPlayer();
		m_iMaxCnt = 2;
		if (pPlayer->IsShadow())
		{
			m_iMaxCnt = 4;
			pPlayer->GetShadow()->Set_Attack(std::bind(&SkillLuck::create_luck, this), 0.04f);
		}
		create_luck();
		
	}
	void SkillLuck::create_luck()
	{
		for (int i = 0; i < 2; ++i)
		{
			++m_iCreateCnt;

			PlayerAttackObject* pAttackObj = GetPlayer()->GetScript<PlayerScript>()->GetPlayerSkill(L"luck");
			Shuriken* pShuriken = dynamic_cast<Shuriken*>(pAttackObj);
			
			pShuriken->SetDir(GetPlayer()->GetDir());
		
			//추가 데미지
			AddDamage(pShuriken);

			tAttackInfo& tAttack = pShuriken->GetScript<AttackScript>()->GetAttackInfo();
			tAttack.iDamageCount = m_iMaxCnt;

			Transform* pTr = pShuriken->GetComponent<Transform>();
			Vector3 vPosition = GetPlayer()->GetComponent<Transform>()->GetPosition();
			vPosition.y += 0.3f;
			vPosition.y -= 0.1f * m_iCreateCnt;

			vPosition.x += (0.6f * GetPlayer()->GetDir());
			vPosition.x -= 0.3f * m_iCreateCnt * GetPlayer()->GetDir();

			pTr->SetPosition(vPosition);

			EventManager::CreateObject(pShuriken, eLayerType::AttackObject);
		}

		if (m_iMaxCnt <= m_iCreateCnt)
		{
			m_iCreateCnt = 0;
		}
	}
}