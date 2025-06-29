#pragma once
#include "WMonster.h"

namespace W
{
	
	class Whiggin : public Monster
	{
	public:
		Whiggin();
		virtual ~Whiggin();

		virtual void Initialize()override;
		virtual void Update()override;
		virtual void LateUpdate()override;
		virtual void Render()override;
		virtual void UpdateState(const wstring& _strStateName, int _iState)override;

	};


}


