#pragma once
#include "WPlayerState.h"

namespace W
{
	class PlayerLadder : public PlayerState
	{
	public:
		PlayerLadder();
		virtual ~PlayerLadder();

		virtual void Update();
		virtual void Enter();
		virtual void Exit();

	private:


	};
}


