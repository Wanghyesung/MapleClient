#pragma once
#include "WMonsterState.h"
#include "WInfo.h"

namespace W
{
	class MonsterHit : public MonsterState
	{
	public:
		MonsterHit();
		virtual ~MonsterHit();

		virtual void Update()override;
		virtual void Enter()override;
		virtual void Exit()override;

	private:
		tHitInfo m_tHitInfo;
		float  m_fAttRigidityTime;
	};
}


