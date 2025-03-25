#pragma once
#include "WUI.h"

namespace W
{
	class Scene;

	class UIManger
	{
	public:
		static void Update();
		static void SetFoucseUI(UI* _pUI);
		static void MoveFrontChildUI(UI* pUI);

		static UI* GetFoucseUI();
		static UI* GetTargetUI(UI* _pParentUI);
		static void ReleaseChildUI();


	private:
		static UI* m_pFoucseUI;
	};
}


