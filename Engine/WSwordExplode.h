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

	};
}


