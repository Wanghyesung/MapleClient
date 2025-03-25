#pragma once
#include "WUI.h"
#include "WSkillNumber.h"
namespace W
{
	class SkillNumber2 : public SkillNumber
	{
	public:
		SkillNumber2();
		virtual ~SkillNumber2();

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
		Vector3 m_vJumpSkillPosition;
		Vector3 m_vSpeedSkillPosition;

	};
}

