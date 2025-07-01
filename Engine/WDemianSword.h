#pragma once
#include "WMonsterAttackObject.h"
namespace W
{
	class DemianSword : public MonsterAttackObject
	{
	public:
		DemianSword();
		virtual ~DemianSword();

		virtual void Initialize()override;
		virtual void Update()override;
		virtual void LateUpdate()override;
		virtual void Render()override;
		virtual void UpdateState(const wstring& _strStateName, int _iState);

		friend class SwordExplode;
	};
}


