#include "WMonsterDead.h"
#include "WAnimator.h"
#include "WObject.h"
#include "WEventManager.h"
#include "WMonsterManager.h"
#include "WMonsterFSM.h"
#include "WMonsterScript.h"
namespace W
{
	MonsterDead::MonsterDead():
		m_iCount(0)
	{
		SetType(Monster::eMonsterState::dead);
		SetStateName(L"_dead");
	}
	MonsterDead::~MonsterDead()
	{

	}
	void MonsterDead::Update()
	{
		Monster* pMonster = GetMonster();
		Animation* pAnim = pMonster->GetComponent<Animator>()->GetActiveAnimation();
		if (pAnim->IsComplete() && m_iCount==0)
		{
			++m_iCount;
			//정지
			pMonster->SetState(GameObject::eState::Paused);
			GetFSM()->SetActiveState(Monster::eMonsterState::stand);
			pMonster->SetCurStateName(L"_stand");

			pMonster->SetDead(true);

			//임시로
			if(!pMonster->GetScript<MonsterScript>()->IsBoss())
				MonsterManager::AddDeadObject(pMonster);
		}
	}
	void MonsterDead::Enter()
	{
		m_iCount = 0.f;
		GetMonster()->GetComponent<Collider2D>()->SetActive(false);
		GetMonster()->GetScript<MonsterScript>()->DeleteActiveAttack();
	}
	void MonsterDead::Exit()
	{

	}
}
