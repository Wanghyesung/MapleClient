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

		void SetNextScene(const std::wstring _strNextScene) { m_strNextScene = _strNextScene; }

	private:
		std::wstring m_strNextScene;

		UINT m_iBtnNumber;
		static UINT COUNT;

	};
}


