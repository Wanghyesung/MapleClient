#pragma once
#include "WMonsterAttackObject.h"
namespace W
{
	class DemianFire0 : public MonsterAttackObject
	{
	public:
		DemianFire0();
		virtual ~DemianFire0();

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


