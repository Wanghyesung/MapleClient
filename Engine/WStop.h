#pragma once
#include "WAbnormal.h"
namespace W
{
	class Stop : public Abnormal
	{
	public:
		Stop();
		virtual ~Stop();

		virtual void Initialize() override;
		virtual void Update()override;
		virtual void LateUpdate()override;
		virtual void Render()override;


		virtual void Restore()override;

	private:
	};
}


