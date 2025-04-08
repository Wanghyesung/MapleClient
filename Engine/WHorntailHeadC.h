#pragma once
#include "WMonster.h"

namespace W
{
	class Horntail;
	class HorntailHeadC : public Monster
	{
	public:
		HorntailHeadC();
		virtual ~HorntailHeadC();
	
		virtual void Initialize()override;
		virtual void Update()override;
		virtual void LateUpdate()override;
		virtual void Render()override;
	
	};
}


