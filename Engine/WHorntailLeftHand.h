#pragma once
#include "WMonster.h"
namespace W
{
	class Horntail;
	class HorntailLeftHand : public Monster
	{
	public:
		HorntailLeftHand(Horntail* _pOwner);
		virtual ~HorntailLeftHand();

		virtual void Initialize()override;
		virtual void Update()override;
		virtual void LateUpdate()override;
		virtual void Render()override;


		void SetBuff(std::function<void()> _func) { m_pBuffFunc = std::move(_func); }
	private:
		void add_skill();
		void setAttack();

		void create_spear();
		void temptation();
		void buff_defnes();

	private:
		Horntail* m_pOwner;

		std::function<void()> m_pBuffFunc;
	};
}

