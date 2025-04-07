#pragma once
#include "WGameObject.h"
#include "WPlayer.h"
namespace W
{
	class PlayerWeapon;
	class PlayerArm : public GameObject
	{
	public:
		PlayerArm();
		virtual ~PlayerArm();

		virtual void Initialize()override;
		virtual void Update()override;
		virtual void LateUpdate()override;
		virtual void Render()override;

		void SetEquipWeapon(Equip* _pEquip);

	};
}


