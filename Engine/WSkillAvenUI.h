#pragma once
#include "WSKill.h"

namespace W
{
	class SkillAvenUI : public SKill
	{
	public:
		SkillAvenUI();
		virtual ~SkillAvenUI();

		virtual void Initialize()override;
		virtual void Update()override;
		virtual void LateUpdate()override;
		virtual void Render()override;

		virtual void MouseOn()override;
		virtual void MouseLbtnDown()override;
		virtual void MouseLbtnUp()override;
		virtual void MouseLbtnClicked()override;

		virtual void Using()override;

	private:

	};
}


