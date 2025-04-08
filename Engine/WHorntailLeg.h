#pragma once
#include "WMonster.h"

namespace W
{
	class Horntail;
	class HorntailLeg : public Monster
	{
	public:
		HorntailLeg();
		virtual ~HorntailLeg();

		virtual void Initialize()override;
		virtual void Update()override;
		virtual void LateUpdate()override;
		virtual void Render()override;
	};
}


