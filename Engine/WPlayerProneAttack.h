#pragma once
#include "WPlayerState.h"

namespace W
{
	class PlayerProneAttack : public PlayerState
	{
	public:
		PlayerProneAttack();
		virtual ~PlayerProneAttack();

		virtual void Update()override;
		virtual void Enter()override;
		virtual void Exit()override;


	private:
	};

}
	
