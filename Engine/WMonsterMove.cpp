#include "WMonsterMove.h"
#include "WSceneManger.h"
#include "WRigidbody.h"
#include "WTime.h"
#include "WEventManager.h"
#include "WSceneManger.h"
#include "WMonsterStand.h"
#include "WMonsterScript.h"
namespace W
{
	MonsterMove::MonsterMove():
		m_pTarget(nullptr),
		m_fTime(1.f),
		m_fTargetDistance(3.f)
	{
		SetType(Monster::eMonsterState::move);
		SetStateName(L"_move");

	}

	MonsterMove::~MonsterMove()
	{

	}

	void MonsterMove::Update()
	{
		bool bHit = false;

		Monster* pMonster = GetMonster();
		Transform* pMonTr = pMonster->GetComponent<Transform>();
	
		m_fTime -= Time::DeltaTime();
		if (m_fTime <= 0.f)
		{
			EventManager::ChangeMonsterFSMState(GetFSM(), Monster::eMonsterState::stand);
			return;
		}

		move_target();
		
	}
	void MonsterMove::Enter()
	{
		MonsterState* pState = GetFSM()->FindState(Monster::eMonsterState::stand);
		m_fTargetDistance =  dynamic_cast<MonsterStand*>(pState)->GetTargetDistance();
		m_fTime = 1.f;
	}
	void MonsterMove::Exit()
	{

	}
	void MonsterMove::move_target()
	{
		m_pTarget = SceneManger::FindPlayer();
		if (m_pTarget == nullptr)
			return;

		Monster* pMonster = GetMonster();
		Player* pPlayer = dynamic_cast<Player*>(m_pTarget);

		Vector3 vTargetPosition = m_pTarget->GetComponent<Collider2D>()->GetPosition();
		Vector3 vPosition = GetMonster()->GetComponent<Collider2D>()->GetPosition();
		vTargetPosition.z = 0.f;
		vPosition.z = 0.f;

		Vector3 vDiff = vTargetPosition - vPosition;

		float fLen = vDiff.Length();
		float iDir;
		const tObjectInfo& tInfo = GetMonster()->GetScript<MonsterScript>()->GetObjectInfo();
	
		if (fLen <= 0.4f)
		{
			EventManager::ChangeMonsterFSMState(GetFSM(), Monster::eMonsterState::stand);
		}

		else if (fLen <= m_fTargetDistance)
		{
			iDir = vDiff.x > 0 ? 1 : -1;

			pMonster->GetComponent<Rigidbody>()->AddForce(Vector2(tInfo.fSpeed * iDir, 0.f));
			GetMonster()->SetDir(iDir);
		}

		else
		{
			int iDir = pMonster->GetDir();
			pMonster->GetComponent<Rigidbody>()->AddForce(Vector2(tInfo.fSpeed * iDir, 0.f));
		}
		
	}
}