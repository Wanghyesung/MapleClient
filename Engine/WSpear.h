#pragma once
#include "WMonsterAttackObject.h"

namespace W
{
	class Spear : public MonsterAttackObject
	{
	public:
		Spear();
		virtual ~Spear();

		virtual void Initialize()override;
		virtual void Update()override;
		virtual void LateUpdate()override;
		virtual void Render()override;
	};
}


