#include "WSkillRaid.h"
#include "WResources.h"
#include "WEffect.h"
#include "WAttackScript.h"
#include "WPlayerAttackObject.h"
#include "WPlayer.h"
#include "WPlayerScript.h"
#include "WEventManager.h"
#include "WBattleManager.h"
#include "WLight.h"
#include "WPlayerScript.h"
namespace W
{
	SkillRaid::SkillRaid():
		m_pFadeEffect(nullptr)
	{
		SetSkillType(Player::ePlayerSkill::raid);
		SetStateName(L"_alert");

		tSkillTime tTime = {};
		tTime.fCoolTime = 10.f;
		tTime.fCurTime = 0.f;
		SetCoolTime(tTime);

		m_pEffectAtlas = Resources::Load<Texture>(L"raideffect1", L"..\\Resources\\Texture\\Player\\skill\\effect8.png");
		Resources::Load<Texture>(L"raideffect2", L"..\\Resources\\Texture\\Player\\skill\\effect9.png");

		Effect* pEffect = CreateEffet(m_pEffectAtlas, L"raideffect1", Vector2(0.f, 0.f),
			Vector2(1060.f, 727.f), 10, 3, Vector2(1000.f, 1000.f), Vector2(0.2f, 2.f), 0.1f);
		pEffect->AddComponent<Light>();

		Effect* pEffect2 = CreateEffet(Resources::Find<Texture>(L"raideffect2"), L"raideffect2", Vector2(0.f, 0.f), Vector2(880.f, 637.f), 10, 3,
			Vector2(1000.f, 1000.f), Vector2(0.2f, 2.f), 0.1f);
		pEffect2->SetFunction(std::bind(&SkillRaid::activeskill_raid, this), 11);

		pEffect->GetComponent<Transform>()->SetScale(10.f, 10.f, 0.f);
		pEffect2->GetComponent<Transform>()->SetScale(10.f, 10.f, 0.f);

		m_pHitEffectAtlas = Resources::Load<Texture>(L"raidhit", L"..\\Resources\\Texture\\Player\\skill\\hit2.png");
		for (int i = 0; i < 7; ++i)
		{
			Effect* pEffet3 = CreateEffet(m_pHitEffectAtlas, L"raid", Vector2(0.f, 0.f), Vector2(276.f, 252.f), 6, 1,
				Vector2(300.f, 300.f), Vector2(0.f, 0.f), 0.2f);
			pEffet3->GetComponent<Transform>()->SetScale(3.5f, 3.5f, 0.f);
		}

		SetSound(Resources::Load<AudioClip>(L"raidsound", L"..\\Resources\\sound\\skill\\raid.mp3"), false);
		Resources::Load<AudioClip>(L"raid_hit", L"..\\Resources\\sound\\skill\\raid_hit.mp3");
	}
	SkillRaid::~SkillRaid()
	{

	}
	void SkillRaid::Update()
	{
		if (m_bCreate)
			Exit();
	}
	void SkillRaid::Initialize()
	{
		for (int i = 0; i < 2; ++i)
			create_raid();
	}
	void SkillRaid::Enter()
	{
		if (GetPlayer()->GetCurPlayerState() == Player::ePlayerState::ladder)
		{
			Exit();
			return;
		}
		SkillState::Enter();

		m_bCreate = false;
		
		m_pFadeEffect = BattleManager::GetEffect(L"raideffect1");
		Effect* pEffect2 = BattleManager::GetEffect(L"raideffect2");
		StartEffect(m_pFadeEffect);
		StartEffect(pEffect2);

		Light* lightComp = m_pFadeEffect->GetComponent<Light>();
		lightComp->SetType(eLightType::FadeOut);
		lightComp->SetColor(Vector4(0.8f, 0.8f, 0.8f, 0.0f));
		//lightComp->SetColor(Vector4(1.f, 1.f, 1.f, 1.0f));
		lightComp->SetRadius(10.0f);

		m_pFadeEffect->SetFunction(std::bind(&SkillRaid::fade_out, this), 28);
	}

	void SkillRaid::Exit()
	{
		SkillState::Exit();
	}

	void SkillRaid::create_raid()
	{
		PlayerAttackObject* pAttackObj = new PlayerAttackObject();

		pAttackObj->SetName(L"raid");
		pAttackObj->SetPlayer(GetPlayer());

		Collider2D* pCollider = pAttackObj->AddComponent<Collider2D>();
		pCollider->SetSize(Vector2(8.f, 8.f));
		GetPlayer()->GetScript<PlayerScript>()->AddPlayerSkill(pAttackObj);

		pAttackObj->AddComponent<AttackScript>()->SetStayObject(7, 0.8f);
		pAttackObj->GetComponent<AttackScript>()->SetDeleteTime(1.f);

		pAttackObj->SetHitSound(Resources::Find<AudioClip>(L"raid_hit"),false);
	}

	void SkillRaid::activeskill_raid()
	{
		PlayerAttackObject* pAttackObj = GetPlayer()->GetScript<PlayerScript>()->GetPlayerSkill(L"raid");
		pAttackObj->GetScript<AttackScript>()->SetDeleteObject(false);
		Transform* pTr = pAttackObj->GetComponent<Transform>();
		Vector3 vPosition = GetPlayer()->GetComponent<Transform>()->GetPosition();
		pTr->SetPosition(vPosition);

		const tAttackInfo& Attack = GetPlayer()->GetScript<PlayerScript>()->GetAttackInfo();

		tAttackInfo AttackInfo;
		AttackInfo.fAttackDamage = 1.f;
		AttackInfo.fAttack = Attack.fAttack;
		AttackInfo.fDex = Attack.fDex;

		AttackInfo.fAttRcnt = 0.3f;
		AttackInfo.fAttRigidityTime = 0.3f;
		AttackInfo.fAttUpperRcnt = 0.f;

		AttackInfo.iDamageCount = 7;

		pAttackObj->GetScript<AttackScript>()->SetAttackInfo(AttackInfo);
		EventManager::CreateObject(pAttackObj, eLayerType::AttackObject);

		m_bCreate = true;
	}

	void SkillRaid::fade_out()
	{
		Light* lightComp = m_pFadeEffect->GetComponent<Light>();
		lightComp->SetType(eLightType::End);
		//lightComp->SetRadius(5.0f);
	}

}