#pragma once

#include "WMonsterAttackObject.h"

namespace W
{
	class SolThunder : public MonsterAttackObject
	{
	public:
		SolThunder();
		virtual ~SolThunder();

		virtual void Initialize()override;
		virtual void Update()override;
		virtual void LateUpdate()override;
		virtual void Render()override;

	};
}


