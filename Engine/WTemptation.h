#pragma once
#include "WAbnormal.h"

namespace W
{
	class Temptation : public Abnormal
	{
	public:
		Temptation();
		virtual ~Temptation();

		virtual void Initialize() override;
		virtual void Update()override;
		virtual void LateUpdate()override;
		virtual void Render()override;

		virtual void Restore()override;
		
	private:

	};
}


