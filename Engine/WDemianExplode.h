#pragma once
#include "WMonsterAttackObject.h"

namespace W
{
	class DemianExplode : public MonsterAttackObject
	{
	public:
		DemianExplode();
		virtual ~DemianExplode();

		virtual void Initialize()override;
		virtual void Update()override;
		virtual void LateUpdate()override;
		virtual void Render()override;
		virtual void UpdateState(const wstring& _strStateName, int _iState);
	};

}

