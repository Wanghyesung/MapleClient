#pragma once
#include "WGameObject.h"
#include "WAudioClip.h"
namespace W
{
	class Player;
	class Effect;
	class PlayerAttackObject : public GameObject
	{
	public:
		PlayerAttackObject();
		virtual ~PlayerAttackObject();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void LateUpdate() override;
		virtual void Render() override;

	};
}


