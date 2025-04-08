#pragma once
#include "WGameObject.h"

namespace W
{
	class Monster;
	class MonsterBackHP;

	class MonsterHP : public GameObject
	{
	public:
		MonsterHP();
		virtual ~MonsterHP();

		virtual void Initialize()override;
		virtual void Update()override;
		virtual void LateUpdate()override;
		virtual void Render()override;


	private:
		UINT m_iHPCount;
		static UINT HP_COUNT;

		float m_fHP;
		bool m_bBoss;

		friend class MonsterManager;
	};
}


