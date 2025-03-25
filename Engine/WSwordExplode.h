#pragma once
#include "WMonsterAttackObject.h"

namespace W
{
	class DemianSword;
	class SwordExplode : public MonsterAttackObject
	{
	public:
		SwordExplode();
		virtual ~SwordExplode();

		virtual void Initialize()override;
		virtual void Update()override;
		virtual void LateUpdate()override;
		virtual void Render()override;

		void SetSword(DemianSword* _pSword) { m_pSword = _pSword; }
	private:
		void off();
		void start();
		void check();

	private:
		UINT m_iCallCount;
		UINT m_iExplodeCount;
		tMonsterAttack m_tMonsterAttack;
		DemianSword* m_pSword;

	};
}


