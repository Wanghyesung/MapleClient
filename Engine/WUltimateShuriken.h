#pragma once
#include "WPlayerAttackObject.h"
namespace W
{
	class UltimateShuriken : public PlayerAttackObject
	{
	public:
		//������ ������ �̹��� �ѹ�
		UltimateShuriken();
		virtual ~UltimateShuriken();

		virtual void Initialize()override;
		virtual void Update()override;
		virtual void LateUpdate()override;
		virtual void Render()override;


	};
}


