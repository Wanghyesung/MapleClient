#pragma once
#include "WAbnormal.h"

namespace W
{
	class Slow : public Abnormal
	{
	public:
		Slow(float _fAccStat);
		virtual ~Slow();

		virtual void Initialize() override;
		virtual void Update()override;
		virtual void LateUpdate()override;
		virtual void Render()override;

		virtual void Restore()override;
	private:
		float m_fAccValue;
	};
}

