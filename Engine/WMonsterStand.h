#pragma once
#include "WMonsterState.h"

namespace W
{
	class Player;
	class MonsterStand : public MonsterState
	{
	public:
		MonsterStand();
		virtual ~MonsterStand();

		virtual void Update()override;
		virtual void Enter()override;
		virtual void Exit()override;

		void SetTargetDistance(float _fDistance) { m_fTargetDistance = _fDistance; }
		void SetMinDistance(float _fDistance) { m_fMinDistance = _fDistance; }

		float GetTargetDistance() { return m_fTargetDistance; }
	private:
		bool m_bHit;

		float m_fCurTime;
		float m_fTime;

		float m_fTargetDistance;
		float m_fMinDistance;

		GameObject* m_pTarget;
	};
}


