#pragma once

#include "WGameObject.h"
#include "WPlayer.h"

namespace W
{
	class PlayerHead;
	class Eyes : public GameObject
	{
	public:
		Eyes();
		virtual ~Eyes();

		virtual void Initialize()override;
		virtual void Update()override;
		virtual void LateUpdate()override;
		virtual void Render()override;

		void SetPlayerHead(PlayerHead* _pPlayerHead) { m_pPlayerHead = _pPlayerHead; }

		void SetEye(UINT _iNum);

	private:
		PlayerHead* m_pPlayerHead;

		UINT m_iEyeNumber;
		std::wstring m_strCurAnim;

	};
}


