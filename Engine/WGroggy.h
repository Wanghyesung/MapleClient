#pragma once
#include "WAbnormal.h"

namespace W
{
	class Groggy : public Abnormal
	{
	public:
		Groggy();
		virtual ~Groggy();

		virtual void Initialize()override;
		virtual void Update()override;
		virtual void LateUpdate()override;
		virtual void Render()override;

		virtual void Restore()override;

	};
}


