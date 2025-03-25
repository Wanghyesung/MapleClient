#include "WSkillSpeed.h"
#include "WResources.h"
#include "WPlayerScript.h"
#include "WEffect.h"
#include "WSceneManger.h"
#include "WBattleManager.h"
namespace W
{
	SkillSpeed::SkillSpeed()
	{
		SetSkillType(Player::ePlayerSkill::speed);
		

		tSkillTime tTime = {};
		tTime.fCoolTime = 10.f;
		tTime.fCurTime = 0.f;
		tTime.fActiveTime = 1.f;
		tTime.fCurTime = 0.f;
		SetCoolTime(tTime);

		m_pEffectAtlas = Resources::Load<Texture>(L"speedffect", L"..\\Resources\\Texture\\Player\\skill\\effect3.png");
		Effect* pEffect = CreateEffet(m_pEffectAtlas, L"speedffect", Vector2(0.f, 0.f), Vector2(122.f, 64.f), 9, 1,
			Vector2(200.f, 200.f), Vector2(0.f, 0.0f), tTime.fActiveTime / 9.f);
		pEffect->GetComponent<Transform>()->SetScale(2.f, 2.f, 0.f);

		SetSound(Resources::Load<AudioClip>(L"speedskillsound", L"..\\Resources\\sound\\skill\\speed.mp3"), false);

		
	}
	SkillSpeed::~SkillSpeed()
	{

	}
	void SkillSpeed::Enter()
	{
		SkillState::Enter();

		Player* pPlayer = GetPlayer();
		if (pPlayer->GetCurPlayerState() != Player::ePlayerState::ladder)
			pPlayer->SetCurStateName(L"_stand");

		Effect* pEffect = BattleManager::GetEffect(L"speedffect");
		StartEffect(pEffect);
		BattleManager::Buff_Stat(GetPlayer(), BattleManager::eUpStatType::Speed, 1.f);

	}
	void SkillSpeed::Exit()
	{
		SkillState::Exit();
	}
	void SkillSpeed::Update()
	{
		SkillState::Update();

		tSkillTime tTime = GetCoolTime();

		if (tTime.fCurActiveTime >= tTime.fActiveTime)
		{
			activeskill_jump();
			Exit();
		}

	}
	void SkillSpeed::Initialize()
	{

	}
	void SkillSpeed::activeskill_jump()
	{
		//GetPlayer()->GetScript<PlayerScript>()->
	}
}