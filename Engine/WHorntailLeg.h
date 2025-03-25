#pragma once
#include "WMonster.h"

namespace W
{
	class Horntail;
	class HorntailLeg : public Monster
	{
	public:
		HorntailLeg(Horntail* _pOwner);
		virtual ~HorntailLeg();

		virtual void Initialize()override;
		virtual void Update()override;
		virtual void LateUpdate()override;
		virtual void Render()override;

	private:
		void add_skill();
		void setAttack();

		void attack1();
		void attack2();

	private:
		Horntail* m_pOwner;

	};
}


