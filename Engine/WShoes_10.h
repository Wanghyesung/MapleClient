#pragma once

#include "WEquip.h"

namespace W
{
	class Shoes_10 : public Equip
	{
	public:
		Shoes_10();
		virtual ~Shoes_10();

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


