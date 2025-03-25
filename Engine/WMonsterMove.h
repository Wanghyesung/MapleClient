#pragma once
#include "WMonsterState.h"

namespace W
{
	class Player;
	class MonsterMove : public MonsterState
	{
	public:
		MonsterMove();
		virtual ~MonsterMove();

		virtual void Update();
		virtual void Enter();
		virtual void Exit();

	private:
		void move_target();

	private:
		GameObject* m_pTarget;
		float m_fTime;
		float m_fTargetDistance;
	};
}

