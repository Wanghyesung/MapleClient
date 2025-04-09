#pragma once
#include "WGameObject.h"
#include "WPlayer.h"
namespace W
{	
	class PlayerTop;
	class PlayerBottom;
	class PlayerShoes;

	class PlayerBody : public GameObject
	{
	public:
		PlayerBody();
		virtual ~PlayerBody();

		void SetPlayer(Player* _pPlayer) { m_pPlayer = _pPlayer; }
		Player* GetPlayer() { return m_pPlayer; }

		virtual void Initialize()override;
		virtual void Update()override;
		virtual void LateUpdate()override;
		virtual void Render()override;

		void SetEquipTop(Equip* _pEquip);
		void SetEquipBottom(Equip* _pEquip);
		void SetEquipShoes(Equip* _pEquip);

	private:
		Player* m_pPlayer;

		PlayerTop* m_pPlayerTop;
		PlayerBottom* m_pPlayerBottom;
		PlayerShoes* m_pPlayerShoes;

		std::wstring m_strCurAnim;
	};
}


