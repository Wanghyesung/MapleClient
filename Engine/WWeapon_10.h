#pragma once

#include "WEquip.h"

namespace W
{
	class Weapon_10 : public Equip
	{
	public:
		Weapon_10();
		virtual ~Weapon_10();

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


