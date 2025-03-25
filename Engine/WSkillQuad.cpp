#include "WSkillQuad.h"
#include "WResources.h"
#include "WAnimator.h"
#include "WPlayerBody.h"
#include "WShadow.h"
#include "WPlayer.h"
#include "WPlayerScript.h"
#include "WShuriken.h"
#include "WAttackScript.h"
#include "WEventManager.h"
#include "WEffect.h"
#include "WBattleManager.h"
namespace W
{
	SkillQuad::SkillQuad():
		m_iCallStack(1),
		m_iCreateCnt(0),
		m_iMaxCnt(0)
	{
		SetSkillType(Player::ePlayerSkill::quad);
		SetStateName(L"_swingQS");

		tSkillTime tTime = {};
		tTime.fCoolTime = 0.f;
		tTime.fCurTime = 0.f;
		SetCoolTime(tTime);

		
		
		m_pHitEffectAtlas = Resources::Load<Texture>(L"quadhit", L"..\\Resources\\Texture\\Player\\skill\\hit1.png");
		for (int i = 0; i < 8; ++i)
		{
			Effect* pEffect = CreateEffet(m_pHitEffectAtlas, L"quad", Vector2(0.f, 0.f), Vector2(146.f, 146.f), 9, 1,
				Vector2(150.f, 150.f), Vector2::Zero, 0.06f);
			pEffect->GetComponent<Transform>()->SetScale(1.5f, 1.5f, 0.f);
		}
		
		for (int i = 0; i < 2; ++i)
		{
			m_pEffectAtlas = Resources::Load<Texture>(L"quadffect", L"..\\Resources\\Texture\\Player\\skill\\effect7.png");
			CreateEffet(m_pEffectAtlas, L"quadffect", Vector2(0.f, 0.f), Vector2(299, 196.f), 9, 1,
				Vector2(300.f, 300.f), Vector2(0.4f, 0.f), 0.06f);
		}

		SetSound(Resources::Load<AudioClip>(L"quadsound", L"..\\Resources\\sound\\skill\\qs.mp3"), false);

	}
	SkillQuad::~SkillQuad()
	{

	}
	void SkillQuad::Update()
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
			activeskill_quad();
		}
	}
	void SkillQuad::Initialize()
	{
		PlayerScript* pScript = GetPlayer()->GetScript<PlayerScript>();
		for (int i = 0; i < 24; ++i)
		{
			Shuriken* pShuriken = pScript->CreateShuriken();
			pShuriken->SetName(L"quad");
			pScript->AddPlayerSkill(pShuriken);
		}
	}
	void SkillQuad::Enter()
	{
		if (GetPlayer()->GetCurPlayerState() == Player::ePlayerState::ladder)
		{
			Exit();
			return;
		}

		SkillState::Enter();

		m_iCallStack = 1;

		Effect* pEffect =BattleManager::GetEffect(L"quadffect");
		StartEffect(pEffect);
		pEffect->GetComponent<Transform>()->SetScale(4.f, 4.f, 0.f);
	}
	void SkillQuad::Exit()
	{
		SkillState::Exit();
	}
	void SkillQuad::activeskill_quad()
	{
		Player* pPlayer = GetPlayer();
		m_iMaxCnt = 4;

		if (pPlayer->IsShadow())
		{
			m_iMaxCnt *= 2;
			pPlayer->GetShadow()->Set_Attack(std::bind(&SkillQuad::create_quad, this), 0.07f);
		}
		create_quad();
	}

	void SkillQuad::create_quad()
	{
		for (int i = 0; i < 4; ++i)
		{
			++m_iCreateCnt;

			PlayerAttackObject* pAttackObj = GetPlayer()->GetScript<PlayerScript>()->GetPlayerSkill(L"quad");
			Shuriken* pShuriken = dynamic_cast<Shuriken*>(pAttackObj);
			//pShuriken->GetComponent<Collider2D>()->SetActive(true);
			pShuriken->SetDir(GetPlayer()->GetDir());
			//추가 데미지
			//AddDamage(pShuriken);

			tAttackInfo& tAttack = pShuriken->GetScript<AttackScript>()->GetAttackInfo();
			tAttack.fAttackDamage = 1.f;
			tAttack.iDamageCount = m_iMaxCnt;

			Transform* pTr = pShuriken->GetComponent<Transform>();
			Vector3 vPosition = GetPlayer()->GetComponent<Transform>()->GetPosition();
			vPosition.y += 0.6f;
			vPosition.y -= 0.1f * m_iCreateCnt;
			vPosition.x += (2.f * GetPlayer()->GetDir());
			vPosition.x -= 0.33f * m_iCreateCnt * GetPlayer()->GetDir();

			pTr->SetPosition(vPosition);

			EventManager::CreateObject(pShuriken, eLayerType::AttackObject);
		}

		if (m_iMaxCnt <= m_iCreateCnt)
		{
			m_iCreateCnt = 0;
		}
	}

}