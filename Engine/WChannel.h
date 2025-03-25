#pragma once
#include "WUI.h"

namespace W
{
	class Channel : public UI
	{
	public:
		Channel();
		virtual ~Channel();

		virtual void Initialize()override;
		virtual void Update()override;
		virtual void LateUpdate()override;
		virtual void Render()override;

		virtual void MouseOn()override;
		virtual void MouseLbtnDown()override;
		virtual void MouseLbtnUp()override;
		virtual void MouseLbtnClicked()override;

		bool IsRender() { return m_bRenderOn; }
		void SetRender(bool _bOn) { m_bRenderOn = _bOn; }

	private:
		bool m_bRenderOn;
	};
}


