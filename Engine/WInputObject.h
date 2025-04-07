#pragma once
#include "WObject.h"
#include "WInput.h"
namespace W
{
	class InputBackground;
	class InputObject : public GameObject
	{
	public:
		InputObject(eKeyCode _eKeyCode);
		virtual ~InputObject();

		virtual void Initialize()override;
		virtual void Update()override;
		virtual void LateUpdate()override;
		virtual void Render()override;

	
	};
}


