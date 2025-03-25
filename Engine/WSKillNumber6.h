#pragma once
#include "WSkillNumber.h"
namespace W
{
	class SkillNumber6 : public SkillNumber
	{
	public:
		SkillNumber6();
		virtual ~SkillNumber6();

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
		Vector3 m_vUltimateSkillPosition;

	};
}


