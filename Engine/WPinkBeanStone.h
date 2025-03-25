#pragma once
#include "WMonsterAttackObject.h"

namespace W
{
	class PinkBeanStone : public MonsterAttackObject
	{
	public:
		PinkBeanStone();
		virtual ~PinkBeanStone();

		virtual void Initialize()override;
		virtual void Update()override;
		virtual void LateUpdate()override;
		virtual void Render()override;

	private:
		void off();

	private:
		UINT m_iCallCount;
		tMonsterAttack m_tMonsterAttack;
	};

}

