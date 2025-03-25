#pragma once
#include "WAbnormal.h"

namespace W
{
	class DemianEntireAttack : public Abnormal
	{
	public:
		DemianEntireAttack();
		virtual ~DemianEntireAttack();

		virtual void Initialize()override;
		virtual void Update()override;
		virtual void LateUpdate()override;
		virtual void Render()override;

		virtual void Restore()override;


	private:
		UINT m_iCallStack;
		UINT m_iKeyDonwCount;

		float m_fDeleteTime;
		float m_fCurTime;
	};
}


