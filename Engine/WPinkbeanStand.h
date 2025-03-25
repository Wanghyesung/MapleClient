#pragma once
#include "WMonsterState.h"

namespace W
{
	class PinkbeanStand : public MonsterState
	{
	public:
		PinkbeanStand();
		virtual ~PinkbeanStand();

		virtual void Update();
		virtual void Enter();
		virtual void Exit();

	private:
	};
}


