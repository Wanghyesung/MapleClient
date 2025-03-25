#pragma once
#include "WUI.h"

namespace W
{
	class UpBtn : public UI
	{

	public:
		UpBtn();
		virtual ~UpBtn();

		virtual void Initialize();
		virtual void Update();
		virtual void LateUpdate();
		virtual void Render();

		virtual void MouseOn();
		virtual void MouseLbtnDown();
		virtual void MouseLbtnUp();
		virtual void MouseLbtnClicked();

	private:
		static UINT m_iBntCount;
		UINT m_iNumber;
	};
}


