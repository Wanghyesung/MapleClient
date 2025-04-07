#pragma once

#include "WGameObject.h"
#include "WMonsterAttackObject.h"
#include "WObjectPoolManager.h"

namespace W
{
	class Monster : public GameObject
	{
	public:
		
		Monster();
		virtual ~Monster();

		virtual void Initialize()override;
		virtual void Update()override;
		virtual void LateUpdate()override;
		virtual void Render()override;

	private:
		int m_iDir;
	};
}


