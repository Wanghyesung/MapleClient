#pragma once
#include "WScript.h"
#include "WInfo.h"

namespace W
{
	class AttackScript : public Script
	{
	public:
		struct tAttackCount
		{
			UINT iAttackCount;
			UINT iCurAttackCount;
			float fCurAttackTime;
			float fAttackTime;

			bool bAttackOn = false;
		};

		AttackScript();
		virtual ~AttackScript();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void LateUpdate() override;
		virtual void Render() override;

		virtual void OnCollisionEnter(Collider2D* other)override;
		virtual void OnCollisionStay(Collider2D* other) override;
		virtual void OnCollisionExit(Collider2D* other) override;

		void SetAccAttack() { m_iAccAttCount = 5; }
		void SetDir(int _iDir) { m_iDir = _iDir; }

		tAttackInfo& GetAttackInfo() { return m_tAttackInfo; }
		void SetAttackInfo(const tAttackInfo& _tAttackInfo) { m_tAttackInfo = _tAttackInfo; }

		void SetDeleteTime(float _fDeleteTime) { m_fCurDeleteTime = 0.f;  m_fDeleteTime = _fDeleteTime; }
		float GetCurDeleteTime() { return m_fCurDeleteTime; }
		void SetDelete() { m_fCurDeleteTime = 0.f; }

		void SetDeleteObject(bool _bDelete) { m_bDelete = _bDelete; }
		void SetStayObject(UINT _iAttackCount, float _fAttackTime);
		void SetAbleAttackCount(UINT _iCount) { m_iAbleAttackCount = _iCount; }
		bool IsAttackOn(UINT _iMonsterID);


		void Erase(UINT _iMonsterID);
		void ResetAttackCount();
	private:
		bool check_attack(UINT _iMonsterID);
		void add_attack(UINT _iMonsterID);
		bool check_time(UINT _iMonsterID);

		void create_effect(Collider2D* other);

		void off();
	private:
		/// enter
		int m_iDir;
		float m_fCurDeleteTime;
		float m_fDeleteTime;

		UINT m_iAccAttCount;
		bool m_bdead;
		bool m_bDelete;
		///

		/// stay
		float m_fAttackTime;
		UINT m_iAttackCount;
		UINT m_iAbleAttackCount;

		std::unordered_map<UINT, tAttackCount> m_hashAttack;
		///

		tAttackInfo m_tAttackInfo;

		friend class PlayerAttackObject;
	};
}

