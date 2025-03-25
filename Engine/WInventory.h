#pragma once

#include "WUI.h"
#include "WIconUI.h"

namespace W
{
	class InvenPage;
	class Scroll;

	class Inventory : public UI
	{
	public:
		enum class eItemPage
		{
			Equip,
			Item,
			None,
			Install,
			Cash,
			End,
		};

		Inventory();
		virtual ~Inventory();

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

		IconUI* FindItem(std::wstring _strName);
		void InsertItem(IconUI* _pItem, std::wstring _strName);
		void AddItem(IconUI* _pItem, std::wstring _strName);
		void DeleteItem(IconUI* _pItem) { m_mapItems.erase(_pItem->GetName()); }

		bool SetItemPosition(IconUI* _pItem);
		bool ChangeItemPosition(IconUI* _pItem , Vector2 _vSetPosition);
		IconUI* FindItemOnPosition(UINT _iX, UINT _iY, IconUI* _pIcon);

		Vector2 GetStartPosition() { return m_vUIStartPosition; }
		Vector2 GetEndPosition() { return m_vUIEndPosition; }
		Vector2 GetDiffPosition() { return m_vUIDiffPosition; }

		eItemPage GetActivePage() { return m_eActivePage; }
		void SetActivePage(eItemPage _ePageType); 

		bool IsActivePage(UINT _i);

		void CheckPosition(int _iDir);
		UINT GetScrollCurY() { return m_iScrollCurY; }
		void SetScrollCurY(UINT _iY) {m_iScrollCurY = _iY;};

	private:
		Scroll* m_pScroll;
		UINT    m_iScrollCurY;

		eItemPage m_eActivePage;

		bool m_bRenderOn;

		std::map<std::wstring, IconUI*> m_mapItems;

		std::vector<InvenPage*> m_vecPages;

		bool m_bTargetOn;

		Vector2 m_vDragStartPos;

		Vector2 m_vUIStartPosition;
		Vector2 m_vUIEndPosition;
		Vector2 m_vUIDiffPosition;
	};

}

