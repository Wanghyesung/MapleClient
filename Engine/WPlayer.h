#pragma once
#include "WGameObject.h"
namespace W
{
	class Equip;
	class Shadow;
	class Player : public GameObject
	{
	public:
		enum class ePlayerState
		{
			alert,
			jump,
			ladder,
			pronestab,
			proneattack,
			stab,
			stand,
			swing1,
			swingOF,
			walk,
			dead,
			end
		};

		enum class ePlayerSkill
		{
			luck,
			dark,
			speed,
			jump,
			aven,
			shadow,
			quad,
			raid,
			wind,
			blast,
			load,
			ultimate,
			//
			end
		};

		Player();
		virtual ~Player();

		virtual void Initialize()override;
		virtual void Update()override;
		virtual void LateUpdate()override;
		virtual void Render()override;

	private:
		int m_iDir;
	};
}


