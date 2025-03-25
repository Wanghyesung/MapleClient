#pragma once
#include "WMonster.h"

namespace W
{
	
	class Whiggin : public Monster
	{
	public:
		Whiggin();
		virtual ~Whiggin();

		virtual void Initialize()override;
		virtual void Update()override;
		virtual void LateUpdate()override;
		virtual void Render()override;

	private:
		void add_skill();

		void setattack();
		void attack1();
		void attack2();

		void dark();
		void attack_reflect();

	};


}


