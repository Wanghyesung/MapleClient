#pragma once
#include "WMonster.h"
namespace W
{
	class Horntail;

	class HorntailTail : public Monster
	{
	public:
		HorntailTail();
		virtual ~HorntailTail();

		virtual void Initialize()override;
		virtual void Update()override;
		virtual void LateUpdate()override;
		virtual void Render()override;

	};
}


