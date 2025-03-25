#pragma once
#include "WUI.h"

namespace W
{
	class ChannelNumber : public UI
	{
	public:
		ChannelNumber();
		virtual ~ChannelNumber();

		virtual void Initialize()override;
		virtual void Update()override;
		virtual void LateUpdate()override;
		virtual void Render()override;

		virtual void MouseOn()override;
		virtual void MouseLbtnDown()override;
		virtual void MouseLbtnUp()override;
		virtual void MouseLbtnClicked()override;

	private:
		static UINT NUMBER;
		UINT m_iNumber;

	};
}


