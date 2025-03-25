#include "WMonsterAttackScript.h"
#include "WGameObject.h"
#include "WEffect.h"
#include "WMonsterAttackObject.h"
#include "WEventManager.h"
#include "WBattleManager.h"
#include "WPlayer.h"
#include "WCollisionManager.h"
#include "WPlayerScript.h"
namespace W
{
	MonsterAttackScript::MonsterAttackScript() :
		m_eAbnorType(BattleManager::eAbnormalType::None),
		m_fAccValue(0.f),
		m_iAbnormalStack(1),
		m_bEnter(false)
	{
	}
	MonsterAttackScript::~MonsterAttackScript()
	{

	}
	void MonsterAttackScript::Initialize()
	{

	}
	void MonsterAttackScript::Update()
	{

	}
	void MonsterAttackScript::LateUpdate()
	{

	}
	void MonsterAttackScript::Render()
	{

	}

	void MonsterAttackScript::OnCollisionEnter(Collider2D* other)
	{
		GameObject* pOther = other->GetOwner();
		if (pOther->GetLayerType() == eLayerType::Player ||
			pOther->GetLayerType() == eLayerType::Ground)
		{
			if (pOther->GetLayerType() == eLayerType::Player)
				m_bPlayerEnter = true;

			m_bEnter = true;
		}
			
	}

	void MonsterAttackScript::OnCollisionStay(Collider2D* other)
	{
		GameObject* pOther = other->GetOwner();

		if (pOther->GetLayerType() == eLayerType::Player)
		{
			MonsterAttackObject* pMonsterAttack = dynamic_cast<MonsterAttackObject*>(GetOwner());
			Player* pPlayer = dynamic_cast<Player*>(pOther);
			bool bHit = pPlayer->IsAlert();
			if (bHit)
				return;

			//ex : ½ºÅÏ, ¾ÏÈæ, ³«ÀÎ
			if (m_iAbnormalStack == 1)
			{
				BattleManager::HitchAbnormal(m_eAbnorType, m_fAccValue);
				m_iAbnormalStack = 0;
			}

			Effect* pEffect = BattleManager::GetEffect(pMonsterAttack->GetName());
			if (pEffect)
			{
				EventManager::CreateObject(pEffect, eLayerType::Effect);
				pEffect->SetOwner(pOther);
				pEffect->SetPosition(other);
				pEffect->SetActive(true);
				pEffect->StartEffect(pPlayer->GetDir() * -1);
			}
		}
	}

	void MonsterAttackScript::OnCollisionExit(Collider2D* other)
	{
		GameObject* pOther = other->GetOwner();

		if (pOther->GetLayerType() == eLayerType::Player)
			m_bPlayerEnter = false;
	}
}