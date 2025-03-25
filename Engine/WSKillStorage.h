#pragma once

#include "WUI.h"
namespace W
{
	class SkillNumber;

	class SKillStorage : public UI
	{
	public:
		enum class eSkillNuber
		{
			First,
			Second,
			Third,
			Four,
			Five,
			Six,
			None,
		};

		SKillStorage();
		virtual ~SKillStorage();

		virtual void Initialize() override;
		virtual void Update()override;
		virtual void LateUpdate()override;
		virtual void Render()override;

		virtual void MouseOn()override;
		virtual void MouseLbtnDown()override;
		virtual void MouseLbtnUp()override;
		virtual void MouseLbtnClicked()override;

		void RenderOn(bool _bOn) { m_bRenderOn = _bOn; }
		bool IsRender() { return m_bRenderOn; }

		void SetActiveNumber(eSkillNuber _eSkillNumber);

	private:
		std::vector<SkillNumber*> m_vecSkillNumber;

		bool m_bRenderOn;
		bool m_bTargetOn;

		Vector2 m_vDragStartPos;

		Vector2 m_vUIStartPosition;
		Vector2 m_vUIEndPosition;
		Vector2 m_vUIDiffPosition;


	};
}


