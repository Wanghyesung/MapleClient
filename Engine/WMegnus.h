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

	
	};
}


