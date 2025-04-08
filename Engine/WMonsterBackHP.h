#pragma once
#include "WGameObject.h"

namespace W
{
	class MonsterHP;

	class MonsterBackHP : public GameObject
	{
	public:
		MonsterBackHP();
		virtual ~MonsterBackHP();

		virtual void Initialize() override;
		virtual void Update()override;
		virtual void LateUpdate()override;
		virtual void Render()override;

	};
}


