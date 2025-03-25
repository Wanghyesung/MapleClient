#pragma once
#include "WUpStat.h"

namespace W
{
	class AttackUp : public UpStat
	{
	public:
		AttackUp(float _fAccStat);
		virtual ~AttackUp();

		virtual void Initialize() override;
		virtual void Update()override;
		virtual void LateUpdate()override;
		virtual void Render()override;

	private:
		
	};
}


