#pragma once
#include "WUI.h"
#include "WBossUI.h"
namespace W
{
	class BossEnterUI : public UI
 	{
	public:
		BossEnterUI();
		virtual ~BossEnterUI();
		
		virtual void Initialize();
		virtual void Update();
		virtual void LateUpdate();
		virtual void Render();

		virtual void MouseOn();//UI위에 마우스 올라왔을 떄 
		virtual void MouseLbtnDown();//UI안에서 눌렸을 떄
		virtual void MouseLbtnUp();//UI안에서 땠을 때
		virtual void MouseLbtnClicked();//UI안에서 누르고 떘을 떄

	private:
		void set_nextscene(BossUI::eBossUnber _eNumber);

	private:
		std::wstring m_strNextScene;

		bool m_bDown;

		friend class BossUI;
	};
}


