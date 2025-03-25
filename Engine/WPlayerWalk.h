#pragma once
#include "WPlayerState.h"

namespace W
{
	class PlayerWalk : public PlayerState
	{
	public:
		PlayerWalk();
		virtual ~PlayerWalk();

		virtual void Update()override;
		virtual void Enter()override;
		virtual void Exit()override;

	private:
		

	};
}


