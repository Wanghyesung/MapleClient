#pragma once
#include "WMonsterAttackObject.h"
namespace W
{
	class RoccatBean : public MonsterAttackObject
	{
	public:
		RoccatBean();
		virtual ~RoccatBean();

		virtual void Initialize()override;
		virtual void Update()override;
		virtual void LateUpdate()override;
		virtual void Render()override;
		

	};
}


