#pragma once

#include "WItemUI.h"

namespace W
{
	class EyeItem : public ItemUI
	{
	public:
		EyeItem();
		EyeItem(const EyeItem& _pItem);
		virtual ~EyeItem();

		virtual void Initialize() override;
		virtual void Update()override;
		virtual void LateUpdate()override;
		virtual void Render()override;

		virtual void MouseOn()override;
		virtual void MouseLbtnDown()override;
		virtual void MouseLbtnUp()override;
		virtual void MouseLbtnClicked()override;

		virtual EyeItem* Create_Clone()override;
		virtual void Using()override;
	private:
	};
}


