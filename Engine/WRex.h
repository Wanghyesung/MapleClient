#pragma once
#include "WMonster.h"
namespace W
{
	class Rex : public Monster
	{
	public:
		Rex();
		virtual ~Rex();

		virtual void Initialize()override;
		virtual void Update()override;
		virtual void LateUpdate()override;
		virtual void Render()override;

	};
}


