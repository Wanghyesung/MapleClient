#include "WHorntailDead.h"
#include "WAnimator.h"

namespace W
{
	HorntailDead::HorntailDead():
		m_iCount(0)
	{
		SetType(Monster::eMonsterState::dead);
		SetStateName(L"_dead");
	}
	HorntailDead::~HorntailDead()
	{

	}
	void HorntailDead::Update()
	{
		Animator* pAnimator = GetMonster()->GetComponent<Animator>();
		Animation* pAnim = pAnimator->GetActiveAnimation();
		if (pAnim->IsComplete() && m_iCount == 0)
		{
			pAnimator->Stop(true);
			m_iCount++;
			GetMonster()->SetDead(true);
		}
	}
	void HorntailDead::Enter()
	{
		GetMonster()->GetComponent<Collider2D>()->SetActive(false);
		m_iCount = 0.f;
	}
	void HorntailDead::Exit()
	{

	}
}