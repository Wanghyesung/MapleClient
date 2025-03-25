#pragma once
#include "WSkillNumber.h"

namespace W
{
	class SkillNumber3 : public SkillNumber
	{
	public:
		SkillNumber3();
		virtual ~SkillNumber3();

		virtual void Initialize();
		virtual void Update();
		virtual void LateUpdate();
		virtual void Render();

		virtual void MouseOn();
		virtual void MouseLbtnDown();
		virtual void MouseLbtnUp();
		virtual void MouseLbtnClicked();

		class SKill* CreateClone(class SKill* _pSkill);

	private:
		Vector3 m_vAvenSkillPosition;
		Vector3 m_vShadowSkillPosition;
	};
}


