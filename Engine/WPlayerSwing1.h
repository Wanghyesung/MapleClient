#pragma once
#include "WPlayerState.h"

namespace W
{
	class PlayerSwing1 : public PlayerState
	{
	public:
		PlayerSwing1();
		virtual ~PlayerSwing1();

		virtual void Update()override;
		virtual void Enter()override;
		virtual void Exit()override;
	private:
		UINT m_iSwingCount;

	};
}


