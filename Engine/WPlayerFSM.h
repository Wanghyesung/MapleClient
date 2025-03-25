#pragma once
#include "WPlayer.h"

namespace W
{
	class PlayerState;
	class PlayerFSM
	{
	public:
		PlayerFSM();
		~PlayerFSM();

	public:
		void Update();
		void Initialize();
	public:
		void AddState(PlayerState* _pState);
		PlayerState* FindState(Player::ePlayerState _ePlayerState);

		void ChangeState(Player::ePlayerState _ePlayerState);
		void SetActiveState(Player::ePlayerState _ePlayerState);

		PlayerState* GetActiveState() { return m_pActiveState; }

		Player* GetPlayer() { return m_pOwner; }
		void SetPlayer(Player* _pPlayer) { m_pOwner = _pPlayer; }

	private:
		void swing_shuriken();
		void near_attack();

	private:
		std::map<Player::ePlayerState, PlayerState*> m_mapState;
		PlayerState* m_pActiveState;

		Player::ePlayerState m_eCurState;
		Player::ePlayerState m_ePreState;

		Player* m_pOwner;
	};
}


