#pragma once
#include "WMonsterState.h"

namespace W
{
	class BossStart : public MonsterState
	{
	public:
		BossStart();
		virtual ~BossStart();

		virtual void Update()override;
		virtual void Enter()override;
		virtual void Exit()override;

	private:
		UINT m_iCount;
	};
}

