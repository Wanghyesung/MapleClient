#pragma once

#include "WPlayerAttackObject.h"

namespace W
{
	class Shuriken : public PlayerAttackObject
	{
	public:
		Shuriken();
		virtual ~Shuriken();

		virtual void Initialize()override;
		virtual void Update()override;
		virtual void LateUpdate()override;
		virtual void Render()override;

		virtual void UpdateState(const wstring& _strStateName, int _iAnim) override;
	};
}


