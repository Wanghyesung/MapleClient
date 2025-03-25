#pragma once
#include "WSKill.h"

namespace W
{
	class SkillDarkUI : public SKill
	{
	public:
		SkillDarkUI();
		virtual ~SkillDarkUI();

		virtual void Initialize();
		virtual void Update();
		virtual void LateUpdate();
		virtual void Render();

		virtual void MouseOn();
		virtual void MouseLbtnDown();
		virtual void MouseLbtnUp();
		virtual void MouseLbtnClicked();
		
		virtual void Using();

	private:
	};
}