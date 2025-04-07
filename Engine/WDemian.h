#pragma once
#include "WMonster.h"

namespace W
{
	class DemianSword;
	class Demian : public Monster
	{
	public:
		Demian();
		virtual ~Demian();

		virtual void Initialize()override;
		virtual void Update()override;
		virtual void LateUpdate()override;
		virtual void Render()override;

	
	};
}


