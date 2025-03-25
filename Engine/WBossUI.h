#pragma once
#include "WUI.h"
namespace W
{
	class BossUI : public UI
	{
	public:
		enum class eBossUnber
		{
			Horntail,
			PinkBean,
			Magnus,
			Demian,
			End,
		};

		BossUI();
		virtual ~BossUI();

		virtual void Initialize()override;
		virtual void Update()override;
		virtual void LateUpdate()override;
		virtual void Render()override;

		virtual void MouseOn()override;//UI위에 마우스 올라왔을 떄 
		virtual void MouseLbtnDown()override;//UI안에서 눌렸을 떄
		virtual void MouseLbtnUp()override;//UI안에서 땠을 때
		virtual void MouseLbtnClicked()override;//UI안에서 누르고 떘을 떄
	
		void SetActiveBoss(eBossUnber _eNumber);
		void SetRender(bool _bRender) { m_bRenderOn = _bRender; }
	private:
		void clear_monster();

	private:
		class BossTex* m_pBossTex;
		class BossEnterUI* m_pBossEnter;
		std::vector<class MonsterUI*>m_vecMonsterUI;

		bool m_bRenderOn;
		bool m_bTargetOn;

		Vector2 m_vDragStartPos;

		eBossUnber m_eNuber;
	};
}


