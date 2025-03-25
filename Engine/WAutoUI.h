#pragma once
#include "WUI.h"

namespace W
{
	class AutoUI : public UI
	{
	public:
		AutoUI();
		virtual ~AutoUI();

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


