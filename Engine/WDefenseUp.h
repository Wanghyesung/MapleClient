#pragma once
#include "WUpStat.h"

namespace W
{
	class DefenseUp : public UpStat
	{
	public:
		DefenseUp(float _fAccStat);
		virtual ~DefenseUp();

		virtual void Initialize() override;
		virtual void Update()override;
		virtual void LateUpdate()override;
		virtual void Render()override;

	private:
	};
}

