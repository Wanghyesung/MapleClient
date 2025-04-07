#pragma once
#include "WGameObject.h"

namespace W
{
	class DemianCircle : public GameObject
	{
	public:
		DemianCircle();
		virtual ~DemianCircle();

		virtual void Initialize()override;
		virtual void Update()override;
		virtual void LateUpdate()override;
		virtual void Render()override;

	};
}


