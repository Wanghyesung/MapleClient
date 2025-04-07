#pragma once
#include "WGameObject.h"

namespace W
{
	
	class MobZone : public GameObject
	{
	public:
		MobZone();
		virtual ~MobZone();

		virtual void Initialize()override;
		virtual void Update()override;
		virtual void LateUpdate()override;
		virtual void Render()override;
	};
}


