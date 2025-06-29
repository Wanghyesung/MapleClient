#pragma once
#include "WMonsterHP.h"

namespace W
{
	class Monster;
	class MonsterBackHP;

	class SharHP : public MonsterHP
	{
	public:
		SharHP();
		virtual ~SharHP();

		virtual void Initialize()override;
		virtual void Update()override;
		virtual void LateUpdate()override;
		virtual void Render()override;
		virtual void UpdateState(const wstring& _strStateName, int _iState)override;

	};

	
}


