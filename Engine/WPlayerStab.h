#pragma once
#include "WPlayerState.h"
namespace W
{
	class PlayerStab : public PlayerState
	{
	public:
		PlayerStab();
		virtual ~PlayerStab();

		virtual void Update()override;
		virtual void Enter()override;
		virtual void Exit()override;

	private:
		UINT m_iAttackCount;


	};
}


