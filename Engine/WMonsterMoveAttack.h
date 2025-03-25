#pragma once
//attack2
#include "WMonsterAttackObject.h"

namespace W
{
	class MonsterMoveAttack : public MonsterAttackObject
	{
	public:
		MonsterMoveAttack();
		virtual ~MonsterMoveAttack();

		virtual void Initialize()override;
		virtual void Update()override;
		virtual void LateUpdate()override;
		virtual void Render()override;
	
	private:
		tMonsterAttack m_tMonsterAttack;

	};
}


