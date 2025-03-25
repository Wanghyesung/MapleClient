#include "WBossStart.h"
#include "WAnimator.h"
#include "WCollider2D.h"
#include "WEventManager.h"
namespace W
{
	BossStart::BossStart()
		:m_iCount(0)
	{
		SetType(Monster::eMonsterState::start);
		SetStateName(L"_start");
	}
	BossStart::~BossStart()
	{

	}
	void BossStart::Update()
	{
		Animator* pAnimator = GetMonster()->GetComponent<Animator>();
		Animation* pAnim = pAnimator->GetActiveAnimation();
		if (pAnim->IsComplete() && m_iCount == 0)
		{
			Collider2D* pCollider = GetMonster()->GetComponent<Collider2D>();
			pCollider->SetActive(true);
			EventManager::ChangeMonsterFSMState(GetFSM(), Monster::eMonsterState::stand);
		}

	}
	void BossStart::Enter()
	{
		GetMonster()->SetCurStateName(GetStateName());
		m_iCount = 0;
	}
	void BossStart::Exit()
	{

	}
}