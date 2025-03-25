#pragma once
#include "WMonster.h"
namespace W
{
	class Horntail;

	class HorntailTail : public Monster
	{
	public:
		HorntailTail(Horntail* _pOwner);
		virtual ~HorntailTail();

		virtual void Initialize()override;
		virtual void Update()override;
		virtual void LateUpdate()override;
		virtual void Render()override;

	private:
		void add_skill();
		void setAttack();
		void attack();

	private:
		Horntail* m_pOwner;

	};
}


