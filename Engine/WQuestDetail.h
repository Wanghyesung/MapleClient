#pragma once
#include "WUI.h"

namespace W
{
	class QuestDetail : public UI
	{
	public:
		QuestDetail();
		virtual ~QuestDetail();

		virtual void Initialize();
		virtual void Update();
		virtual void LateUpdate();
		virtual void Render();

		virtual void MouseOn();
		virtual void MouseLbtnDown();
		virtual void MouseLbtnUp();
		virtual void MouseLbtnClicked();

	private:
		

	};
}


