#pragma once
#include "WMonster.h"

namespace W
{
	class Horntail;
	class HorntailWing : public Monster
	{
	public:
		HorntailWing();
		virtual ~HorntailWing();

		virtual void Initialize()override;
		virtual void Update()override;
		virtual void LateUpdate()override;
		virtual void Render()override;

	};
}


