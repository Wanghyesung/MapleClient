#pragma once
#include "WGameObject.h"

namespace W
{
	class InputBackground : public GameObject
	{
	public:
		InputBackground();
		virtual ~InputBackground();

		virtual void Initialize() override;
		virtual void Update()override;
		virtual void LateUpdate()override;
		virtual void Render()override;

	};
}


