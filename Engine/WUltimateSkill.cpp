#include "WUltimateSkill.h"
#include "WResources.h"
#include "WEffect.h"
#include "WAttackScript.h"
#include "WPlayerAttackObject.h"
#include "WPlayer.h"
#include "WPlayerScript.h"
#include "WEventManager.h"
#include "WBattleManager.h"
#include "WLight.h"
#include "WUltimateFog.h"
#include "WUltimateBackground.h"
#include "WSpawnUltimate.h"
#include "WUltimateShuriken.h"
#include "WRenderer.h"
#include "WEventManager.h"
#include "WUltimateObject.h"
namespace W
{
	SkillUltimate::SkillUltimate():
		m_pUltimateSkill(nullptr)
	{
		SetSkillType(Player::ePlayerSkill::ultimate);
		SetStateName(L"_alert");

		tSkillTime tTime = {};
		tTime.fCoolTime = 50.f;
		tTime.fCurTime = 0.f;
		SetCoolTime(tTime);

		Resources::Load<Texture>(L"ultimate0", L"..\\Resources\\Texture\\Player\\skill\\ultimate\\ultimate0.png");
		Resources::Load<Texture>(L"UltiShuriken", L"..\\Resources\\Texture\\Player\\skill\\ultimate\\s1.png");
		m_pHitEffectAtlas = Resources::Load<Texture>(L"ultimate_hit", L"..\\Resources\\Texture\\Player\\skill\\ultimate\\hit.png");
		for (int i = 0; i < 30; ++i)
		{
			Effect* pEffect = CreateEffet(m_pHitEffectAtlas, L"ultimate_suriken", Vector2(0.f, 0.f), Vector2(219.f, 209.f), 8, 1,
				Vector2(250.f, 250.f), Vector2(0.f, 0.f), 0.1f);
			pEffect->GetComponent<Transform>()->SetScale(2.5f, 2.5f, 0.f);
		}

		SetSound(Resources::Load<AudioClip>(L"ultisound", L"..\\Resources\\sound\\skill\\UltiUse.mp3"), false);
		Resources::Load<AudioClip>(L"UltiHit", L"..\\Resources\\sound\\skill\\UltiHit.mp3");
		Resources::Load<AudioClip>(L"UltiShurikenHit", L"..\\Resources\\sound\\skill\\UltiShurikenHit.mp3");

	}
	SkillUltimate::~SkillUltimate()
	{

	}
	void SkillUltimate::Update()
	{
		int iCurFrame = m_pUltimateSkill->GetCurFrame();
		if (iCurFrame >= m_pUltimateSkill->GetAttackFrame())
			m_bCreate = true;

		if (m_bCreate)
		{
			create_shuriken();
			Exit();
		}
	}
	void SkillUltimate::Initialize()
	{
		PlayerScript* pScript = GetPlayer()->GetScript<PlayerScript>();
		//처음 공격
		m_pUltimateSkill = new UltimateObject();
		m_pUltimateSkill->SetName(L"ultimate0");
		m_pUltimateSkill->SetPlayer(GetPlayer());
		m_pUltimateSkill->AddComponent<Collider2D>();
		pScript->AddPlayerSkill(m_pUltimateSkill);


		//이미지들
		UltimateBackground* pBackGround = new UltimateBackground();
		pBackGround->SetName(L"ultimate1");
		pBackGround->SetPlayer(GetPlayer());
		pScript->AddPlayerSkill(pBackGround);

		UltimateFog* pFog = new UltimateFog();
		pFog->SetPlayer(GetPlayer());
		pFog->SetName(L"ultimate2");
		pScript->AddPlayerSkill(pFog);

		SpawnUltimate* spawn = new SpawnUltimate();
		spawn->SetPlayer(GetPlayer());
		spawn->SetName(L"ultimate_spawn");
		pScript->AddPlayerSkill(spawn);
		//방향 설정
		
		
		for (int i = 0; i < 25; ++i)
		{
			UltimateShuriken* pShuriken = new UltimateShuriken();
			pShuriken->SetPlayer(GetPlayer());
			pShuriken->SetName(L"ultimate_suriken");
			pShuriken->Initialize();
			pScript->AddPlayerSkill(pShuriken);

			const tAttackInfo& Attack = GetPlayer()->GetScript<PlayerScript>()->GetAttackInfo();

			tAttackInfo AttackInfo;
			AttackInfo.fAttackDamage = 2.f;
			AttackInfo.fAttack = Attack.fAttack;
			AttackInfo.fDex = Attack.fDex;

			AttackInfo.fAttRcnt = 0.3f;
			AttackInfo.fAttRigidityTime = 0.3f;
			AttackInfo.fAttUpperRcnt = 0.f;

			//7번 공격
			AttackInfo.iDamageCount = 3;

			pShuriken->GetScript<AttackScript>()->SetAttackInfo(AttackInfo);
		}
	}
	void SkillUltimate::Enter()
	{
		if (GetPlayer()->GetCurPlayerState() == Player::ePlayerState::ladder)
		{
			Exit();
			return;
		}
		SkillState::Enter();
	
		m_bCreate = false;
		
		activeskill_ultimate();
		//StartEffect(pEffect);
	}
	void SkillUltimate::Exit()
	{
		SkillState::Exit();
	}
	void SkillUltimate::activeskill_ultimate()
	{
		PlayerAttackObject* pAttackObj = GetPlayer()->GetScript<PlayerScript>()->GetPlayerSkill(L"ultimate0");
		pAttackObj->GetComponent<Collider2D>()->SetActive(false);
		pAttackObj->GetScript<AttackScript>()->SetDeleteObject(false);
		pAttackObj->Initialize();

		const tAttackInfo& Attack = GetPlayer()->GetScript<PlayerScript>()->GetAttackInfo();

		tAttackInfo AttackInfo;
		AttackInfo.fAttackDamage = 2.f;
		AttackInfo.fAttack = Attack.fAttack;
		AttackInfo.fDex = Attack.fDex;

		AttackInfo.fAttRcnt = 0.3f;
		AttackInfo.fAttRigidityTime = 0.3f;
		AttackInfo.fAttUpperRcnt = 0.f;
		//7번 공격
		AttackInfo.iDamageCount = 7;

		pAttackObj->GetScript<AttackScript>()->SetAttackInfo(AttackInfo);
		EventManager::CreateObject(pAttackObj, eLayerType::AttackObject);

	}
	void SkillUltimate::create_shuriken()
	{
		PlayerAttackObject* pAttackObj = GetPlayer()->GetScript<PlayerScript>()->GetPlayerSkill(L"ultimate_spawn");
		SpawnUltimate* pSpawn = dynamic_cast<SpawnUltimate*>(pAttackObj);
		pSpawn->Initialize();
		EventManager::CreateObject(pSpawn, eLayerType::AttackObject);

		Vector3 vCamPos = renderer::MainCamera->GetOwner()->GetComponent<Transform>()->GetPosition();
		Transform* pTr = pSpawn->GetComponent<Transform>();
		pTr->SetPosition(Vector3(vCamPos.x, vCamPos.y, -4.f));
	}
}