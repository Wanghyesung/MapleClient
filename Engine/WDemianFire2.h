#pragma once
#include "WMonsterAttackObject.h"

namespace W
{
	class DemianFire2 : public MonsterAttackObject
	{
	public:
		DemianFire2();
		virtual ~DemianFire2();

		virtual void Initialize()override;
		virtual void Update()override;
		virtual void LateUpdate()override;
		virtual void Render()override;

	private:
		void off();

		void start();
		void move();
	private:
		tMonsterAttack m_tMonsterAttack;
		std::wstring m_strCurAnim;

		Vector2 m_vVelocity;
		bool m_bMove;
		bool m_bEnd;

	};

}

