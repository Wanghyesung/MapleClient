#pragma once
#include "WGameObject.h"

namespace W
{
	class PullObject : public GameObject
	{
	public:
		PullObject();
		virtual ~PullObject();

		virtual void Initialize()override;
		virtual void Update()override;
		virtual void LateUpdate()override;
		virtual void Render()override;

	};
}


