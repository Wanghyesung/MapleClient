#include "WAttackScript.h"
#include "WGameObject.h"
#include "WTime.h"
#include "WGameObject.h"
#include "WObject.h"
#include "WMonster.h"
#include "WEffect.h"
#include "WAnimator.h"
#include "WPlayerAttackObject.h"
#include "WBattleManager.h"
#include "WEventManager.h"
#include "WSkillManager.h"
#include "WMonsterScript.h"
#include "WSceneManger.h"
#include "WPlayerScript.h"
namespace W
{
	AttackScript::AttackScript() :
		m_iDir(1),
		m_fDeleteTime(0.5f),
		m_fCurDeleteTime(0.f),
		m_bdead(false),
		m_iAccAttCount(0),
		m_bDelete(true),
		m_fAttackTime(0.f),
		m_iAttackCount(1),
		m_iAbleAttackCount(5),
		m_tAttackInfo{},
		m_hashAttack{}

	{
	}
	AttackScript::~AttackScript()
	{

	}
	void AttackScript::Initialize()
	{

	}
	void AttackScript::Update()
	{
		m_fCurDeleteTime += Time::DeltaTime();

		if (m_fCurDeleteTime >= m_fDeleteTime && !m_bdead)
		{
			m_bdead = true;
			EventManager::AddPlayerPool(GetOwner());
			return;
		}
	}
	void AttackScript::LateUpdate()
	{

	}
	void AttackScript::Render()
	{

	}
	void AttackScript::OnCollisionEnter(Collider2D* other)
	{
		GameObject* pOther = other->GetOwner();

		if (pOther->GetLayerType() == eLayerType::Monster)
		{
			if (!m_bdead)
			{
				//등록된 공격인지
				if (!check_attack(other->GetColliderID()))
					return;
	
				create_effect(other);

				//추가 공격
				if (m_iAccAttCount>0)
				{
					SkillManager::AccAttack(other->GetPosition());
					--m_iAccAttCount;
				}

				if (m_bDelete)
				{
					m_bdead = true;
					EventManager::AddPlayerPool(GetOwner());
				}
			}
		}
	}
	void AttackScript::OnCollisionStay(Collider2D* other)
	{
		GameObject* pOther = other->GetOwner();

		if (pOther->GetLayerType() == eLayerType::Monster)
		{
			UINT ID = other->GetColliderID();
			check_attack(other->GetColliderID());

			//해당공격 데미지 수 , 시간 체크
			if (!check_time(ID))
				return;

			create_effect(other);
		}
	}
	void AttackScript::OnCollisionExit(Collider2D* other)
	{
		Erase(other->GetColliderID());
	}

	void AttackScript::SetStayObject(UINT _iAttackCount, float _fAttackTime)
	{
		m_bDelete = false;
		m_iAttackCount = _iAttackCount;
		m_fAttackTime = _fAttackTime;
	}

	bool AttackScript::IsAttackOn(UINT _iMonsterID)
	{
		std::unordered_map<UINT, tAttackCount>::iterator iter =
			m_hashAttack.find(_iMonsterID);

		if (iter == m_hashAttack.end())
			return false;

		return iter->second.bAttackOn;
	}

	void AttackScript::ResetAttackCount()
	{
		std::unordered_map<UINT, tAttackCount>::iterator iter =
			m_hashAttack.begin();

		for (iter; iter != m_hashAttack.end(); ++iter)
		{
			iter->second.iCurAttackCount = 1;
			iter->second.fCurAttackTime = 0.f;
		}

	}

	bool AttackScript::check_time(UINT _iMonsterID)
	{
		std::unordered_map<UINT, tAttackCount>::iterator iter =
			m_hashAttack.find(_iMonsterID);

		if (iter == m_hashAttack.end())
			return false;

		tAttackCount& tCount = m_hashAttack[_iMonsterID];
		tCount.fCurAttackTime += Time::DeltaTime();

		if (tCount.iAttackCount <= tCount.iCurAttackCount)
		{
			tCount.bAttackOn = false;
			return false;
		}

		if (tCount.fCurAttackTime >= tCount.fAttackTime / tCount.iAttackCount)
		{
			tCount.fCurAttackTime = 0.f;

			++tCount.iCurAttackCount;
			tCount.bAttackOn = true;
		}
		else
			tCount.bAttackOn = false;

		return tCount.bAttackOn;
	}

	void AttackScript::Erase(UINT _iMonsterID)
	{
		std::unordered_map<UINT, tAttackCount>::iterator iter =
			m_hashAttack.find(_iMonsterID);

		if (iter != m_hashAttack.end())
		{
			m_hashAttack.erase(_iMonsterID);
		}
	}

	void AttackScript::create_effect(Collider2D* other)
	{
		GameObject* pOther = other->GetOwner();

		PlayerAttackObject* pAttackObject
			= dynamic_cast<PlayerAttackObject*>(GetOwner());
		Monster* pMon = dynamic_cast<Monster*>(pOther);

		Effect* pEffect = BattleManager::GetEffect(pAttackObject->GetName());
		if (pEffect)
		{
			EventManager::CreateObject(pEffect, eLayerType::Effect);
			pEffect->SetPosition(other);
			pEffect->SetActive(true);
			pEffect->StartEffect(pMon->GetDir() * -1);
		}

		//sound
		pAttackObject->HitStartSound();
	}

	void AttackScript::off()
	{
		m_bdead = false;
		m_bDelete = true;
		m_fCurDeleteTime = 0.f;
		m_iAccAttCount = 0;
		m_hashAttack.clear();
	}

	bool AttackScript::check_attack(UINT _iMonsterID)
	{
		std::unordered_map<UINT, tAttackCount>::iterator iter =
			m_hashAttack.find(_iMonsterID);

		if (iter != m_hashAttack.end())
			return false;
		if (m_hashAttack.size() >= m_iAbleAttackCount)
			return false;

		add_attack(_iMonsterID);
		return true;
	}

	void AttackScript::add_attack(UINT _iMonsterID)
	{
		tAttackCount tCount = {};
		tCount.bAttackOn = true;
		tCount.fCurAttackTime = 0.f;
		tCount.fAttackTime = m_fAttackTime;
		tCount.iCurAttackCount = 1;
		tCount.iAttackCount = m_iAttackCount;

		m_hashAttack.insert(std::make_pair(_iMonsterID, tCount));
	}
	
}