#pragma once
#include "WScript.h"

namespace W
{
	class StoneScript : public Script
	{
	public:
		StoneScript();
		virtual ~StoneScript();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void LateUpdate() override;
		virtual void Render() override;

		virtual void OnCollisionEnter(Collider2D* other)override;
		virtual void OnCollisionStay(Collider2D* other)override;
		virtual void OnCollisionExit(Collider2D* other)override;

		void SetFunction(std::function<void()> _func) { m_pFunction = std::move(_func); }

	private:
		std::function<void()> m_pFunction;
	};
}


