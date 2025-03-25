#pragma once
#include "WAbnormal.h"

namespace W
{
	class Faint : public Abnormal
	{
	public:
		Faint();
		virtual ~Faint();

		virtual void Initialize() override;
		virtual void Update()override;
		virtual void LateUpdate()override;
		virtual void Render()override;


		virtual void Restore()override;
		
	private:
	};
}


