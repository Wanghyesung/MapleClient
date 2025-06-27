#pragma once

#include "WMonsterAttackObject.h"

namespace W
{
	class Fire : public MonsterAttackObject
	{
	public:
		Fire();
		virtual ~Fire();

		virtual void Initialize()override;
		virtual void Update()override;
		virtual void LateUpdate()override;
		virtual void Render()override;
		virtual void UpdateState(const wstring& _strStateName, int _iState)override;

	};
}


