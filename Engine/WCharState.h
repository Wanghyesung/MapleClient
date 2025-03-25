#pragma once

#include "WUI.h"

namespace W
{
	class CharState : public UI
	{
	public:
		CharState();
		virtual ~CharState();

		virtual void Initialize();
		virtual void Update();
		virtual void LateUpdate();
		virtual void Render();

		virtual void MouseOn();
		virtual void MouseLbtnDown();
		virtual void MouseLbtnUp();
		virtual void MouseLbtnClicked();


	private:

	};
}


