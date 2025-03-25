#pragma once
#include "WSkillNumber.h"

namespace W
{
	class SkillNumber4 : public SkillNumber
	{
	public:
		SkillNumber4();
		virtual ~SkillNumber4();

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

	};
}


