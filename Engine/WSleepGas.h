#pragma once
#include "WMonsterAttackObject.h"
namespace W
{
	class SleepGas : public MonsterAttackObject
	{
	public:
		SleepGas();
		virtual ~SleepGas();

		virtual void Initialize()override;
		virtual void Update()override;
		virtual void LateUpdate()override;
		virtual void Render()override;

	};

}



