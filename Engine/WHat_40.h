#pragma once

#include "WEquip.h"
namespace W
{
	class Hat_40 : public Equip
	{
	public:
		Hat_40();
		virtual ~Hat_40();

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

