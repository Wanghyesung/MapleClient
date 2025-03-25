#pragma once
#include "WScript.h"
#include "WInfo.h"

namespace W
{
	class MonsterFSM;
	class MonsterHP;
	class MonsterScript : public Script
	{
	public:
		MonsterScript();
		virtual ~MonsterScript();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void LateUpdate() override;
		virtual void Render() override;

		virtual void OnCollisionEnter(Collider2D* other)override;
		virtual void OnCollisionStay(Collider2D* other)override;
		virtual void OnCollisionExit(Collider2D* other)override;

		MonsterHP* GetMonsterHP() { return m_pHP; }

		void SetHitInfo(const tHitInfo& _tHitInfo) { m_tHitInfo = _tHitInfo; }
		const tHitInfo& GetHitInfo() { return m_tHitInfo; }

		void SetObjectInfo(const tObjectInfo& tObjectInfo) { m_tObjectInfo = tObjectInfo; }
		const tObjectInfo& GetObjectInfo() { return m_tObjectInfo; }

		void SetAttackInfo(const tAttackInfo& _tAttackInfo) { m_tMonsterInfo.tAttackInfo = _tAttackInfo; }
		const tAttackInfo& GetAttackInfo() { return  m_tMonsterInfo.tAttackInfo; }

		//스킬 바로 활성화
		void AciveAttack(UINT _iINdex);
		void AddAttack(const tMonsterAttack& _tMonsterAttack);
		const tMonsterAttack& GetCurMonsterAttack() { return m_vecAttacks[m_iCurAttackCount]; }

		//현재 사용할 스킬 지정
		void SetMonsterAttack(MonsterAttackObject* _pAttackObject) { m_pAttackObject = _pAttackObject; }
		MonsterAttackObject* GetMonsterAttack() { return m_pAttackObject; }

		void SetSpeed(float _pSpeed) { m_tObjectInfo.fSpeed = _pSpeed; }
		void SetHP(float _fHP) { m_tObjectInfo.fMaxHP = _fHP; m_tObjectInfo.fHP = _fHP; }
		UINT GetAttackNumber() { return m_iCurAttackCount; }

		void SetActiveAttack();
		void DeleteActiveAttack();

		Monster* GetMonster() { return m_pMonster; }
		void SetFSM(MonsterFSM* _pFSM) { m_pFSM = _pFSM; }

		void CreateHP();
		void SetBoss() { m_bBoss = true; }
		bool IsBoss() { return m_bBoss; }
	private:
		void hit(const tAttackInfo& _tAttackInfo, GameObject* _pAttackObj);
		void update_cooltime();

		void reflex(const tAttackInfo& _tAttackInfo, GameObject* _pAttackObj);

	private:
		MonsterAttackObject* m_pAttackObject;
		GameObject* m_pHitEffect;

		MonsterFSM* m_pFSM;
		
		tHitInfo m_tHitInfo;
		tMonsterAttack m_tMonsterInfo;
		tObjectInfo m_tObjectInfo;

		std::vector<tMonsterAttack> m_vecAttacks;
		UINT m_iCurAttackCount;

		MonsterHP* m_pHP;
		Monster* m_pMonster;
		//보스, 공반
		bool m_bBoss;
		bool m_bReflex;

		//hp공유 몬스터
		friend class Horntail;
		//매니저
		friend class BattleManager;
		friend class MonsterManager;
	};
}

