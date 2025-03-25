#pragma once
#include "WMonster.h"
namespace W
{
	class Megnus : public Monster
	{
	public:
		Megnus();
		virtual ~Megnus();

		virtual void Initialize()override;
		virtual void Update()override;
		virtual void LateUpdate()override;
		virtual void Render()override;

		void add_skill();
		void setattack();

		void attack0();
		void attack1();
		void attack2();
		void attack3();
		void attack4();
		void attack5();
		void attack6();
		void create_stone();
		void create_gas();

		void check_time();
		void check_HP();
	private:


		class MobZone* m_pZone;
		class SleepGas* m_pGas;

		float m_fGasTime;
		float m_fCurGasTime;

		float m_fCreateTime;
		float m_fCurCreateTime;

		UINT m_iCurLevel;
	};
}


