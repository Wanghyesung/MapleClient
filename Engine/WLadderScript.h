#pragma once
#include "WScript.h"

namespace W
{
	class LadderScript : public Script
	{
	public:
		LadderScript();
		virtual ~LadderScript();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void LateUpdate() override;
		virtual void Render() override;

		virtual void OnCollisionEnter(Collider2D* other);
		virtual void OnCollisionStay(Collider2D* other) ;
		virtual void OnCollisionExit(Collider2D* other) ;

		void SetUpPosition(float _fPosition) { m_fUpPosition = _fPosition; }
		void SetDownPosition(float _fPosition) { m_fDownPositioin = _fPosition; }

	private:
		float m_fUpPosition;
		float m_fDownPositioin;

	};
}


