#pragma once
#include "WMonsterAttackObject.h"

namespace W
{
	class DemianFire2 : public MonsterAttackObject
	{
	public:
		DemianFire2();
		virtual ~DemianFire2();

		virtual void Initialize()override;
		virtual void Update()override;
		virtual void LateUpdate()override;
		virtual void Render()override;


	};

}

