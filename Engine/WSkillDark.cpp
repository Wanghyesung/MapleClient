#include "WSkillDark.h"
#include "WResources.h"
#include "WEffect.h"
#include "WTime.h"
#include "WSceneManger.h"
#include "WBattleManager.h"

//gs에서 정점을 바꾸고 ps로 전달
//정점 정보를 하나만 가지고 gs에서 정점을 늘리고 ps로 넘기기

namespace W
{
	SkillDark::SkillDark()
	{
		SetSkillType(Player::ePlayerSkill::dark);

		tSkillTime tTime = {};
		tTime.fCoolTime = 0.f;
		tTime.fCurTime = 0.f;
		tTime.fActiveTime = 1.5f;
		tTime.fCurTime = 0.f;

		SetCoolTime(tTime);

		m_pEffectAtlas = Resources::Load<Texture>(L"darkffect", L"..\\Resources\\Texture\\Player\\skill\\effect1.png");

		Effect* pEffect = CreateEffet(m_pEffectAtlas, L"darkffect", Vector2(0.f, 0.f), Vector2(126.f, 129.f), 8, 1,
			Vector2(110.f, 110.f), Vector2(-0.15f, 0.1f), tTime.fActiveTime / 8.f);

		SetSound(Resources::Load<AudioClip>(L"darksound", L"..\\Resources\\sound\\skill\\dark.mp3"), false);
	}

	SkillDark::~SkillDark()
	{

	}

	void SkillDark::Enter()
	{
		SkillState::Enter();

		Player* pPlayer = GetPlayer();
		if(pPlayer->GetCurPlayerState() != Player::ePlayerState::ladder)
			pPlayer->SetCurStateName(L"_stand");

		//if(GetPlayer()->IsAlert())
		//	GetPlayer()->SetCurStateName(L"_alert");
		//else
		//	GetPlayer()->SetCurStateName(L"_stand");
		
		Effect* pEffect =BattleManager::GetEffect(L"darkffect");
		StartEffect(pEffect);
	}

	void SkillDark::Exit()
	{
		SkillState::Exit();
	}

	void SkillDark::Update()
	{
		SkillState::Update();
		//캐스팅
		tSkillTime tTime = GetCoolTime();

		if (tTime.fCurActiveTime >= tTime.fActiveTime)
		{
			GetPlayer()->SetDark(true);
			Exit();
		}
	}

	void SkillDark::Initialize()
	{

	}
}