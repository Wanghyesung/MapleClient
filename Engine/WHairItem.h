#pragma once

#include "WItemUI.h"

namespace W
{
	class HairItem : public ItemUI
	{
	public:
		HairItem();
		HairItem(const HairItem& _pItem);
		virtual ~HairItem();

		virtual void Initialize() override;
		virtual void Update()override;
		virtual void LateUpdate()override;
		virtual void Render()override;

		virtual void MouseOn()override;
		virtual void MouseLbtnDown()override;
		virtual void MouseLbtnUp()override;
		virtual void MouseLbtnClicked()override;

		virtual HairItem* Create_Clone()override;
		virtual void Using()override;
	private:
	};
}


