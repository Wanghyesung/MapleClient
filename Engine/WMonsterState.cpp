#include "WMonsterState.h"

namespace W
{
	MonsterState::MonsterState()
	{

	}
	MonsterState::~MonsterState()
	{

	}
	Monster* MonsterState::GetMonster()
	{
		return m_pOwner->GetMonster();
	}
}