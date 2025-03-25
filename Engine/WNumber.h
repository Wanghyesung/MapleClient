#pragma once
#include "WUI.h"

namespace W
{
	class Number : public UI
	{
	public:
		Number();
		virtual ~Number();

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


