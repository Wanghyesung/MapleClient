#pragma once
#include "WMonster.h"
namespace W
{
	class Horntail : public Monster
	{
	public:
		enum class eHorntailChild
		{
			HorntailHeadA,
			HorntailHeadB,
			HorntailHeadC,
			HorntailLeftHand,
			HorntailRightHand,
			HorntailLeg,
			HorntailTail,
			HorntailWing,
		};

		Horntail();
		virtual ~Horntail();

		virtual void Initialize()override;
		virtual void Update()override;
		virtual void LateUpdate()override;
		virtual void Render()override;
		virtual void UpdateState(const wstring& _strStateName, int _iState) override;

		std::vector<Monster*> m_vecMonster;
	};
}


