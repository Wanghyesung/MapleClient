#pragma once
#include "WMonsterState.h"

namespace W
{
	class HorntailDead : public MonsterState
	{
	public:
		HorntailDead();
		virtual ~HorntailDead();

		virtual void Update()override;
		virtual void Enter()override;
		virtual void Exit()override;

	private:
		UINT m_iCount;

	};
}
