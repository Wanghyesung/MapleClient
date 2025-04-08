#pragma once
#include "WGameObject.h"

namespace W
{
	class UpStat : public GameObject
	{
	public:
		UpStat();
		virtual ~UpStat();

		virtual void Initialize()override;
		virtual void Update()override;
		virtual void LateUpdate()override;
		virtual void Render()override;

	};
}


