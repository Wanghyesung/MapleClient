#pragma once

#include "WGameObject.h"

namespace W
{
	class PlayerHead;
	class Equip;
	class PlayerHat : public GameObject
	{
	public:
		PlayerHat();
		virtual ~PlayerHat();

		virtual void Initialize()override;
		virtual void Update()override;
		virtual void LateUpdate()override;
		virtual void Render()override;

		void SetPlayerHead(PlayerHead* _pPlayerHead) { m_pPlayerHead = _pPlayerHead; }

		void SetPlayerEquip(Equip* _pEquip);

		const std::wstring& GetCurAnimName() { return m_strCurAnim; }

		void SetStop(bool _bStop) { GetComponent<Animator>()->Stop(_bStop); }

	private:
		PlayerHead* m_pPlayerHead;

		std::wstring m_strCurAnim;
		std::wstring m_strCurEquip;


	};
}
	

