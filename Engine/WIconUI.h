#pragma once
#include "WUI.h"
#include "WInput.h"

namespace W
{
	class IconUI : public UI
	{
	public:
		//eItemPage 와 순서 같게
		enum class eIconType
		{
			Equip,
			Item,
			None,
			Install,
			Cash,
			SKill,
			End,
		};

		IconUI();
		IconUI(const IconUI& _pIcon);
		virtual ~IconUI();

		virtual void Initialize() override;
		virtual void Update()override;
		virtual void LateUpdate()override;
		virtual void Render()override;

		virtual void MouseOn()override;
		virtual void MouseLbtnDown()override;
		virtual void MouseLbtnUp()override;
		virtual void MouseLbtnClicked()override;

		virtual void CheckPosition(int _iDir, Vector2 _vDiff) {}

		virtual void Using() {};
		virtual IconUI* Create_Clone() { return nullptr; }

		void SetIconType(eIconType _eType) { m_eType = _eType; }
		eIconType GetIconType() { return m_eType; }

		void SetParentUIType(eParentUI _eType) { m_ePrevParentType = m_eParentType; m_eParentType = _eType; }
		eParentUI GetParentUIType() { return m_eParentType; }

		void SetItemIndex(int _iX, int _iY)
		{
			m_iPrevIndexX = m_iItemIndexX; m_iPrevIndexY = m_iItemIndexY;
			m_iItemIndexX = _iX; m_iItemIndexY = _iY;
		}
		void SetKeyCode(eKeyCode _eCode) { m_eKeyCode = _eCode; }

		int GetItemindexX() { return m_iItemIndexX; }
		int GetItemIndexY() { return m_iItemIndexY; }

		int GetPrevItemindexX() { return m_iPrevIndexX; }
		int GetPrevItemIndexY() { return m_iPrevIndexY; }

		Vector3 GetStartPosition() { return m_vStartPos; }
		Vector2 GetDragStartPos() { return m_vDragStartPos; }
		void DeleteParent();

	private:
		void check_doubleclick();

	private:
		eIconType m_eType;

		bool m_bTargetOn;

		eParentUI m_eParentType;
		eParentUI m_ePrevParentType;
		
		//인터페이스 내 아이템 위치
		eKeyCode m_eKeyCode;

		Vector2 m_vDragStartPos;
		Vector2 m_vDragEndPos;
		Vector3 m_vStartPos;

		int m_iItemIndexX;
		int m_iItemIndexY;

		int m_iPrevIndexX;
		int m_iPrevIndexY;

		int m_iClickCount;
		float m_fDoubleClickTime;
		float m_fCurClickTime;
	};
}


