#pragma once
#include "WGameObject.h"
namespace W
{
	class PlayerArm;
	class Equip;
	class PlayerWeapon : public GameObject
	{
	public:
		PlayerWeapon();
		virtual ~PlayerWeapon();

		virtual void Initialize()override;
		virtual void Update()override;
		virtual void LateUpdate()override;
		virtual void Render()override;

		void SetPlayerArm(PlayerArm* pPlayerArm) { m_pPlayerArm = pPlayerArm; }

		void SetPlayerEquip(Equip* _pEquip);

		const std::wstring& GetCurAnimName() { return m_strCurAnim; }

		void SetStop(bool _bStop) { GetComponent<Animator>()->Stop(_bStop); }
	private:
		PlayerArm* m_pPlayerArm;

		std::wstring m_strCurAnim;
		std::wstring m_strCurEquip;
	};
	
}


