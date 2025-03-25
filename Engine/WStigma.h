#pragma once
#include "WAbnormal.h"

namespace W
{
	class Stigma : public Abnormal
	{
	public:
		Stigma();
		virtual ~Stigma();

		virtual void Initialize()override;
		virtual void Update()override;
		virtual void LateUpdate()override;
		virtual void Render()override;

		virtual void Restore()override;

	private:


	};
}


