#pragma once

#include "WUI.h"

namespace W
{
	class Scroll : public UI
	{
	public:
		Scroll();
		virtual ~Scroll();

		virtual void Initialize();
		virtual void Update();
		virtual void LateUpdate();
		virtual void Render();

		virtual void MouseOn();
		virtual void MouseLbtnDown();
		virtual void MouseLbtnUp();
		virtual void MouseLbtnClicked();

		UINT GetCurY() { return m_iCurY; }
		void SetCurY(UINT _iY) { m_iCurY = m_iCurY; }

		UINT GetMaxY() { return m_iMaxY; }
		void SetMaxY(UINT _iX) { m_iMaxY = _iX; }

		void SetEndPosition(Vector2 _vEndPos) {m_vEndPos = _vEndPos;}

		void SetParntUI(eParentUI _eParentUI) { m_eParentUI = _eParentUI; }
	private:
		void check_pos();

	private:
		UINT m_iCurY;
		UINT m_iMaxY;

		bool m_bTargetOn;
		Vector2 m_vDragStartPos;

		Vector2 m_vStartPos;
		Vector2 m_vEndPos;

		Vector2 m_vCurStartPos;
		Vector2 m_vCurEndPos;

		eParentUI m_eParentUI;
	};
}


