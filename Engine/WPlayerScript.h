#pragma once

#include "WScript.h"
#include "WPlayer.h"
#include "WInfo.h"

namespace W
{
	class Player;
	class PlayerFSM;
	class PlayerSkill;
	class PlayerAttackObject;
	class PlayerScript : public Script
	{
	public:
		PlayerScript();
		virtual ~PlayerScript();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void LateUpdate() override;
		virtual void Render() override;

		virtual void OnCollisionEnter(Collider2D* other)override;
		virtual void OnCollisionStay(Collider2D* other)override;
		virtual void OnCollisionExit(Collider2D* other)override;

		void ActiveJump();

		bool IsAttack() { return m_bAttack; }
		void SetAttack(bool _bActive) { m_bAttack = _bActive; }

		bool IsStab() { return m_bStab; }
		void SetStab(bool _bActive) { m_bStab = _bActive; }

		bool IsLadder() { return m_bLadder; }
		void SetLadder(bool _bLadder) { m_bLadder = _bLadder; }

		const std::wstring& GetCurStateName();

		void MinusAttackCnt();
		void SetAccAttack() { m_fCurAccTime = 0.f; m_iAccAttCnt = 20; }
		bool IsAccAttack() { return m_fAccAttackTime > m_fCurAccTime ? true : false; }

		bool IsHit() { return m_fHitTime >= 2.f ? false : true; }
		bool IsAbnormal() { return m_bAbnormal; }
		bool IsSealSkill() { return m_bSealSkill; }
		bool IskNockBack() { return m_bSuperKnockback; }

		bool IsOnGround() { return m_bOnGround; }
		void SetOnGround(bool _bOn) { m_bOnGround = _bOn; }

		void SetHitInfo(const tHitInfo& _tHitInfo) { m_tHitInfo = _tHitInfo; }
		void SetAttackInfo(const tAttackInfo& _tAttackInfo) { m_tAttackInfo = _tAttackInfo; }

		const tHitInfo& GetHitInfo() { return m_tHitInfo; }
		const tAttackInfo& GetAttackInfo() { return m_tAttackInfo; }
		const tObjectInfo& GetObjectInfo() { return m_tObjectInfo; }

		void Hit(const tAttackInfo& _tAttackInfo, std::wstring _strAttackName);

		void SetActiveState(Player::ePlayerState _eState);

		class Shuriken* CreateShuriken();
		class PlayerAttackObject* CreateAttackObject();

		void AddPlayerSkill(PlayerAttackObject* _pObj);
		PlayerAttackObject* GetPlayerSkill(const std::wstring& _strName);

	private:
		void add_skill();
		void check_time();
		void super_knockback(float _fTime);
		void knockback();

	private:
		bool m_bLadder;
		bool m_bStab;
		bool m_bAttack;
		bool m_bOnGround;
		
		UINT m_iAccAttCnt;
		float m_fCurAccTime;
		float m_fAccAttackTime;

		//상태이상
		bool m_bAbnormal;
		bool m_bSuperKnockback;
		bool m_bSealSkill;

		float m_fHitTime;
		float m_fknockbackTime;

		tHitInfo m_tHitInfo;
		tAttackInfo m_tAttackInfo;
		tObjectInfo m_tObjectInfo;

		Player* m_pPlayer;
		PlayerFSM* m_pFSM;
		PlayerSkill* m_pSkill;

		
		//std::map <std::wstring, std::queue<PlayerAttackObject*>> m_mapAttackObjs;


		friend class EventManager;
		friend class BattleManager;
	};
}

