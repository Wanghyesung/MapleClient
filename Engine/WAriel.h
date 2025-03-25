#pragma once

#include "WMonster.h"

namespace W
{
	class Ariel : public Monster
	{
	public:
		Ariel();
		virtual ~Ariel();

		virtual void Initialize()override;
		virtual void Update()override;
		virtual void LateUpdate()override;
		virtual void Render()override; 
	
	private:
		void add_skill();

		void setattack();
		void attack1();
		void attack2();

		void heal();
		void pull();


	};
}


