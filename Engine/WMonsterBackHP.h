#pragma once
#include "WGameObject.h"

namespace W
{
	class MonsterHP;

	class MonsterBackHP : public GameObject
	{
	public:
		MonsterBackHP(bool _bBoss);
		virtual ~MonsterBackHP();

		virtual void Initialize() override;
		virtual void Update()override;
		virtual void LateUpdate()override;
		virtual void Render()override;

	};
}


