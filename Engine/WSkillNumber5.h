#pragma once
#include "WSkillNumber.h"

namespace W
{
	class SkillNumber5 : public SkillNumber
	{
	public:
		SkillNumber5();
		virtual ~SkillNumber5();

		virtual void Initialize();
		virtual void Update();
		virtual void LateUpdate();
		virtual void Render();

		virtual void MouseOn()override;
		virtual void MouseLbtnDown()override;
		virtual void MouseLbtnUp()override;
		virtual void MouseLbtnClicked()override;

		class SKill* CreateClone(class SKill* _pSkill);

	private:
		Vector3 m_vQSSkillPosition;
		Vector3 m_vRadeSkillPosition;
		Vector3 m_vWindSkillPosition;
	
	};
}