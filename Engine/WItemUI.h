#pragma once
#include "WIconUI.h"

namespace W
{
	class ItemUI : public IconUI
	{
	public:
		ItemUI();
		ItemUI(const ItemUI& _pItem);
		virtual ~ItemUI();
		
		virtual void Initialize() override;
		virtual void Update()override;
		virtual void LateUpdate()override;
		virtual void Render()override;

		virtual void MouseOn()override;
		virtual void MouseLbtnDown()override;
		virtual void MouseLbtnUp()override;
		virtual void MouseLbtnClicked()override;

		virtual ItemUI* Create_Clone()override;
		virtual void CheckPosition(int _iDir, Vector2 _vDiff)override;

		virtual void Using()override;

		void SetItemCount(UINT _iCount) { m_iItemCount = _iCount; }
		UINT GetItemCount() { return m_iItemCount; }

		void SetItemNumber();
		void AddItemNumber(UINT _iAccNumber);

		void SetFunction(std::function<void()> _func) { m_pFunction = std::move(_func); }
	private:
		bool changepos_interface();
		bool changepos_inventory();

		bool check_postion();
		bool check_inventory();
		bool check_interface();

		bool active_item();
		bool active_cash();


	protected:
		float m_fAccHP;
		float m_fAccMP;
		//hp만 회복인지 둘다 회복인지
		UINT m_iAccCount;

	private:
		UINT m_iItemCount;
		
		class Number* m_pNumber;
		Vector2 m_vNumberOffset;

		//눌렀을 때 사용되는 템 ex : 헤어
		std::function<void()> m_pFunction;
	};
}


