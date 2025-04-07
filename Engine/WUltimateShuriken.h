#pragma once
#include "WPlayerAttackObject.h"
namespace W
{
	class UltimateShuriken : public PlayerAttackObject
	{
	public:
		//가져올 수리검 이미지 넘버
		UltimateShuriken();
		virtual ~UltimateShuriken();

		virtual void Initialize()override;
		virtual void Update()override;
		virtual void LateUpdate()override;
		virtual void Render()override;


	};
}


