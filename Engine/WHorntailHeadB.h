#pragma once
#include "WMonster.h"

namespace W
{
	class Horntail;
	class HorntailHeadB : public Monster
	{
	public:
		HorntailHeadB(Horntail* _pOwner);
		virtual ~HorntailHeadB();

		virtual void Initialize()override;
		virtual void Update()override;
		virtual void LateUpdate()override;
		virtual void Render()override;

	};
}
