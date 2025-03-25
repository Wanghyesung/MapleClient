#pragma once

#include "WEquip.h"

namespace W
{
	class Weapon_25 : public Equip
	{
	public:
		Weapon_25();
		virtual ~Weapon_25();

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


