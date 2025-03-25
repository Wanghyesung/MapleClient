#pragma once

#include "WSKill.h"

namespace W
{
	class SkillRaidUI : public SKill
	{
	public:
		SkillRaidUI();
		virtual ~SkillRaidUI();

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

