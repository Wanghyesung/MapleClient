#pragma once
#include "WGameObject.h"

namespace W
{
	class Player;

	class Shadow : public GameObject
	{
	public:
		Shadow();
		virtual ~Shadow();

		virtual void Initialize()override;
		virtual void Update()override;
		virtual void LateUpdate()override;
		virtual void Render()override;

		void Set_Attack(std::function<void()> _pFunc, float _fTime = 0.1f)
		{
			m_pFuncAttack = std::move(_pFunc);
			m_fAttackTime = _fTime;
		}

	private:
		void update_attack();
		void off();
		void set_owner(Player* _pPlayer) { m_pOwner = _pPlayer; }
		void set_active(float _fTime) 
		{
			m_bActive = true;
			m_bOff = false;
			m_fActiveTime = _fTime;
			m_fCurTime = 0.f;
		}

	private:
		Player* m_pOwner;
		std::wstring m_strCurAnim;

		float m_fActiveTime;
		float m_fCurTime;

		float m_fAttackTime;
		float m_fCurAttackTime;

		bool m_bActive;
		bool m_bOff;

		std::function<void()> m_pFuncAttack;

		friend class SkillShadow;
	};
}


