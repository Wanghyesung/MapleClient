#pragma once

#include "WUI.h"

namespace W
{
	class StartUI : public UI
	{
	public:
		StartUI();
		virtual ~StartUI();

		virtual void Initialize();
		virtual void Update();
		virtual void LateUpdate();
		virtual void Render();

		virtual void MouseOn()override;
		virtual void MouseLbtnDown()override;
		virtual void MouseLbtnUp()override;
		virtual void MouseLbtnClicked()override;

		void SetFunction(function<void()> _pFunc) { m_pFunction = _pFunc; }

	private:
		function<void()> m_pFunction;

		UINT m_iBtnNumber;
		static UINT COUNT;

	};
}


