#pragma once
#include "WMonster.h"

namespace W
{
	class Horntail;
	class HorntailWing : public Monster
	{
	public:
		HorntailWing(Horntail* _pOwner);
		virtual ~HorntailWing();

		virtual void Initialize()override;
		virtual void Update()override;
		virtual void LateUpdate()override;
		virtual void Render()override;


		void SetHeal(std::function<void()> _pFunc){ m_pHealFunc = std::move(_pFunc); }
	private:
		void setAttack();

		void summons();
		void Heal();

	private:
		Horntail* m_pOwner;

		std::function<void()> m_pHealFunc;
	};
}


