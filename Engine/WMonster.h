#pragma once

#include "WGameObject.h"
#include "WInfo.h"
#include "WMonsterAttackObject.h"
#include "WObjectPoolManager.h"

namespace W
{
	class Monster : public GameObject
	{
	public:
		enum class eMonsterState
		{
			stand,
			wait,
			start,
			move,
			attack,
			dead,
			hit,
			end,
		};

		Monster();
		virtual ~Monster();

		virtual void Initialize()override;
		virtual void Update()override;
		virtual void LateUpdate()override;
		virtual void Render()override;


		const std::wstring& GetCurStateName() { return m_strCurStateName; }
		void SetCurStateName(const std::wstring& _strName) { m_strCurStateName = _strName; }

		void SetMonsterCurState(eMonsterState _eState){m_eMonsterState = _eState;}
		eMonsterState GetCurMonsterState() { return m_eMonsterState; }

		void SetMonsterAnim(const std::wstring& _strName) { m_strCurAnim = _strName; }
		const std::wstring& GetMonsterAnim() { return m_strCurAnim; }

		void SetDir(int _iDir) { m_iDir = _iDir; }
		int GetDir() { return m_iDir; }

		bool IsDead() { return m_bDead; }
		void SetDead(bool _bDead) { m_bDead = _bDead; }

		void SetItem(const std::vector<std::wstring>& _vecItemNames);
		const std::vector<std::wstring>& GetItemVec() { return m_vecItemNames; }

		const UINT GetCreateCount() { return m_iCreateCount; }
		void SetCreateCount(UINT _iCount) { m_iCreateCount = _iCount; }

		void AddMonsterSkill(MonsterAttackObject* _pObj);
		MonsterAttackObject* GetMonsterSkill(const std::wstring& _strName);

	private:
		int m_iDir;
		
		bool m_bDead;
		eMonsterState m_eMonsterState;

		std::wstring m_strCurStateName;
		std::wstring m_strCurAnim;
		
		//죽으면 나올 아이템들
		UINT m_iCreateCount;
		std::vector<std::wstring> m_vecItemNames;

		//사용할 스킬들
		//std::map < std::wstring, std::queue<MonsterAttackObject*>> m_mapAttackObjs;

		friend class MonsterManager;
	};
}


