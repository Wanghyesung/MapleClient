#pragma once
#include "WMonsterHP.h"

namespace W
{
	class Monster;
	class MonsterBackHP;

	class SharHP : public MonsterHP
	{
	public:
		SharHP();
		virtual ~SharHP();

		virtual void Initialize()override;
		virtual void Update()override;
		virtual void LateUpdate()override;
		virtual void Render()override;

		void SetHPValue(float _fValue) { m_fHP = _fValue; }
	private:
		float m_fHP;
		friend class MonsterManager;
	};

	
}


