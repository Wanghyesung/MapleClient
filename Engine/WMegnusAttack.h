#pragma once
#include "WMonsterAttackObject.h"
namespace W
{
	class MegnusAttack : public MonsterAttackObject
	{
	public:
		MegnusAttack();
		virtual ~MegnusAttack();

		virtual void Initialize()override;
		virtual void Update()override;
		virtual void LateUpdate()override;
		virtual void Render()override;

		void SetDir(int _iDir);
	private:
		void off();
	private:
		UINT m_iCallCount;
		tMonsterAttack m_tMonsterAttack;

	};
}


