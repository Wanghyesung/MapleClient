#pragma once
#include "WMonster.h"
namespace W
{
	class DemianPhase2 : public Monster
	{
	public:
		DemianPhase2();
		virtual ~DemianPhase2();


		virtual void Initialize()override;
		virtual void Update()override;
		virtual void LateUpdate()override;
		virtual void Render()override;

	
	};
}


