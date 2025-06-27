#pragma once
#include "WPlayerAttackObject.h"

namespace W
{
	class Aven : public PlayerAttackObject
	{
	public:
		Aven();
		virtual ~Aven();

		virtual void Initialize()override;
		virtual void Update()override;
		virtual void LateUpdate()override;
		virtual void Render()override;
		virtual void UpdateState(const wstring& _strStateName, int _iState)override;


		//UINT m_iCount;
		//static UINT COUNT
	};
}


