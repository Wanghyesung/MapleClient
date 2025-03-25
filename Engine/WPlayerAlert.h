#pragma once
#include "WPlayerState.h"

namespace W
{
	class PlayerAlert : public PlayerState
	{
	public:
		PlayerAlert();
		virtual ~PlayerAlert();

		virtual void Update()override ;
		virtual void Enter() override;
		virtual void Exit()  override;
	};
}


