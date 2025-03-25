#pragma once
#include "WGameObject.h"

namespace W
{
	class InputBackground : public GameObject
	{
	public:
		InputBackground();
		virtual ~InputBackground();

		virtual void Initialize() override;
		virtual void Update()override;
		virtual void LateUpdate()override;
		virtual void Render()override;

		void SetOwner(GameObject* _pObj) { m_pOwner = _pObj; }

		void Failed();
		void Next();
		UINT GetCurIndex() { return m_iCurIndex; }
		void DeleteObject(UINT _iIndex);
	private:
		void next_button();
	private:
		//성공이나 실패시 groggy오브젝트에 time 변경
		GameObject* m_pOwner;

		UINT m_iCurIndex;
		std::vector<class InputObject*> m_vecInput;
		bool m_bNext;
		
	};
}


