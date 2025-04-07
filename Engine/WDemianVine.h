#pragma once
#include "WMonsterAttackObject.h"

namespace W
{
	class White;
	class DemianVine : public MonsterAttackObject
	{
	public:
		DemianVine();
		virtual ~DemianVine();

		virtual void Initialize()override;
		virtual void Update()override;
		virtual void LateUpdate()override;
		virtual void Render()override;

	};
}


