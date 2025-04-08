#pragma once

#include "WInput.h"
namespace W
{
	class InputBackground;
	class InputObject : public GameObject
	{
	public:
		InputObject();
		virtual ~InputObject();

		virtual void Initialize()override;
		virtual void Update()override;
		virtual void LateUpdate()override;
		virtual void Render()override;

	
	};
}


