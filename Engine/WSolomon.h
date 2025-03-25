#pragma once
#include "WMonster.h"

namespace W
{
	class Solomon : public Monster
	{
	public:
		Solomon();
		virtual ~Solomon();

		virtual void Initialize()override;
		virtual void Update()override;
		virtual void LateUpdate()override;
		virtual void Render()override;

	private:
		void add_skill();

		void setattack();
		void attack1();
		void attack2();
		void attack3();
		void faint();
		void attack_reflect();
	
	};
}


