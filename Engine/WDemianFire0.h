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
		virtual void UpdateState(const wstring& _strStateName, int _iState);
	};
}


