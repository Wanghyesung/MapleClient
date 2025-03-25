#pragma once
#include "WMonster.h"
namespace W
{
	class MiniBean;
	class SharHP;
	class PinkBean : public Monster
	{
	public:
		enum class ePinkBeanChild
		{
			Solomon,
			Whiggin,
			Ariel,
			Munin,
			Rex,
		};

		PinkBean();
		virtual ~PinkBean();

		virtual void Initialize()override;
		virtual void Update()override;
		virtual void LateUpdate()override;
		virtual void Render()override;

		bool IsStart() { return m_bStart; }
	private:
		void update_HP();

		void create_child();

		void add_skill();

		void set_minibean();
		void setattack();

		void attack1();
		void attack2();
		void attack3();
		void attack4();
		void attack5();
		void attack6();
		void attack7();
		void attack8(); 
		void attack9();
		void attack10();
		void attack11();

		void start();

	private:
		bool m_bStart;


		SharHP* m_pSharHP;//몬스터 공유 hp
		
		std::vector<Monster*> m_vecMonster;
		std::queue< MiniBean*> m_queueMiniBean;
	};
}


