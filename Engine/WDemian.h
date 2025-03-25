#pragma once
#include "WMonster.h"

namespace W
{
	class DemianSword;
	class Demian : public Monster
	{
	public:
		Demian();
		virtual ~Demian();

		virtual void Initialize()override;
		virtual void Update()override;
		virtual void LateUpdate()override;
		virtual void Render()override;

	private:
		void add_skill();
		void setattack();

		void attack0();
		void attack1();
		void attack2();
		void attack3();
	
		void move();

		void check_time();
		//키입력 공격
		void create();
	private:
		float m_fCreateTime;
		float m_fCurCreateTime;
	};
}


