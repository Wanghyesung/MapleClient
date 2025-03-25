#pragma once
#include "WMonsterFSM.h"
#include "WInfo.h"
namespace W
{
	class MonsterFSM;

	class MonsterState
	{
	public:
		MonsterState();
		~MonsterState();

		Monster::eMonsterState GetType() { return m_eMonsterState; }
		void SetType(Monster::eMonsterState  _eMonsterState) { m_eMonsterState = _eMonsterState; }

		void SetCurFrame(int _iCurFrame) { m_iCurFrame = _iCurFrame; }
		int GetCurFrame() { return m_iCurFrame; }
		void InitZeroFrame() { m_iCurFrame = 0; }

		virtual void Update() = 0;
		virtual void Enter() = 0;
		virtual void Exit() = 0;

		Monster* GetMonster();

		MonsterFSM* GetFSM() { return m_pOwner; }
		void SetFSM(MonsterFSM* _pFSM) { m_pOwner = _pFSM; }

		void SetStateName(const std::wstring _strName) { m_strStateName = _strName; }
		const std::wstring GetStateName() { return m_strStateName; }

	private:
		Monster::eMonsterState m_eMonsterState;
		MonsterFSM* m_pOwner;

		std::wstring m_strStateName;

		int m_iCurFrame;

	};
}


