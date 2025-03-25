#pragma once
#include "WSKill.h"

namespace W
{
	class SkillQSUI : public SKill
	{
	public:
		SkillQSUI();
		virtual ~SkillQSUI();

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


