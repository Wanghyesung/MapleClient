#pragma once
#include "WMonster.h"

namespace W
{
	class Horntail;
	class HorntailHeadB : public Monster
	{
	public:
		HorntailHeadB(Horntail* _pOwner);
		virtual ~HorntailHeadB();

		virtual void Initialize()override;
		virtual void Update()override;
		virtual void LateUpdate()override;
		virtual void Render()override;

	private:
		void add_skill();

		void setAttack();
		void create_breath();
		void create_fire();
		void faint();

	private:
		Horntail* m_pOwner;
	};
}
