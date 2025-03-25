#include "WSkillLoad.h"
#include "WBattleManager.h"
#include "WResources.h"
#include "WLoad.h"
#include "WEventManager.h"
#include "WPlayerScript.h"
#include "WAutoShuriken.h"
namespace W
{
	SkillLoad::SkillLoad():
		m_bCreate(false)
	{
		SetSkillType(Player::ePlayerSkill::load);
		SetStateName(L"_swingOF");

		tSkillTime tTime = {};
		tTime.fCoolTime = 6.f;
		tTime.fCurTime = 0.f;
		SetCoolTime(tTime);

		m_pEffectAtlas = Resources::Load<Texture>(L"loadeffect", L"..\\Resources\\Texture\\Player\\skill\\load\\start.png");
		Effect* pEffect = CreateEffet(m_pEffectAtlas, L"loadeffect", Vector2(0.f, 0.5f), Vector2(1700.f, 1200.f), 5, 3,
			Vector2(1700.f, 1200.f), Vector2(0.5f, 3.f), 0.06f);
		pEffect->GetComponent<Transform>()->SetScale(10.f, 10.f, 0.f);

		m_pHitEffectAtlas = Resources::Load<Texture>(L"load", L"..\\Resources\\Texture\\Player\\skill\\load\\hit.png");
		for (int i = 0; i < 30; ++i)
		{
			pEffect = CreateEffet(m_pHitEffectAtlas, L"load", Vector2(0.f, 0.f), Vector2(315.f, 204.f), 14, 1,
				Vector2(300.f, 300.f), Vector2(0.f, 0.f), 0.07f);
			pEffect->GetComponent<Transform>()->SetScale(3.f, 3.f, 0.f);
		}

		std::shared_ptr<Texture> pAtlas
			= Resources::Load<Texture>(L"loadTex", L"..\\Resources\\Texture\\Player\\skill\\load\\load.png");

		SetSound(Resources::Load<AudioClip>(L"loadsound", L"..\\Resources\\sound\\skill\\load.mp3"), false);
		Resources::Load<AudioClip>(L"load_loop", L"..\\Resources\\sound\\skill\\load_loop.mp3");
		Resources::Load<AudioClip>(L"load_dead", L"..\\Resources\\sound\\skill\\load_dead.mp3");
		Resources::Load<AudioClip>(L"load_hit", L"..\\Resources\\sound\\skill\\load_hit2.mp3");
	}							

	SkillLoad::~SkillLoad()
	{

	}

	void SkillLoad::Update()
	{
		if (m_bCreate)
			Exit();
	}

	void SkillLoad::Initialize()
	{
		PlayerScript* pScript = GetPlayer()->GetScript<PlayerScript>();
		for (int i = 0; i < 2; ++i)
		{
			Load* pLoad = new Load();
			pLoad->SetPlayer(GetPlayer());
			pLoad->Initialize();
			pLoad->SetName(L"load");
			pScript->AddPlayerSkill(pLoad);
		}

		for (int i = 0; i < 50; ++i)
		{
			AutoShuriken* pShuriken = new AutoShuriken();
			pShuriken->SetPlayer(GetPlayer());
			pShuriken->Initialize();
			pShuriken->SetName(L"autoSuriken");
			pScript->AddPlayerSkill(pShuriken);
		}
	}

	void SkillLoad::Enter()
	{

		if (GetPlayer()->GetCurPlayerState() == Player::ePlayerState::ladder)
		{
			Exit();
			return;
		}
		SkillState::Enter();

		m_bCreate = false;

		Effect* pEffect = BattleManager::GetEffect(L"loadeffect");
		StartEffect(pEffect);
		pEffect->SetFunction(std::bind(&SkillLoad::activeskill_load, this), 13);
	}

	void SkillLoad::Exit()
	{
		SkillState::Exit();
	}

	void SkillLoad::activeskill_load()
	{
		m_bCreate = true;

		create_load();
	}
	void SkillLoad::create_load()
	{
		PlayerAttackObject* pAttackObj = GetPlayer()->GetScript<PlayerScript>()->GetPlayerSkill(L"load");
		pAttackObj->GetComponent<Collider2D>()->SetActive(false);

		Load* pLoad = dynamic_cast<Load*>(pAttackObj);
		pLoad->Start();

		Transform* pTr = pLoad->GetComponent<Transform>();
		Vector3 vPos = GetPlayer()->GetComponent<Transform>()->GetPosition();
		vPos.y += 3.f;
		pTr->SetPosition(vPos);
		EventManager::CreateObject(pLoad, eLayerType::AttackObject);
	}
}