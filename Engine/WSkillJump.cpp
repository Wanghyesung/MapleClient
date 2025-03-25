#include "WSkillJump.h"
#include "WResources.h"
#include "WEffect.h"
#include "WRigidbody.h"
#include "WPlayerScript.h"
#include "WSkillManager.h"
#include "WSceneManger.h"
#include "WBattleManager.h"
#include "WEventManager.h"
namespace W
{
	SkillJump::SkillJump()
	{
		SetSkillType(Player::ePlayerSkill::jump);
		SetStateName(L"_jump");

		tSkillTime tTime = {};
		tTime.fCoolTime = 7.f;
		tTime.fCurTime = 0.f;
		SetCoolTime(tTime);

		m_pEffectAtlas = Resources::Load<Texture>(L"jumpeffect", L"..\\Resources\\Texture\\Player\\skill\\effect2.png");
		Effect* pEffect = CreateEffet(m_pEffectAtlas, L"jumpeffect", Vector2(0.f, 0.f), Vector2(235.5f, 133.f), 8, 1,
			Vector2(200.f, 200.f), Vector2(-1.f, 0.0f), 0.1f);
		pEffect->GetComponent<Transform>()->SetScale(2.f, 2.f, 0.f);

		SetSound(Resources::Load<AudioClip>(L"fjumpsound", L"..\\Resources\\sound\\skill\\fjump.mp3"), false);

	}
	SkillJump::~SkillJump()
	{

	}

	void SkillJump::Enter()
	{
		//skillState::enter
		GetPlayer()->GetScript<PlayerScript>()->SetActiveState(Player::ePlayerState::jump);

		Player* pPlayer = GetPlayer();
		Rigidbody* pRigidbody = pPlayer->GetComponent<Rigidbody>();
		if (pRigidbody->IsGround())
		{
			Exit();
			return;
		}
		
		Effect* pEffect =BattleManager::GetEffect(L"jumpeffect");
		StartEffect(pEffect);

		pRigidbody->SetVelocity(Vector2(pPlayer->GetDir() * 4.f, 3.5f));

		//skillState::exit
		EventManager::ChangePlayerSkillState(Player::ePlayerSkill::end);
		//SkillManager::SetActiveSkill(Player::ePlayerSkill::end);

		StartSound();
	}

	void SkillJump::Exit()
	{
		SkillState::Exit();
	}

	void SkillJump::Update()
	{

	}

	void SkillJump::Initialize()
	{

	}

	void SkillJump::activeskill_jump()
	{

	}
}