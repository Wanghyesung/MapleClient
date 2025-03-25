#pragma once
#include "WPlayerState.h"

namespace W
{
	class PlayerStand : public PlayerState
	{
	public:
		PlayerStand();
		virtual ~PlayerStand();

		virtual void Update()override;
		virtual void Enter()override;
		virtual void Exit()override;
		
	private:

	};
}


