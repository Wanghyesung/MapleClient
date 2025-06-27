#pragma once
#include "WMonster.h"

namespace W
{
	class Horntail;
	class HorntailHeadA : public Monster
	{
	public:
		HorntailHeadA();
		virtual ~HorntailHeadA();

		virtual void Initialize()override;
		virtual void Update()override;
		virtual void LateUpdate()override;
		virtual void Render()override;
		virtual void UpdateState(const wstring& _strStateName, int _iState);
	};
}


