#pragma once
#include "WUI.h"
#include "WBossUI.h"
namespace W
{
	class MonsterUI : public UI
	{
	public:
		MonsterUI();
		virtual ~MonsterUI();

		virtual void Initialize();
		virtual void Update();
		virtual void LateUpdate();
		virtual void Render();

		virtual void MouseOn();//UI위에 마우스 올라왔을 떄 
		virtual void MouseLbtnDown();//UI안에서 눌렸을 떄
		virtual void MouseLbtnUp();//UI안에서 땠을 때
		virtual void MouseLbtnClicked();//UI안에서 누르고 떘을 떄

		BossUI::eBossUnber GetBossNumber() { return m_eBossNumber; }
	private:
		void set_bossnumber(BossUI::eBossUnber _eNumber);
		void clear();
	private:
		static UINT COUNT;
		UINT m_iCount;

		bool m_bSelete;
		BossUI::eBossUnber m_eBossNumber;

		friend class BossUI;
	};
}


