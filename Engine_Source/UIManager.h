#pragma once
#include "WUI.h"

namespace W
{
	class Scene;

	class UIManager
	{
	public:
		static void Update();

		static void LateUpdate();

		static void MoveFrontChildUI(UI* pUI);

		static UI* GetFoucseUI();
		static UI* GetTargetUI(UI* _pParentUI);
		static void SetLateRenderUI();

	private:
		static void ReleaseChildUI();
		static void TargetUIDraw();

	private:
		static UI* m_pFoucseUI;
		static UI* m_pTargetUI;

		static UI* m_pLateRenderUI;
	};
}


