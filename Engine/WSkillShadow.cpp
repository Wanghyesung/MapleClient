#include "WSkillShadow.h"
#include "WResources.h"
#include "WEffect.h"
#include "WShadow.h"
#include "WEventManager.h"
#include "WPlayerScript.h"
#include "WBattleManager.h"
namespace W
{
	SkillShadow::SkillShadow():
		m_bCreate(false)
	{
		SetSkillType(Player::ePlayerSkill::shadow);
		//SetStateName(L"_stand");

		tSkillTime tTime = {};
		tTime.fCoolTime = 20.f;
		tTime.fCurTime = 0.f;
		SetCoolTime(tTime);
		
		Resources::Load<Texture>(L"shadowe1ffect", L"..\\Resources\\Texture\\Player\\skill\\effect5.png");
		Effect* pEffect = CreateEffet(Resources::Find<Texture>(L"shadowe1ffect"),L"shadowe1ffect", Vector2(0.f, 0.f), Vector2(158.f, 131.f), 11, 1,
			Vector2(150.f, 150.f), Vector2(-0.6f, 0.2f), 0.1f);
		pEffect->SetFunction(std::bind(&SkillShadow::activeskill_shadow, this), 10);


		m_pEffectAtlas = Resources::Load<Texture>(L"shadowe2ffect", L"..\\Resources\\Texture\\Player\\skill\\effect6.png");
		pEffect = CreateEffet(m_pEffectAtlas, L"shadowe2ffect",Vector2(0.f, 0.f), Vector2(195.f, 180.f), 16, 1,
			Vector2(200.f, 200.f), Vector2(-0.4f, 0.2f), 0.1f);
		pEffect->SetFunction(std::bind(&SkillShadow::create_shadow, this), 4);
		pEffect->GetComponent<Transform>()->SetScale(2.2f, 2.2f, 0.f);

		SetSound(Resources::Load<AudioClip>(L"shadowsound", L"..\\Resources\\sound\\skill\\shadow.mp3"), false);

	}

	SkillShadow::~SkillShadow()
	{

	}

	void SkillShadow::Enter()
	{
		SkillState::Enter();

		Player* pPlayer = GetPlayer();
		if (pPlayer->GetCurPlayerState() != Player::ePlayerState::ladder)
			pPlayer->SetCurStateName(L"_stand");
		//if (GetPlayer()->GetCurPlayerState() == Player::ePlayerState::ladder)
		//{
		//	Exit();
		//	return;
		//}

		m_bCreate = false;

		Effect* pEffect = BattleManager::GetEffect(L"shadowe2ffect");
		StartEffect(pEffect);
	}

	void SkillShadow::Exit()
	{
		SkillState::Exit();
	}

	void SkillShadow::Update()
	{
		if (m_bCreate)
			Exit();
	}

	void SkillShadow::Initialize()
	{

	}

	void SkillShadow::activeskill_shadow()
	{
		m_bCreate = true;

		Shadow* pShadow = GetPlayer()->GetShadow();
		pShadow->set_owner(GetPlayer());

		float fCoolTime = GetCoolTime().fCoolTime;
		pShadow->set_active(fCoolTime);
		GetPlayer()->SetShadow(true);
	}

	void SkillShadow::create_shadow()
	{
		Effect* pEffect = BattleManager::GetEffect(L"shadowe1ffect");
		StartEffect(pEffect);

		Vector3 vPos = pEffect->GetComponent<Transform>()->GetPosition();
		vPos.z -= 0.2f;
		pEffect->GetComponent<Transform>()->SetPosition(vPos);
	}
}