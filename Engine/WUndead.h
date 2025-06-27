#pragma once
#include "WAbnormal.h"

namespace W
{
	class Undead :public Abnormal
	{
	public:
		Undead();
		virtual ~Undead();

		virtual void Initialize() override;
		virtual void Update()override;
		virtual void LateUpdate()override;
		virtual void Render()override;
		virtual void UpdateState(const wstring& _strStateName, int _iState);
		
		virtual void Restore()override;

	private:
	};
}


