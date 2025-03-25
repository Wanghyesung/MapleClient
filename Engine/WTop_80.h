#pragma once
#include "WEquip.h"

namespace W
{
	class Top_80 : public Equip
	{
	public:
		Top_80();
		virtual ~Top_80();

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

