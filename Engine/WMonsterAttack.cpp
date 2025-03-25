#include "WMonsterAttack.h"
#include "WMonsterScript.h"
#include "WAnimator.h"

namespace W
{
	MonsterAttack::MonsterAttack() :
		m_iCallTime(0)
	{
		SetType(Monster::eMonsterState::attack);
		SetStateName(L"_attack");
	}
	MonsterAttack::~MonsterAttack()
	{

	}
	void MonsterAttack::Update()
	{
		Animation* pAnim = GetMonster()->GetComponent<Animator>()->GetActiveAnimation();
		if (pAnim == nullptr)
			return;

		MonsterScript* pScript = GetMonster()->GetScript<MonsterScript>();
		int iIndex = pAnim->GetCurIndex();

		if (m_iCallTime == 0 &&
			(m_tMonsterAttack.iStartFrame <= iIndex &&
			 iIndex <= m_tMonsterAttack.iEndFrame))
		{
			pScript->SetActiveAttack();
			m_iCallTime = 1;
		}
		else if(m_iCallTime == 1 &&
			iIndex > m_tMonsterAttack.iEndFrame)
		{
			pScript->DeleteActiveAttack();
			m_iCallTime = 2;
		}
		
		if (pAnim->IsComplete())
			GetFSM()->ChangeState(Monster::eMonsterState::stand);
	}
	void MonsterAttack::Enter()
	{
		MonsterScript* pScript = GetMonster()->GetScript<MonsterScript>();
		m_tMonsterAttack = pScript->GetCurMonsterAttack();
		m_iCallTime = 0;
	}
	void MonsterAttack::Exit()
	{
		if(m_iCallTime == 1)
			GetMonster()->GetScript<MonsterScript>()->DeleteActiveAttack();
	}
}