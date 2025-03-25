#pragma once
#include "WUI.h"
#include "WInventory.h"

namespace W
{
	class InvenPage : public UI
	{
	public:
		InvenPage(Inventory::eItemPage _ePageType);
		virtual ~InvenPage();

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

		void SetPageType(Inventory::eItemPage _ePageType) { m_ePageType = _ePageType; }
		Inventory::eItemPage GetPageType() { return m_ePageType; }

		void SetActive(bool _bOn);
		bool IsActive() { return m_bActive; }

		

	private:
		bool m_bRenderOn;
		bool m_bActive;

		Inventory::eItemPage m_ePageType;

		Inventory* m_pParentInventory;
	};
}


