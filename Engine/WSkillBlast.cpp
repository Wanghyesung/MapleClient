#include "WSkillBlast.h"
#include "WResources.h"
#include "WBattleManager.h"
#include "WAttackScript.h"
#include "WBlast.h"
#include "WEventManager.h"
#include "WSkillManager.h"
#include "WPlayerScript.h"
namespace W
{
	SkillBlast::SkillBlast()
	{
		SetSkillType(Player::ePlayerSkill::blast);
		SetStateName(L"_swingOF");

		tSkillTime tTime = {};
		tTime.fCoolTime = 5.f;
		tTime.fCurTime = 0.f;
		SetCoolTime(tTime);

		m_pEffectAtlas = Resources::Load<Texture>(L"blastffect1", L"..\\Resources\\Texture\\Player\\skill\\blast\\effect_0.png");
		Effect* pEffect = CreateEffet(m_pEffectAtlas, L"blastffect1", Vector2(0.f, 0.f),
			Vector2(752.f, 358.f), 13, 1, Vector2(750.f, 750.f), Vector2(0.f, 0.f), 0.1f);
		pEffect->GetComponent<Transform>()->SetScale(5.f, 5.f, 0.f);
		pEffect->SetFunction(std::bind(&SkillBlast::activeskill_blast, this), 7);

		Resources::Load<Texture>(L"blastffect2", L"..\\Resources\\Texture\\Player\\skill\\blast\\effect_1.png");
		pEffect = CreateEffet(Resources::Find<Texture>(L"blastffect2"), L"blastffect2", Vector2(0.f, 0.f),
			Vector2(735.f, 673.f), 9, 1, Vector2(750.f, 750.f), Vector2(0.f, 0.f), 0.1f);
		pEffect->GetComponent<Transform>()->SetScale(5.f, 5.f, 0.f);
		pEffect->SetFunction(std::bind(&SkillBlast::exit, this), 8);

		for (int i = 0; i < 25; ++i)
		{
			m_pHitEffectAtlas = Resources::Load<Texture>(L"blast", L"..\\Resources\\Texture\\Player\\skill\\blast\\hit.png");
			pEffect = CreateEffet(m_pHitEffectAtlas, L"blast", Vector2(0.f, 0.f),
				Vector2(285.f, 284.f), 8, 1, Vector2(300.f, 300.f), Vector2(0.f, 0.f), 0.1f);
		}

		std::shared_ptr<Texture> pAtlas
			= Resources::Load<Texture>(L"blastTex", L"..\\Resources\\Texture\\Player\\skill\\blast\\effect_2.png");

		SetSound(Resources::Load<AudioClip>(L"blastsound", L"..\\Resources\\sound\\skill\\blast.mp3"), false);
		Resources::Load<AudioClip>(L"blasthit", L"..\\Resources\\sound\\skill\\blast1.mp3");

	}
	SkillBlast::~SkillBlast()
	{

	}
	void SkillBlast::Update()
	{
		if (m_bCreate)
			Exit();
	}
	void SkillBlast::Initialize()
	{
		PlayerScript* pScript = GetPlayer()->GetScript<PlayerScript>();
		for (int i = 0; i < 10; ++i)
		{
			Blast* pBlast = new Blast();
			pBlast->Initialize();
			pBlast->SetName(L"blast");
			pBlast->SetPlayer(GetPlayer());
			pScript->AddPlayerSkill(pBlast);
		}
	}
	void SkillBlast::Enter()
	{

		if (GetPlayer()->GetCurPlayerState() == Player::ePlayerState::ladder)
		{
			Exit();
			return;
		}
		SkillState::Enter();

		m_bCreate = false;

		Effect* pEffect = BattleManager::GetEffect(L"blastffect1");
		StartEffect(pEffect);
	}
	void SkillBlast::Exit()
	{
		SkillState::Exit();
	}

	void SkillBlast::activeskill_blast()
	{
		Effect* pEffect = BattleManager::GetEffect(L"blastffect2");
		StartEffect(pEffect);
	}

	void SkillBlast::create_blast(const math::Vector3& _vPosition)
	{
		int iDir = GetPlayer()->GetDir();
		PlayerAttackObject* pAttackObj = GetPlayer()->GetScript<PlayerScript>()->GetPlayerSkill(L"blast");
		Blast* pBlast = dynamic_cast<Blast*>(pAttackObj);
		pBlast->SetDir(iDir);

		pBlast->GetScript<AttackScript>()->SetDeleteObject(false);
		//AddDamage(m_bWind);
		tAttackInfo& tAttack = pBlast->GetScript<AttackScript>()->GetAttackInfo();
		tAttack.iDamageCount = 5;
		tAttack.fAttackDamage = 1.f;

		tAttack.fAttRcnt = 0.7f;
		tAttack.fAttRigidityTime = 0.3f;
		tAttack.fAttUpperRcnt = 0.f;

		pBlast->GetComponent<Transform>()->SetPosition(_vPosition);

		EventManager::CreateObject(pBlast, eLayerType::AttackObject);
	}

	void SkillBlast::exit()
	{
		GetPlayer()->GetScript<PlayerScript>()->SetAccAttack();
		m_bCreate = true;
	}
}