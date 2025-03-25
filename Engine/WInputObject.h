#pragma once
#include "WObject.h"
#include "WInput.h"
namespace W
{
	class InputBackground;
	class InputObject : public GameObject
	{
	public:
		InputObject(eKeyCode _eKeyCode);
		virtual ~InputObject();

		virtual void Initialize()override;
		virtual void Update()override;
		virtual void LateUpdate()override;
		virtual void Render()override;

		void SetClear(bool _bClear);
		void SetOwner(InputBackground* _pOwner) { m_pOwner = _pOwner; }
		void SetIndex(UINT _iIndex) { m_iIndex = _iIndex; }
		UINT GetIndex() { return m_iIndex; }
	private:
		void check();
		void failed();
		void clear();
	private:
		eKeyCode m_eKeyCode;
		InputBackground* m_pOwner;
		UINT m_iIndex;

		bool m_bActive;
		bool m_bRender;
	};
}


