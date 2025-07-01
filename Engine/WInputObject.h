#pragma once

#include "WInput.h"
#include "WGameObject.h"
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
		virtual void UpdateState(const wstring& _strStateName, int _iState)override;
	
	};
}


