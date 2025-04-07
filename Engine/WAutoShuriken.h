#pragma once
#include "WPlayerAttackObject.h"

namespace W
{
	class Monster;
	class AutoShuriken : public PlayerAttackObject
	{
	public:
		AutoShuriken();
		virtual ~AutoShuriken();

		virtual void Initialize()override;
		virtual void Update()override;
		virtual void LateUpdate()override;
		virtual void Render()override;

	private:
		int m_iDir;
	};
}


