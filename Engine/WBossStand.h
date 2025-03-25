#pragma once
#include "WMonsterState.h"

namespace W
{
	class BossStand : public MonsterState
	{
	public:
		BossStand();
		virtual ~BossStand();

		virtual void Update();
		virtual void Enter();
		virtual void Exit();

	private:
		
	

	};
}


