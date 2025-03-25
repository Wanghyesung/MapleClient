#pragma once
#include "WMonsterAttackObject.h"
namespace W
{
	class Ice : public MonsterAttackObject
	{
	public:
		Ice();
		virtual ~Ice();

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


