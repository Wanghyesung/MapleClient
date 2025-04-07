#pragma once
#include "WMonster.h"

namespace W
{
	class PinkBean;

	class MiniBean : public Monster
	{
	public:
		MiniBean();
		virtual ~MiniBean();

		virtual void Initialize()override;
		virtual void Update()override;
		virtual void LateUpdate()override;
		virtual void Render()override;

		
	};

}

