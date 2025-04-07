#pragma once

#include "WPlayerAttackObject.h"

namespace W
{
	class Shuriken : public PlayerAttackObject
	{
	public:
		Shuriken();
		virtual ~Shuriken();

		virtual void Initialize()override;
		virtual void Update()override;
		virtual void LateUpdate()override;
		virtual void Render()override;

	private:
		int m_iDir;
	};
}


