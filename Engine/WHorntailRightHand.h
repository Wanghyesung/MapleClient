#pragma once
#include "WMonster.h"

namespace W
{
	class Horntail;
	class HorntailRightHand : public Monster
	{
	public:
		HorntailRightHand(Horntail* _pOwner);
		virtual ~HorntailRightHand();

		virtual void Initialize()override;
		virtual void Update()override;
		virtual void LateUpdate()override;
		virtual void Render()override;

		void SetBuff(std::function<void()> _func) { m_pBuffFunc = std::move(_func); }
	private:
		void add_skill();
		void setAttack();

		void create_spear();
		void seal_skill();
		void buff_attack();
	private:
		Horntail* m_pOwner;

		std::function<void()> m_pBuffFunc;
	};
}


