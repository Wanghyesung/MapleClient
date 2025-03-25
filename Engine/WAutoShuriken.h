#pragma once
#include "WPlayerAttackObject.h"

namespace W
{
	class Monster;
	class AutoShuriken : public PlayerAttackObject
	{
	public:
		AutoShuriken();
		virtual ~AutoShuriken();

		virtual void Initialize()override;
		virtual void Update()override;
		virtual void LateUpdate()override;
		virtual void Render()override;

		void SetVelocity(const Vector2& _vVel) { m_vVelocity= _vVel; }
		void SetDir(const Vector2& _vDir);

		virtual void Off()override;
	private:
		bool set_target();
		void move_target();
		
		void move();
		void rotate();
		const Vector2& get_dir();
		

	private:
		Monster* m_pTarget;

		int m_iDir;

		float m_fDeleteTime;
		float m_fCurTime;
		const float m_fContFoce;

		Vector2 m_vForce;
		Vector2 m_vVelocity;
		Vector2 m_vDir;
		Vector2 m_vMaxVelocity;
	};
}


