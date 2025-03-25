#include "WSkillWind.h"
#include "WBattleManager.h"
#include "WResources.h"
#include "WWind.h"
#include "WAttackScript.h"
#include "WEventManager.h"
#include "WPlayerScript.h"
namespace W
{
	SkillWind::SkillWind():
		m_pWind(nullptr)
	{
		SetSkillType(Player::ePlayerSkill::wind);
		SetStateName(L"_swingOF");

		tSkillTime tTime = {};
		tTime.fCoolTime = 6.f;
		tTime.fCurTime = 0.f;
		SetCoolTime(tTime);

		m_pEffectAtlas = Resources::Load<Texture>(L"windffect1", L"..\\Resources\\Texture\\Player\\skill\\shuriken\\effect_0.png");
		Effect* pEffect = CreateEffet(m_pEffectAtlas, L"windffect1", Vector2(0.f, 0.5f), Vector2(626.f, 508.f), 7, 1,
			Vector2(600.f, 600.f), Vector2(0.5f, 0.f), 0.06f);

		Resources::Load<Texture>(L"windffect2", L"..\\Resources\\Texture\\Player\\skill\\shuriken\\effect_1.png");
		pEffect = CreateEffet(Resources::Find<Texture>(L"windffect2"), L"windffect2", Vector2(0.f, 0.f), 
			Vector2(572.f, 413.f), 11, 1, Vector2(580.f, 580.f), Vector2(0.5f, 0.5f), 0.06f);
		pEffect->SetFunction(std::bind(&SkillWind::activeskill_wind, this), 6);


		m_pHitEffectAtlas = Resources::Load<Texture>(L"wind", L"..\\Resources\\Texture\\Player\\skill\\shuriken\\hit.png");
		for (int i = 0; i < 7; ++i)
		{
			pEffect = CreateEffet(m_pHitEffectAtlas, L"wind", Vector2(0.f, 0.f), Vector2(249.f, 248.f), 6, 1,
				Vector2(250.f, 250.f), Vector2(0.f, 0.2f), 0.15f);
			pEffect->GetComponent<Transform>()->SetScale(2.5f, 2.5f, 0.f);
		}

		std::shared_ptr<Texture> pAtlas
			= Resources::Load<Texture>(L"windTex", L"..\\Resources\\Texture\\Player\\skill\\shuriken\\windshuriken.png");

		SetSound(Resources::Load<AudioClip>(L"windsound", L"..\\Resources\\sound\\skill\\wind.mp3"), false);
		Resources::Load<AudioClip>(L"wind_move", L"..\\Resources\\sound\\skill\\wind_loop.mp3");
		Resources::Load<AudioClip>(L"wind_finish", L"..\\Resources\\sound\\skill\\wind_dead.mp3");
		Resources::Load<AudioClip>(L"wind_hit", L"..\\Resources\\sound\\skill\\wind_hit.mp3");

	}
	SkillWind::~SkillWind()
	{

	}
	void SkillWind::Update()
	{
		if (m_bStart)
			Exit();
	}
	void SkillWind::Initialize()
	{
		PlayerScript* pScript = GetPlayer()->GetScript<PlayerScript>();
		for (int i = 0; i < 2; ++i)
		{
			Wind* pWind = new Wind();
			pWind->Initialize();
			pWind->SetName(L"wind");
			pWind->SetPlayer(GetPlayer());
			pScript->AddPlayerSkill(pWind);
		}
	}
	void SkillWind::Enter()
	{

		if (GetPlayer()->GetCurPlayerState() == Player::ePlayerState::ladder)
		{
			Exit();
			return;
		}

		SkillState::Enter();
	
		m_bStart = false;

		Effect* pEffect = BattleManager::GetEffect(L"windffect2");
		pEffect->GetComponent<Transform>()->SetScale(6.f, 6.f, 0.f);
		StartEffect(pEffect);
	}
	void SkillWind::Exit()
	{
		SkillState::Exit();
	}
	void SkillWind::activeskill_wind()
	{
		Effect* pEffect = BattleManager::GetEffect(L"windffect1");
		pEffect->GetComponent<Transform>()->SetScale(6.f, 6.f, 0.f);
		pEffect->SetFunction(std::bind(&SkillWind::create_wind, this), 6);
		StartEffect(pEffect);
	}

	void SkillWind::create_wind()
	{
		m_bStart = true;

		int iDir = GetPlayer()->GetDir();
		PlayerAttackObject* pAttackObj = GetPlayer()->GetScript<PlayerScript>()->GetPlayerSkill(L"wind");
		m_pWind = dynamic_cast<Wind*>(pAttackObj);
		m_pWind->GetScript<AttackScript>()->SetDeleteObject(false);
		m_pWind->SetDir(iDir);
		
		//추가 데미지
		//AddDamage(m_bWind);

		tAttackInfo& tAttack = m_pWind->GetScript<AttackScript>()->GetAttackInfo();
		tAttack.iDamageCount = 5;
		tAttack.fAttackDamage = 1.f;

		tAttack.fAttRcnt = 0.7f;
		tAttack.fAttRigidityTime = 0.3f;
		tAttack.fAttUpperRcnt = 0.f;


		Transform* pTr = m_pWind->GetComponent<Transform>();
		Vector3 vPosition = GetPlayer()->GetComponent<Transform>()->GetPosition();
		vPosition.y -= 0.2f;
		vPosition.x += (0.4f * iDir);
		pTr->SetPosition(vPosition);

		EventManager::CreateObject(m_pWind, eLayerType::AttackObject);
	}
}