#include "WSkillAven.h"
#include "WResources.h"
#include "WEffect.h"
#include "WAnimator.h"
#include "WPlayerBody.h"
#include "WAven.h"
#include "WAttackScript.h"
#include "WEventManager.h"
#include "WShadow.h"
#include "WBattleManager.h"
#include "WPlayerScript.h"
namespace W
{
	SkillAven::SkillAven():
		m_iCallStack(1),
		m_bStart(false)
	{
		SetSkillType(Player::ePlayerSkill::aven);
		SetStateName(L"_swing2");

		tSkillTime tTime = {};
		tTime.fCoolTime = 0.f;
		tTime.fCurTime = 0.f;
		SetCoolTime(tTime);

		m_pEffectAtlas = Resources::Load<Texture>(L"aveneffect", L"..\\Resources\\Texture\\Player\\skill\\effect4.png");
		Effect* pEffect = CreateEffet(m_pEffectAtlas, L"aveneffect", Vector2(0.f, 0.f), Vector2(121.f, 71.f), 14, 1,
			Vector2(110.f, 110.f), Vector2(0.f, 0.f), 0.06f);
		pEffect->SetFunction(std::bind(&SkillAven::activeskill_aven, this), 12);
		//m_pHitEffectAtlas = Resources::Load<Texture>(L"kuckhit", L"..\\Resources\\Texture\\Player\\skill\\hit.png");

		SetSound(Resources::Load<AudioClip>(L"avensound", L"..\\Resources\\sound\\skill\\aven.mp3"), false);
	}
	SkillAven::~SkillAven()
	{

	}
	void SkillAven::Update()
	{
		if (!m_bStart)
			return;

		Player* pPlayer = GetPlayer();
		PlayerBody* pBody = pPlayer->GetPlayerChild<PlayerBody>();
		Animation* pBodyAnim = pBody->GetComponent<Animator>()->GetActiveAnimation();

		bool bComplete = pBodyAnim->IsComplete();
		if (bComplete)
			Exit();

	}
	void SkillAven::Initialize()
	{
		PlayerScript* pScript = GetPlayer()->GetScript<PlayerScript>();
		for (int i = 0; i < 3; ++i)
		{
			Aven* pAven = new Aven();
			pAven->SetName(L"Aven");
			pAven->Initialize();
			pAven->SetPlayer(GetPlayer());
			pScript->AddPlayerSkill(pAven);
		}
	}
	void SkillAven::Enter()
	{

		if (GetPlayer()->GetCurPlayerState() == Player::ePlayerState::ladder)
		{
			Exit();
			return;
		}
		SkillState::Enter();

		GetPlayer()->SetAnimStop(true);

		m_iCallStack = 1;
		m_bStart = false;
	
		GetPlayer()->SetCurStateName(L"_swing2");

		Effect* pEffect=  BattleManager::GetEffect(L"aveneffect");
		StartEffect(pEffect);
	}

	void SkillAven::Exit()
	{
		SkillState::Exit();
	}

	void SkillAven::activeskill_aven()
	{
		Player* pPlayer = GetPlayer();
		m_bStart = true;
		pPlayer->SetAnimStop(false);

		if (pPlayer->IsShadow())
		{
			pPlayer->GetShadow()->Set_Attack(std::bind(&SkillAven::create_aven,this));
		}
		create_aven();
	}
	void SkillAven::create_aven()
	{
		UINT iCall = 1;
		Player* pPlayer = GetPlayer();
		if (pPlayer->IsShadow())
			iCall *= 2;

		int iDir = pPlayer->GetDir();
		PlayerAttackObject* pAttackObj = pPlayer->GetScript<PlayerScript>()->GetPlayerSkill(L"Aven");

		Aven* pAven = dynamic_cast<Aven*>(pAttackObj);
		//pAven->GetComponent<Collider2D>()->SetActive(true);
		pAven->SetDir(iDir);
		//추가 데미지
		//AddDamage(pAven);

		AttackScript* pScript = pAven->GetScript<AttackScript>();
		pScript->SetDeleteObject(false);

		tAttackInfo& tAttack = pScript->GetAttackInfo();
		tAttack.iDamageCount = iCall;
		tAttack.fAttackDamage = 1.f;

		tAttack.fAttRcnt = 0.7f;
		tAttack.fAttRigidityTime = 0.3f;
		tAttack.fAttUpperRcnt = 0.f;

		bool bAcc = pPlayer->GetScript<PlayerScript>()->IsAccAttack();
		if (bAcc)
			pScript->SetAccAttack();//추가 공격

		Transform* pTr = pAven->GetComponent<Transform>();
		Vector3 vPosition = GetPlayer()->GetComponent<Transform>()->GetPosition();
		vPosition.y -= 0.2f;
		vPosition.x += (0.4f * iDir);
		pTr->SetPosition(vPosition);

		EventManager::CreateObject(pAven, eLayerType::AttackObject);
	}
}