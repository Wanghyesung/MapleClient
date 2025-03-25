#pragma once
#include "WGameObject.h"
#include "WResources.h"
namespace W
{
	class UI : public GameObject
	{
	public:
		UI();
		UI(const UI& _pOrigin);
		virtual ~UI();

		virtual void Initialize();
		virtual void Update();
		virtual void LateUpdate();
		virtual void Render();

		virtual void MouseOn();//UI위에 마우스 올라왔을 떄 
		virtual void MouseLbtnDown();//UI안에서 눌렸을 떄
		virtual void MouseLbtnUp();//UI안에서 땠을 때
		virtual void MouseLbtnClicked();//UI안에서 누르고 떘을 떄

		UI* GetParentUI() { return m_pParentUI; }
		void AddChildUI(UI* _pUI, bool _bMove = true);

		//내 벡터에만 지우기
		void DeleteChildUI(UI* _pUI);

		void MoveUI(UI* _pUI);
		void MoveToParent(Vector2 _vDiff);

		bool IsLBntDown() { return m_bLbntDown; }
		bool IsMosueOn() { return m_bMouseOn; }

		//private -> public
		void MouseOnCheck();

		const std::vector<UI*> GetChildUI() { return m_vecChildUI; }

	private:
		//자식 UI 업데이트
		void ChildUpdate();
		void ChildRender();
		void ChildLateupdate();

		//void MoveToParent();

	private:
		//내 자식 UI
		std::vector<UI*> m_vecChildUI;
		//내 부모 UI
		UI* m_pParentUI;

		bool m_bMouseOn;
		bool m_bLbntDown;

		friend class UIManger;
	};

}

