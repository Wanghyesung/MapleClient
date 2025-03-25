#pragma once
#include "WScript.h"

namespace W
{
	class PortalScript : public Script
	{
	public:
		PortalScript();
		virtual ~PortalScript();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void LateUpdate() override;
		virtual void Render() override;

		virtual void OnCollisionEnter(Collider2D* other)override;
		virtual void OnCollisionStay(Collider2D* other)override;
		virtual void OnCollisionExit(Collider2D* other)override;

		void SetNextScene(const std::wstring _strNextScene) { m_strNextScene = _strNextScene; }

	private:
		std::wstring m_strNextScene;
	};
}


