#pragma once
#include "WMonsterAttackObject.h"
namespace W
{
	class DemianFire1 : public MonsterAttackObject
	{
	public:
		DemianFire1();
		virtual ~DemianFire1();

		virtual void Initialize()override;
		virtual void Update()override;
		virtual void LateUpdate()override;
		virtual void Render()override;

	private:
		void off();

	private:
		tMonsterAttack m_tMonsterAttack;
		
		Vector2 m_vVelocity;

		float m_fCurTime;
		float m_fDeleteTime;
	};
}