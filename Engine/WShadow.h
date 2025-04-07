#pragma once
#include "WGameObject.h"

namespace W
{
	class Player;

	class Shadow : public GameObject
	{
	public:
		Shadow();
		virtual ~Shadow();

		virtual void Initialize()override;
		virtual void Update()override;
		virtual void LateUpdate()override;
		virtual void Render()override;

		
		friend class SkillShadow;
	};
}


