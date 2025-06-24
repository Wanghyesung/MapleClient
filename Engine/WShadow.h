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

		void SetOwner(Player* _pPlayer) { m_pOwner = _pPlayer; }
		void Off();
		void On();
		
		bool IsActiveOffAnimation() {return m_bOff;}
	private:
		void inactive_shadow();

	private:
		Player* m_pOwner;
		
		bool m_bOff;
		friend class SkillShadow;
	};
}


