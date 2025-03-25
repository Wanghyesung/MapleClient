#include "WBattleManager.h"
#include "WResources.h"
#include "WSceneManger.h"
#include "WTime.h"
#include "WEventManager.h"
#include "WPlayerScript.h"
#include "WSkillManager.h"
#include "WObject.h"
#include "WTemptation.h"
#include "WMonsterScript.h"
#include "WMonster.h"
#include "WAttackUp.h"
#include "WDefenseUp.h"
#include "WSealSkill.h"
#include "WFaint.h"
#include "WIgnore.h"
#include "WAnimator.h"
#include "WReflex.h"
#include "WConfusion.h"
#include "WVariation.h"
#include "WSlow.h"
#include "WUndead.h"
#include "WGroggy.h"
#include "WStigma.h"
#include "WInputBackground.h"
#include "WDemianEntireAttack.h"
#include "WStop.h"
#define DamageMap std::map<std::wstring, BattleManager::tDamageCount>
#define EffectMap std::map<std::wstring, std::queue<Effect*>> 
namespace W
{
	std::queue<DamageFont*> BattleManager::m_queueFonts = {};

	EffectMap BattleManager::m_mapEffects = {};
	DamageMap BattleManager::m_mapDamage = {};
	UINT BattleManager::m_iMaxDamage = 9999999;
	bool BattleManager::m_bOnAbnormal = false;
	bool BattleManager::m_bOnUndead = false;
	float BattleManager::m_fPotionTime = 0.1f;
	float BattleManager::m_fCurPotionTime = 0.f;
	UINT BattleManager::m_iStigmaCount = 6;

	void BattleManager::Initialize()
	{
		std::shared_ptr<Material> pMater = std::make_shared<Material>();
		pMater->SetShader(Resources::Find<Shader>(L"ObjectShader"));
		pMater->SetRenderinMode(eRenderingMode::Transparent);
		Resources::Insert(L"DamageMater", pMater);

		for (int i = 0; i < 10; ++i)
		{
			std::wstring strNum = std::to_wstring(i);
		
			std::shared_ptr<Texture> spTex =
				Resources::Load<Texture>(L"Number_" + strNum, L"..\\Resources\\Texture\\Damage\\" + strNum + L".png");
		}
		
		for (int i = 0; i < 300; ++i)
		{
			DamageFont* pDamageFont = new DamageFont();
			m_queueFonts.push(pDamageFont);
		}

	}

	void BattleManager::Release()
	{
		while (!m_queueFonts.empty())
		{
			DamageFont* pDamageFont = m_queueFonts.front();
			m_queueFonts.pop();

			delete pDamageFont;
			pDamageFont = nullptr;
		}

		EffectMap::iterator iter = m_mapEffects.begin();
		for (iter; iter != m_mapEffects.end(); ++iter)
		{
			std::queue<Effect*> queuEffect = iter->second;
			
			while (!queuEffect.empty())
			{
				Effect* pEffect = queuEffect.front();
				queuEffect.pop();

				delete pEffect;
				pEffect = nullptr;
			}
		}
	}

	void BattleManager::Update()
	{
		DamageMap::iterator iter;

		//
		for (iter = m_mapDamage.begin(); iter != m_mapDamage.end(); )
		{
			iter->second.m_fCurTime += Time::DeltaTime();
		
			if (iter->second.m_fCurTime >= iter->second.iEndCount)
			{
				iter = m_mapDamage.erase(iter);
			}
			else
				++iter;
		}

		if(m_fCurPotionTime< m_fPotionTime)
			m_fCurPotionTime += Time::DeltaTime();

	}

	void BattleManager::CheckDamage(tObjectInfo& _tObjectInfo, const tAttackInfo& _tAttackInfo,
		const std::wstring _strName, Vector3 _vPosition)
	{
		std::queue<DamageFont*> finalQueue = {};
		int iFinalDamage = 0;

		iFinalDamage = floor(_tAttackInfo.fAttackDamage * 10
			- _tObjectInfo.fDefense * _tObjectInfo.fDefense);

		if (iFinalDamage <= 0.f)
			iFinalDamage = 1.f;

		else if (iFinalDamage >= m_iMaxDamage)
			iFinalDamage = m_iMaxDamage;

		_tObjectInfo.fHP -= iFinalDamage;
		if (_tObjectInfo.fHP <= 0.f)
			_tObjectInfo.fHP = 0.f;

		UINT iMinus = m_iMaxDamage + 1;
		
		while (iMinus > 0)
		{
			UINT num = iFinalDamage / iMinus;
			if (num > 0)
			{
				DamageFont* pFont = m_queueFonts.front();
				m_queueFonts.pop();

				pFont->CheckDamage(num);
				pFont->GetComponent<Transform>()->SetPosition(_vPosition);
				finalQueue.push(pFont);
				iFinalDamage %= iMinus;
			}
			iMinus /= 10;
		}

		render_damage(finalQueue, _tAttackInfo.iDamageCount, _strName);
	}

	void BattleManager::render_damage(std::queue<DamageFont*> _queueFonts, UINT _iDamageCount, const std::wstring& _strName)
	{
		//같은공격이면 그 위에 렌더링
		tDamageCount tDamage = add_damage(_iDamageCount, _strName);

		float fOffsetX = -0.25f;
		UINT iQueueSize = _queueFonts.size();
		iQueueSize /= 2;

		float X = iQueueSize * fOffsetX;
		
		while (!_queueFonts.empty())
		{
			DamageFont* pDamage = _queueFonts.front();
			_queueFonts.pop();

			Transform* pTr = pDamage->GetComponent<Transform>();
			Vector3 vPos = pTr->GetPosition();
			vPos.x += X;
			vPos.z = -6.f;
			vPos.y += (0.3f * tDamage.iCurCount);
			pTr->SetPosition(vPos);

			pDamage->m_bActive = true;
			SceneManger::AddGameObject(eLayerType::Effect, pDamage);

			X -= fOffsetX;
		}

		if (tDamage.iCurCount == tDamage.iEndCount)
			erase_damage(_strName);
	}

	void BattleManager::HitchAbnormal(eAbnormalType _eType, float _fAccStat)
	{
		if (_eType == eAbnormalType::None)
			return;

		GameObject* pPlayer = SceneManger::FindPlayer();
		if (_eType == eAbnormalType::Stigma)
		{
			//씬에서 관리하는 게 더 좋음
			EventManager::HitchAbnormal(pPlayer, _eType, _fAccStat);
			return;
		}
			
		if (!m_bOnAbnormal)
			EventManager::HitchAbnormal(pPlayer, _eType, _fAccStat);

		m_bOnAbnormal = true;
	}

	void BattleManager::erase_damage(const std::wstring& _strName)
	{
		DamageMap::iterator iter = m_mapDamage.find(_strName);

		if (iter == m_mapDamage.end())
			return;

		m_mapDamage.erase(iter);
	}

	BattleManager::tDamageCount& BattleManager::add_damage(UINT _iDamageCount, const std::wstring& _strName)
	{
		BattleManager::tDamageCount Count = {};

		DamageMap::iterator iter = m_mapDamage.find(_strName);
		if (iter == m_mapDamage.end())
		{
			Count.iCurCount = 1;
			Count.iEndCount = _iDamageCount;
			Count.m_fCurTime = 0.f;
			m_mapDamage.insert(std::make_pair(_strName, Count));

			return Count;
		}
		else
		{
			if (iter->second.iCurCount > _iDamageCount)
				iter->second.iCurCount = 0;

			++iter->second.iCurCount;
			return iter->second;
		}
	}


	void BattleManager::PushFont(DamageFont* _pDamageFont)
	{
		m_queueFonts.push(_pDamageFont);	
	}

	void BattleManager::dark(GameObject* _pGameObject)
	{

	}
	void BattleManager::stop(GameObject* _pGameObject)
	{
		Player* pPlayer = dynamic_cast<Player*>(_pGameObject);
		if (!pPlayer)
			return;

		Stop * pStop = new Stop();
		pStop->SetTarget(pPlayer);
		pStop->SetTime(6.f);
		EventManager::CreateObject(pStop, eLayerType::Object);

		PlayerScript* pScript = pPlayer->GetScript<PlayerScript>();
		pScript->m_bAbnormal = true;

		EventManager::ChangePlayerSkillState(Player::ePlayerSkill::end);
		EventManager::ChangePlayerFSMState(pScript->m_pFSM, Player::ePlayerState::alert);
	}
	void BattleManager::faint(GameObject* _pGameObject)
	{
		Player* pPlayer = dynamic_cast<Player*>(_pGameObject);
		if (!pPlayer)
			return;

		Faint* pFaint = new Faint();
		pFaint->SetTarget(pPlayer);
		pFaint->SetTime(5.f);
		EventManager::CreateObject(pFaint, eLayerType::Object);

		PlayerScript* pScript = pPlayer->GetScript<PlayerScript>();
		pScript->m_bAbnormal = true;
		
		EventManager::ChangePlayerSkillState(Player::ePlayerSkill::end);
		EventManager::ChangePlayerFSMState(pScript->m_pFSM, Player::ePlayerState::alert);
		//SkillManager::SetActiveSkill(Player::ePlayerSkill::end);
	}
	void BattleManager::seal_potion(GameObject* _pGameObject)
	{

	}

	//음수로 넣어야함
	void BattleManager::debuff_slow(GameObject* _pGameObject, float _fAccSpeed)
	{
		Player* pPlayer = dynamic_cast<Player*>(_pGameObject);
		tObjectInfo& tInfo = pPlayer->GetScript<PlayerScript>()->m_tObjectInfo;
		if (!pPlayer)
			return;

		if (_fAccSpeed < 0)
		{
			Slow* pSlow = new Slow(_fAccSpeed);
			pSlow->SetTarget(pPlayer);
			pSlow->SetTime(6.f);
			EventManager::CreateObject(pSlow, eLayerType::Object);
		}

		tInfo.fSpeed += _fAccSpeed;
	}

	void BattleManager::seal_skill(GameObject* _pGameObject)
	{
		Player* pPlayer = dynamic_cast<Player*>(_pGameObject);
		if (!pPlayer)
			return;

		SealSkill* pSeal = new SealSkill();
		pSeal->SetTarget(pPlayer);
		pSeal->SetTime(7.f);
		EventManager::CreateObject(pSeal, eLayerType::Object);

		PlayerScript* pScript = pPlayer->GetScript<PlayerScript>();
		pScript->m_bSealSkill = true;

		EventManager::ChangePlayerSkillState(Player::ePlayerSkill::end);
		//SkillManager::SetActiveSkill(Player::ePlayerSkill::end);
	}

	void BattleManager::temptation(GameObject* _pGameObject)
	{
		Player* pPlayer = dynamic_cast<Player*>(_pGameObject);
		if (!pPlayer)
			return;

		Temptation* pTemptation = new Temptation();
		pTemptation->SetTarget(pPlayer);
		pTemptation->SetTime(5.f);
		EventManager::CreateObject(pTemptation, eLayerType::Object);


		//스킬 초기화
		//SkillManager::SetActiveSkill(Player::ePlayerSkill::end);
		EventManager::ChangePlayerSkillState(Player::ePlayerSkill::end);

		PlayerScript* pScript = pPlayer->GetScript<PlayerScript>();
		pScript->m_pFSM->SetActiveState(Player::ePlayerState::jump);
		pPlayer->SetPlayerCurState(Player::ePlayerState::jump);
		pPlayer->SetCurStateName(L"_jump");

		pScript->m_bAbnormal = true;

		srand(time(NULL));
		int i = rand() % 2;
		if (i == 0)
			pPlayer->SetDir(1);
		else
			pPlayer->SetDir(-1);
	}

	void BattleManager::undead(GameObject* _pGameObject)
	{
		Player* pPlayer = dynamic_cast<Player*>(_pGameObject);
		if (!pPlayer)
			return;

		Undead* pUndead = new Undead();
		pUndead->SetTarget(pPlayer);
		pUndead->SetTime(8.f);
		EventManager::CreateObject(pUndead, eLayerType::Object);

		m_bOnUndead = true;
	}

	void BattleManager::PushEffect(Effect* _pEffect)
	{
		EffectMap::iterator iter = m_mapEffects.find(_pEffect->GetName());
		if (iter == m_mapEffects.end())
		{
			std::queue<Effect*> pQueue;
			pQueue.push(_pEffect);
			m_mapEffects.insert(std::make_pair(_pEffect->GetName(), pQueue));
		}
		else
		{
			iter->second.push(_pEffect);
			_pEffect->SetActive(false);
		}
	}

	Effect* BattleManager::GetEffect(std::wstring _strName)
	{
		EffectMap::iterator iter = m_mapEffects.find(_strName);

		if (iter == m_mapEffects.end() ||
			iter->second.empty())
			return  nullptr;
		
		Effect* pEffect = iter->second.front();
		iter->second.pop();
		

		return pEffect;
	}

	void BattleManager::restore(GameObject* _pTarget, eAbnormalType _eType, float _fAccValue)
	{
		PlayerScript* pScript = _pTarget->GetScript<PlayerScript>();
		switch (_eType)
		{
		case W::BattleManager::eAbnormalType::SealPotion:
			break;
		case W::BattleManager::eAbnormalType::SealSkill:
			pScript->m_bSealSkill = false;
			break;
		case W::BattleManager::eAbnormalType::temptation:
			pScript->m_bAbnormal = false;
			break;
		case W::BattleManager::eAbnormalType::Faint:
			pScript->m_bAbnormal = false;
			break;
		case W::BattleManager::eAbnormalType::Stop:
			pScript->m_bAbnormal = false;
			break;
		case W::BattleManager::eAbnormalType::Slow:
			debuff_slow(_pTarget, _fAccValue);
			break;
		case W::BattleManager::eAbnormalType::Undead:
			m_bOnUndead = false;
			break;
		case W::BattleManager::eAbnormalType::DemianStop:
			pScript->m_bAbnormal = false;
			break;
		case W::BattleManager::eAbnormalType::InputKey:
			pScript->m_bAbnormal = false;
			break;
		case W::BattleManager::eAbnormalType::Stigma:
			m_iStigmaCount = 0;
			break;
		}

		m_bOnAbnormal = false;
	}

	bool BattleManager::IsAblePotion()
	{
		if(m_fCurPotionTime>= m_fPotionTime)
			return true;

		return false;
	}

	void BattleManager::buff_attack(GameObject* _pTarget, float _fAccDamage)
	{
		Monster* pTarget=  dynamic_cast<Monster*>(_pTarget);
		MonsterScript* pScript = pTarget->GetScript<MonsterScript>();

		if (_fAccDamage > 0.f)
		{
			AttackUp* pAttackUp = new AttackUp(_fAccDamage);
			pAttackUp->SetTarget(pTarget);
			pAttackUp->SetType(eUpStatType::Attack);
			pAttackUp->SetDeleteTime(10.f);
			EventManager::CreateObject(pAttackUp, eLayerType::Object);

		}

		//기본 공격
		pScript->m_tMonsterInfo.tAttackInfo.fAttackDamage += _fAccDamage;

		//스킬 공격
		for (UINT i = 0; i < pScript->m_vecAttacks.size(); ++i)
		{
			pScript->m_vecAttacks[i].tAttackInfo.fAttackDamage += _fAccDamage;
		}
		
	}

	void BattleManager::buff_defense(GameObject* _pTarget, float _fDefense)
	{
		Monster* pTarget = dynamic_cast<Monster*>(_pTarget);
		MonsterScript* pScript = pTarget->GetScript<MonsterScript>();

		if (_fDefense > 0.f)
		{
			DefenseUp* pAttackUp = new DefenseUp(_fDefense);
			pAttackUp->SetTarget(pTarget);
			pAttackUp->SetType(eUpStatType::Defense);
			pAttackUp->SetDeleteTime(10.f);
			EventManager::CreateObject(pAttackUp, eLayerType::Object);

		}

		pScript->m_tObjectInfo.fDefense += _fDefense;
	}

	void BattleManager::buff_ignore(GameObject* _pTarget, float _fsign)
	{
		Monster* pTarget = dynamic_cast<Monster*>(_pTarget);
		MonsterScript* pScript = pTarget->GetScript<MonsterScript>();

		if (_fsign >=0.f)
		{
			Ignore* pIgnore = new Ignore(m_iMaxDamage);
			pIgnore->SetTarget(pTarget);
			pIgnore->SetType(eUpStatType::Ignore);
			pIgnore->SetDeleteTime(10.f);
			EventManager::CreateObject(pIgnore, eLayerType::Object);

			pScript->m_tObjectInfo.fDefense += m_iMaxDamage;
		}
		else
		{
			pScript->m_tObjectInfo.fDefense -= m_iMaxDamage;
		}
		
	}

	void BattleManager::confusion(GameObject* _pGameObject)
	{
		Player* pPlayer = dynamic_cast<Player*>(_pGameObject);
		if (!pPlayer)
			return;

		Confusion* pConfusion = new Confusion();
		pConfusion->SetTarget(pPlayer);
		pConfusion->SetTime(7.f);

		EventManager::CreateObject(pConfusion, eLayerType::Object);
	}
	void BattleManager::demianstop(GameObject* _pGameObject)
	{
		Player* pPlayer = dynamic_cast<Player*>(_pGameObject);
		if (!pPlayer)
			return;

		DemianEntireAttack* DemianEnire = new DemianEntireAttack();
		DemianEnire->SetTarget(pPlayer);
		 
		PlayerScript* pScript = pPlayer->GetScript<PlayerScript>();
		pScript->m_bAbnormal = true;

		EventManager::ChangePlayerSkillState(Player::ePlayerSkill::end);
		EventManager::ChangePlayerFSMState(pScript->m_pFSM, Player::ePlayerState::alert);

		EventManager::CreateObject(DemianEnire, eLayerType::Object);
	}

	void BattleManager::inputkey(GameObject* _pGameObject)
	{
		Player* pPlayer = dynamic_cast<Player*>(_pGameObject);
		if (!pPlayer)
			return;

		Groggy* pGroggy = new Groggy();
		pGroggy->SetTarget(pPlayer);
		pGroggy->SetTime(999999.f);
		//플레이어 아래에 그리기
		pGroggy->SetRenderPos(false);
		pGroggy->Initialize();

		PlayerScript* pScript = pPlayer->GetScript<PlayerScript>();
		pScript->m_bAbnormal = true;

		EventManager::ChangePlayerSkillState(Player::ePlayerSkill::end);
		EventManager::ChangePlayerFSMState(pScript->m_pFSM, Player::ePlayerState::alert);

		//key입력
		InputBackground* pInput = new InputBackground();
		pInput->Initialize();
		pInput->SetOwner(pGroggy);

		EventManager::CreateObject(pInput, eLayerType::Object);
		EventManager::CreateObject(pGroggy, eLayerType::Object);
	}

	void BattleManager::stigma(GameObject* _pGameObject)
	{
		++m_iStigmaCount;
		if (m_iStigmaCount >= 7)
		{
			tAttackInfo tAttackInfo = {};
			tAttackInfo.fAttack = m_iMaxDamage;
			tAttackInfo.fAttRcnt = 0.f;
			tAttackInfo.fAttUpperRcnt = 0.f;
			SceneManger::FindPlayer()->GetScript<PlayerScript>()->Hit(tAttackInfo, L"stigma");
			
			Player* pPlayer = dynamic_cast<Player*>(_pGameObject);
			Stigma* pStigma = new Stigma();
			pStigma->SetTarget(pPlayer);
			pStigma->SetTime(999.f);
			EventManager::CreateObject(pStigma, eLayerType::Object);
		}
	}

	void BattleManager::buff_heal(GameObject* _pTarget, float _fAccHeal)
	{
		Monster* pTarget = dynamic_cast<Monster*>(_pTarget);
		MonsterScript* pScript = pTarget->GetScript<MonsterScript>();

		pScript->m_tObjectInfo.fHP += _fAccHeal;
	}
	
	void BattleManager::buff_speed(GameObject* _pTarget, float _fAccSpeed)
	{
		Player* pTarget = dynamic_cast<Player*>(_pTarget);
		PlayerScript* pScript = pTarget->GetScript<PlayerScript>();

		if (_fAccSpeed >= 0.f)
		{
			UpStat* pStat = new UpStat(_fAccSpeed);
			pStat->SetTarget(pTarget);
			pStat->SetDeleteTime(10.f);
			pStat->SetType(eUpStatType::Speed);
			EventManager::CreateObject(pStat, eLayerType::Object);
		}
		pScript->m_tObjectInfo.fSpeed += _fAccSpeed;
	}

	void BattleManager::buff_MP(GameObject* _pTarget, float _fAccValue)
	{
		tObjectInfo& tInfo = _pTarget->GetScript<PlayerScript>()->m_tObjectInfo;

		tInfo.fMP += _fAccValue;
		if (tInfo.fMP >= tInfo.fMaxMP)
			tInfo.fMP = tInfo.fMaxMP;
	}

	void BattleManager::buff_HP(GameObject* _pTarget, float _fAccValue)
	{
		tObjectInfo& tInfo = _pTarget->GetScript<PlayerScript>()->m_tObjectInfo;

		if (_fAccValue >= m_iMaxDamage)
			_fAccValue = tInfo.fMaxHP;

		if (m_bOnUndead)
			_fAccValue /= 2.f;

		tInfo.fHP += _fAccValue;
		if (tInfo.fHP >= tInfo.fMaxHP)
			tInfo.fHP = tInfo.fMaxHP;
	}

	void BattleManager::buff_reflex(GameObject* _pTarget, float _fsign)
	{
		Monster* pTarget = dynamic_cast<Monster*>(_pTarget);
		MonsterScript* pScript = pTarget->GetScript<MonsterScript>();

		if (_fsign >= 0.f)
		{
			Reflex* pReflex = new Reflex(m_iMaxDamage);
			pReflex->SetTarget(pTarget);
			pReflex->SetType(eUpStatType::ReflexAttack);
			pReflex->SetDeleteTime(10.f);
			
			EventManager::CreateObject(pReflex, eLayerType::Object);
			pScript->m_tObjectInfo.fDefense += m_iMaxDamage;

			pScript->m_bReflex = true;
		}
		else
		{
			pScript->m_tObjectInfo.fDefense -= m_iMaxDamage;
			pScript->m_bReflex = false;
		}
	}

	void BattleManager::Buff_Stat(GameObject* _pTarget, eUpStatType _eType, float _fAccStat)
	{
		EventManager::UpStat(_pTarget, _eType, _fAccStat);
	}

	void BattleManager::Player_DeBuff_Attack(GameObject* _pTarget, eUpStatType _eType, float _fAccStat)
	{
		//_eType 타입에 따라 추가 가능
		if (_fAccStat >= 0.f)
			_pTarget->GetScript<PlayerScript>()->m_tObjectInfo.fDefense / fabs(_fAccStat);
		else
			_pTarget->GetScript<PlayerScript>()->m_tObjectInfo.fDefense * fabs(_fAccStat);
	}

	

	void BattleManager::variation(GameObject* _pGameObject)
	{
		//복제 몬스터 미리 만들어두고 바꾸기
	/*	Player* pPlayer = dynamic_cast<Player*>(_pGameObject);
		pPlayer->SetState(GameObject::eState::Paused);

		if (!pPlayer)
			return;
		
		Variation* pVariation = new Variation();
		pVariation->SetTarget(pPlayer);
		pVariation->SetTime(1.f);
		EventManager::CreateObject(pVariation, eLayerType::Object);
		
		EventManager::ChangePlayerSkillState(Player::ePlayerSkill::end);*/
	}

	
	
}