#pragma once

#include "WItemUI.h"

namespace W
{
	class HairItem : public ItemUI
	{
	public:
		HairItem();
		virtual ~HairItem();

		virtual void Initialize() override;
		virtual void Update()override;
		virtual void LateUpdate()override;
		virtual void Render()override;

		virtual void MouseOn()override;
		virtual void MouseLbtnDown()override;
		virtual void MouseLbtnUp()override;
		virtual void MouseLbtnClicked()override;

		//복사생성자로 받을 때 itemui까지만 만들 수 있으서 여기까지 상속이 안됨
		virtual void Using()final {};
	private:
	};
}


