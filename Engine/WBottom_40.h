#pragma once

#include "WEquip.h"
namespace W
{
	class Bottom_40 : public Equip
	{
	public:
		Bottom_40();
		virtual ~Bottom_40();

		virtual void Initialize() override;
		virtual void Update()override;
		virtual void LateUpdate()override;
		virtual void Render()override;

		virtual void MouseOn()override;
		virtual void MouseLbtnDown()override;
		virtual void MouseLbtnUp()override;
		virtual void MouseLbtnClicked()override;

	};
}


