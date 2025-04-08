#pragma once
#include "WMonster.h"

namespace W
{
	class Horntail;
	class HorntailRightHand : public Monster
	{
	public:
		HorntailRightHand();
		virtual ~HorntailRightHand();

		virtual void Initialize()override;
		virtual void Update()override;
		virtual void LateUpdate()override;
		virtual void Render()override;

	};
}


