#pragma once
#include "WMonster.h"
namespace W
{
	class Horntail;
	class HorntailLeftHand : public Monster
	{
	public:
		HorntailLeftHand();
		virtual ~HorntailLeftHand();

		virtual void Initialize()override;
		virtual void Update()override;
		virtual void LateUpdate()override;
		virtual void Render()override;

	};
}

