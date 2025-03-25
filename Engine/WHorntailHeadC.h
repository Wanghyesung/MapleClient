#pragma once
#include "WMonster.h"

namespace W
{
	class Horntail;
	class HorntailHeadC : public Monster
	{
	public:
		HorntailHeadC(Horntail* _pOwner);
		virtual ~HorntailHeadC();
	
		virtual void Initialize()override;
		virtual void Update()override;
		virtual void LateUpdate()override;
		virtual void Render()override;
	
	private:
		void add_skill();

		void setAttack();
		void create_breath();
		void create_thunder();
		void ignore();
	
	private:
		Horntail* m_pOwner;
	};
}


