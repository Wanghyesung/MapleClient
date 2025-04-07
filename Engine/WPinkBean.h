#pragma once
#include "WMonster.h"
namespace W
{
	class PinkBean : public Monster
	{
	public:
		PinkBean();
		virtual ~PinkBean();

		virtual void Initialize()override;
		virtual void Update()override;
		virtual void LateUpdate()override;
		virtual void Render()override;

	};
}


