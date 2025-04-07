#pragma once

#include "WMonster.h"

namespace W
{
	class Ariel : public Monster
	{
	public:
		Ariel();
		virtual ~Ariel();

		virtual void Initialize()override;
		virtual void Update()override;
		virtual void LateUpdate()override;
		virtual void Render()override; 
	

	};
}


