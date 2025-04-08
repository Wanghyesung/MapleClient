#pragma once
#include "WUpStat.h"

namespace W
{
	class Ignore : public UpStat
	{
	public:
		Ignore();
		virtual ~Ignore();

		virtual void Initialize() override;
		virtual void Update()override;
		virtual void LateUpdate()override;
		virtual void Render()override;

	private:

	};
}

