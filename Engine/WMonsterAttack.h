#pragma once
#include "WMonsterState.h"

namespace W
{
	class MonsterAttack : public MonsterState
	{
	public:
		MonsterAttack();
		virtual ~MonsterAttack();

		virtual void Update()override;
		virtual void Enter()override;
		virtual void Exit() override;

	private:
		tMonsterAttack m_tMonsterAttack;
		UINT m_iCallTime;
	};

}

