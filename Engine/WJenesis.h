#pragma once
#include "WMonsterAttackObject.h"

namespace W
{
	class Jenesis : public MonsterAttackObject
	{
	public:
		Jenesis();
		virtual ~Jenesis();

		virtual void Initialize()override;
		virtual void Update()override;
		virtual void LateUpdate()override;
		virtual void Render()override;

	};
}


