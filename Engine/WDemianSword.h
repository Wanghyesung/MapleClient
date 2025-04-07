#pragma once
#include "WMonsterAttackObject.h"
namespace W
{
	class DemianSword : public MonsterAttackObject
	{
	public:
		DemianSword();
		virtual ~DemianSword();

		virtual void Initialize()override;
		virtual void Update()override;
		virtual void LateUpdate()override;
		virtual void Render()override;

		friend class SwordExplode;
	};
}


