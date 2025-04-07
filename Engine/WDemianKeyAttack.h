#pragma once
#include "WMonsterAttackObject.h"

namespace W
{
	class DemianKeyAttack : public MonsterAttackObject
	{
	public:
		DemianKeyAttack();
		virtual ~DemianKeyAttack();

		virtual void Initialize()override;
		virtual void Update()override;
		virtual void LateUpdate()override;
		virtual void Render()override;

	};
}

