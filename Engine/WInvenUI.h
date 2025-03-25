#pragma once
#include "WUI.h"
#include "WIconUI.h"

namespace W
{
	class InvenUI : public UI
	{
	public:
		InvenUI();
		virtual ~InvenUI();

		virtual void Initialize() override;
		virtual void Update()override;
		virtual void LateUpdate()override;
		virtual void Render()override;

		virtual void MouseOn()override;
		virtual void MouseLbtnDown()override;
		virtual void MouseLbtnUp()override;
		virtual void MouseLbtnClicked()override;

	private:
		

	};
}


