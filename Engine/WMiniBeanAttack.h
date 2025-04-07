#pragma once
#include "WMonsterAttackObject.h"

namespace W
{
	class MiniBeanAttack : public MonsterAttackObject
	{
	public:
		MiniBeanAttack();
		virtual ~MiniBeanAttack();
		virtual void Initialize()override;
		virtual void Update()override;
		virtual void LateUpdate()override;
		virtual void Render()override;

	};
}

