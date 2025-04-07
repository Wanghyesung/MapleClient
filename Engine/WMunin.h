#pragma once
#include "WMonster.h"

namespace W
{
	class Munin : public Monster
	{
	public:
		Munin();
		virtual ~Munin();


		virtual void Initialize()override;
		virtual void Update()override;
		virtual void LateUpdate()override;
		virtual void Render()override;


	};
}


