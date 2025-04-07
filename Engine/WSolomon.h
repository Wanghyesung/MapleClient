#pragma once
#include "WMonster.h"

namespace W
{
	class Solomon : public Monster
	{
	public:
		Solomon();
		virtual ~Solomon();

		virtual void Initialize()override;
		virtual void Update()override;
		virtual void LateUpdate()override;
		virtual void Render()override;

	};
}


