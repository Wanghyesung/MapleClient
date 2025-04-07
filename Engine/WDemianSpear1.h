#pragma once
#include "WMonsterAttackObject.h"

namespace W
{
	class DemianSpear1 : public MonsterAttackObject
	{
	public:
		DemianSpear1();
		virtual ~DemianSpear1();

		virtual void Initialize()override;
		virtual void Update()override;
		virtual void LateUpdate()override;
		virtual void Render()override;

	};

}

