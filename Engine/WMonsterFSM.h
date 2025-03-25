#pragma once
#include "WMonster.h"
#include "WMonsterState.h"

namespace W
{
	class MonsterState;

	class MonsterFSM
	{
	public:
		MonsterFSM();
		~MonsterFSM();

		void Update();
		void Initialize();

		void AddState(MonsterState* _pState);
		MonsterState* FindState(Monster::eMonsterState _eMonsterState);

		void ChangeState(Monster::eMonsterState _eMonsterState);
		void SetActiveState(Monster::eMonsterState _eMonsterState);

		MonsterState* GetActiveState() { return m_pActiveState; }

		Monster* GetMonster() { return m_pOwner; }
		void SetMonster(Monster* _pMonster) { m_pOwner = _pMonster; }

	private:
		std::map<Monster::eMonsterState, MonsterState*> m_mapState;
		MonsterState* m_pActiveState;

		Monster::eMonsterState m_eCurState;

		Monster* m_pOwner;

	};
}


