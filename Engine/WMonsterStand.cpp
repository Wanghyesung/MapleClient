#include "WMonsterStand.h"
#include "WSceneManger.h"
#include "WPlayer.h"
#include "WTime.h"
#include "WEventManager.h"
#include "WSceneManger.h"

namespace W
{
	MonsterStand::MonsterStand():
		m_bHit(false),
		m_fTime(2.5f),
		m_fCurTime(0.f),
		m_fTargetDistance(3.f),
		m_fMinDistance(0.4f)
	{
		SetType(Monster::eMonsterState::stand);
		SetStateName(L"_stand");
	}
	MonsterStand::~MonsterStand()
	{

	}
	void MonsterStand::Update()
	{
		m_fCurTime += Time::DeltaTime();
		
		if (m_fCurTime >= m_fTime)
		{
			EventManager::ChangeMonsterFSMState(GetFSM(), Monster::eMonsterState::move);
			GetMonster()->SetDir(GetMonster()->GetDir() * -1);
		}

		else
		{
			m_pTarget = SceneManger::FindPlayer();

			if (m_pTarget == nullptr)
				return;

			Vector3 vTargetPosition = m_pTarget->GetComponent<Collider2D>()->GetPosition();
			Vector3 vPosition = GetMonster()->GetComponent<Collider2D>()->GetPosition();

			float fLen = fabs(vTargetPosition.x - vPosition.x);
			if (fLen <= 0.4f)
			{
				m_fCurTime = 0.f;
			}
			else if (fLen <= m_fMinDistance)
			{
				EventManager::ChangeMonsterFSMState(GetFSM(), Monster::eMonsterState::move);
			}
		}
	}
	void MonsterStand::Enter()
	{
		Collider2D* pCollider = GetMonster()->GetComponent<Collider2D>();
		if (!pCollider->IsActive())
			pCollider->SetActive(true);
	}
	void MonsterStand::Exit()
	{
		m_fCurTime = 0.f;
	}
}