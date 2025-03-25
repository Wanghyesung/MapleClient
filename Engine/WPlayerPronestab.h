#pragma once
#include "WPlayerState.h"
namespace W
{
	class PlayerPronestab : public PlayerState
	{
	public:
		PlayerPronestab();
		virtual ~PlayerPronestab();

		virtual void Update()override;
		virtual void Enter()override;
		virtual void Exit()override;

	private:
		float m_fTime;
	};
}


