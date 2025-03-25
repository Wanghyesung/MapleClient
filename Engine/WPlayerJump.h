#pragma once
#include "WPlayerState.h"

namespace W
{
	class PlayerJump : public PlayerState
	{
	public:
		PlayerJump();
		virtual ~PlayerJump();

		virtual void Update();
		virtual void Enter();
		virtual void Exit();

	private:
		

	};
}


