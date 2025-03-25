#pragma once
#include "WMonster.h"

namespace W
{
	class Horntail;
	class HorntailHeadA : public Monster
	{
	public:
		HorntailHeadA(Horntail* _pOwner);
		virtual ~HorntailHeadA();

		virtual void Initialize()override;
		virtual void Update()override;
		virtual void LateUpdate()override;
		virtual void Render()override;

	private:
		void add_skill();

		void setAttack();
		void create_breath();
		void create_ice();
		void physics_ignore();

	private:
		Horntail* m_pOwner;
	};
}


