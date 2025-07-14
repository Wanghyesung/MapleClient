#pragma once

#include "WGameObject.h"
#include "WPlayer.h"
#include "WPlayerHair.h"
#include "WEyes.h"

namespace W
{
	class PlayerHat;
	class PlayerHair;
	class Eyes;
	class PlayerHead : public GameObject
	{
	public:
		PlayerHead();
		virtual ~PlayerHead();

		virtual void Initialize()override;
		virtual void Update()override;
		virtual void LateUpdate()override;
		virtual void Render()override;

		void SetEquipHat(Equip* _pEquip);
		void SetEquipHat(const wstring& _strEquipName);

		void SetPlayer(Player* _pPlayer) { m_pPlayer = _pPlayer; }
		Player* GetPlayer() { return m_pPlayer; }

		void SetHair(UINT _iHairNum);
		void SetEye(UINT _iEyeNum);

		UINT GetHairID() { return m_pPlayerHair->GetHairID(); }
		UINT GetEyeID() { return m_pPlayerEyes->GetEyeID(); }
		
	private:
		Player* m_pPlayer;

		Eyes* m_pPlayerEyes;
		PlayerHair* m_pPlayerHair;
		PlayerHat* m_pPlayerHat;

		std::wstring m_strCurAnim;
	};
}


