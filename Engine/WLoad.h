#pragma once
#include "WPlayerAttackObject.h"

namespace W
{
	class Load : public PlayerAttackObject
	{
	public:
		Load();
		virtual ~Load();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void LateUpdate() override;
		virtual void Render() override;
		virtual void UpdateState(const wstring& _strStateName, int _iState)override;
		

	};
}


