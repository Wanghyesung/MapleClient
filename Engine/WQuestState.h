#pragma once
#include "WUI.h"
namespace W
{
	class QuestState : public UI
	{
	public:
		QuestState();
		virtual ~QuestState();

		virtual void Initialize();
		virtual void Update();
		virtual void LateUpdate();
		virtual void Render();

		virtual void MouseOn();
		virtual void MouseLbtnDown();
		virtual void MouseLbtnUp();
		virtual void MouseLbtnClicked();

		void RenderOn(bool _bOn) { m_bRenderOn = _bOn; }
		bool IsRender() { return m_bRenderOn; }
	private:
		bool m_bRenderOn;

		bool m_bTargetOn;
		Vector2 m_vDragStartPos;

	};
}


