#pragma once
#include "WMonsterState.h"

namespace W
{
	class MonsterDead : public MonsterState
	{
	public:
		MonsterDead();
		virtual ~MonsterDead();

		virtual void Update()override;
		virtual void Enter()override;
		virtual void Exit()override;

	private:
		UINT m_iCount;

	};
}


