#pragma once

#include "WEquip.h"

namespace W
{
	class Weapon_63 : public Equip
	{
	public:
		Weapon_63();
		virtual ~Weapon_63();

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


