#pragma once
#include "WMonster.h"
namespace W
{
	class DemianPhase2 : public Monster
	{
	public:
		DemianPhase2();
		virtual ~DemianPhase2();


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
		void attack4();
		void attack5();

		void check_HP();


		//데미안 환영
		void create_spear0();
		void create_spear1();

		void set_effect();
		//void teleport();
		void move();

	private:
		//세계수 카운트
		UINT m_iAttackCallCount;
		bool m_bGroggy;
		int m_iSpearCount;

		//구 레벨
		int m_iCircleLevel;

		std::vector<class DemianCircle*> m_vecCircle;
	};
}


