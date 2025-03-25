#pragma once
#include "WScript.h"

namespace W
{
	class GroundScript : public Script
	{
	public:
		GroundScript();
		virtual ~GroundScript();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void LateUpdate() override;
		virtual void Render() override;


		virtual void OnCollisionEnter(Collider2D* other)override;
		virtual void OnCollisionStay(Collider2D* other) override;
		virtual void OnCollisionExit(Collider2D* other) override;

		void SetFinalGround() { m_bFinalGround = true; }
		bool IsFinalGround() { return m_bFinalGround; }

	private:
		bool check_position(Collider2D* other);
		bool check_ladder(Collider2D* other);
	private:
		bool m_bPass;
		bool m_bFinalGround;

	};
}

