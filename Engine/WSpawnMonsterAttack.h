#pragma once
#include "WMonsterAttackObject.h"

namespace W
{
	class Monster;

	class SpawnMonsterAttack : public MonsterAttackObject
	{
	public:
		SpawnMonsterAttack();
		virtual ~SpawnMonsterAttack();

		virtual void Initialize()override;
		virtual void Update()override;
		virtual void LateUpdate()override;
		virtual void Render()override;
		
	};
}


