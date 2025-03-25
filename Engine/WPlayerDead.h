#pragma once
#include "WPlayerState.h"

namespace W
{
	class PlayerDead : public PlayerState
	{
	public:
		PlayerDead();
		virtual ~PlayerDead();

		virtual void Update();
		virtual void Enter();
		virtual void Exit();

	private:
		float m_fRadian;

	};
}


