#pragma once
#include "WGameObject.h"
#include "WPlayer.h"

namespace W
{
	class PlayerHead;
	class PlayerHair : public GameObject
	{
	public:
		PlayerHair();
		virtual ~PlayerHair();

		virtual void Initialize()override;
		virtual void Update()override;
		virtual void LateUpdate()override;
		virtual void Render()override;

		void SetPlayerHead(PlayerHead* _pPlayerHead) { m_pPlayerHead = _pPlayerHead; }

		const std::wstring& GetCurAnimName() { return m_strCurAnim; }

		void SetHairDown(bool _bDown) { m_bHairDown = _bDown; }

		void SetStop(bool _bStop) { GetComponent<Animator>()->Stop(_bStop); }
		void SetHair(UINT _iNum);
	private:
		PlayerHead* m_pPlayerHead;

		std::wstring m_strCurAnim;
		//헤어 tex 넘버
		UINT m_iHairNum;

		bool m_bHairDown;

	};
}


