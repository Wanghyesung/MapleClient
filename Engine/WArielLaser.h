#pragma once
#include "WMonsterAttackObject.h"

namespace W
{
	class ArielLaser : public MonsterAttackObject
	{
	public:
		ArielLaser();
		virtual ~ArielLaser();

		virtual void Initialize()override;
		virtual void Update()override;
		virtual void LateUpdate()override;
		virtual void Render()override;

	};
}


