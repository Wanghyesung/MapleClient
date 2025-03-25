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

		void SetPlayer(Player* _pPlayer) { m_pPlayer = _pPlayer; }
		Player* GetPlayer() { return m_pPlayer; }

		void SetEquipWeapon(Equip* _pEquip);

		void SetAnimationIndex();

		void SetStop(bool _bStop);

	private:
		Player* m_pPlayer;

		PlayerWeapon* m_pPlayerWeapon;
		std::wstring m_strCurAnim;
	};
}


