#pragma once

#include "WUI.h"

namespace W
{
	class QuestUI : public UI
	{
	public:
		QuestUI();
		virtual ~QuestUI();

		virtual void Initialize() override;
		virtual void Update()override;
		virtual void LateUpdate()override;
		virtual void Render()override;

		virtual void MouseOn()override;
		virtual void MouseLbtnDown()override;
		virtual void MouseLbtnUp()override;
		virtual void MouseLbtnClicked()override;

	private:
		
	};
}


