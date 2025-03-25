#include "WMonsterHit.h"
#include "WAnimator.h"
#include "WMonsterScript.h"
#include "WTime.h"
#include "WRigidbody.h"

namespace W
{
	MonsterHit::MonsterHit():
		m_fAttRigidityTime(10.f)
	{
		SetType(Monster::eMonsterState::hit);
		SetStateName(L"_hit");
	}
	MonsterHit::~MonsterHit()
	{

	}
	void MonsterHit::Update()
	{
		//경직 시간
		m_fAttRigidityTime -= Time::DeltaTime();

		if (m_fAttRigidityTime <= 0.f)
		{
			GetFSM()->ChangeState(Monster::eMonsterState::stand);
			return;
		}

		//공중
		Rigidbody* pRigidbody = GetMonster()->GetComponent<Rigidbody>();
		pRigidbody->AddForce(Vector2(m_tHitInfo.fHitDir * m_tHitInfo.fHitRcnt, 0.f));

	}
	void MonsterHit::Enter()
	{
		m_tHitInfo = GetMonster()->GetScript<MonsterScript>()->GetHitInfo();
		m_fAttRigidityTime = m_tHitInfo.fHitRigidityTime;
	}
	void MonsterHit::Exit()
	{

	}
}