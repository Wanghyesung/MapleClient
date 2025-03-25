#pragma once
#include "WMonsterAttackObject.h"
namespace W
{
	class SleepGas : public MonsterAttackObject
	{
	public:
		SleepGas();
		virtual ~SleepGas();

		virtual void Initialize()override;
		virtual void Update()override;
		virtual void LateUpdate()override;
		virtual void Render()override;

	private:
		void end();
		void start();
		void off();

		std::wstring m_strCurAnim;
		tMonsterAttack m_tMonsterAttack;

		bool m_bStart;
		bool m_bEnd;

		friend class Megnus;
	};

}



