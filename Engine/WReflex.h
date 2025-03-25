#pragma once
#include "WUpStat.h"

namespace W
{
	class Reflex : public UpStat
	{
	public:
		Reflex(float _fAccStat);
		virtual ~Reflex();

		virtual void Initialize() override;
		virtual void Update()override;
		virtual void LateUpdate()override;
		virtual void Render()override;


	private:
		float m_fCurHp;
	};
}


