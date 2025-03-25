#include "WPlayerStab.h"
#include "WAnimator.h"
#include "WPlayerBody.h"
#include "WPlayerScript.h"
#include "WEventManager.h"

namespace W
{
	PlayerStab::PlayerStab():
		m_iAttackCount(1)
	{
		SetType(Player::ePlayerState::stab);
		SetStateName(L"_stab");
	}
	PlayerStab::~PlayerStab()
	{

	}
	void PlayerStab::Update()
	{
		Player* pPlayer = GetPlayer();
		PlayerBody* pBody = pPlayer->GetPlayerChild<PlayerBody>();
		Animation* pBodyAnim = pBody->GetComponent<Animator>()->GetActiveAnimation();

		if (pBodyAnim->IsComplete())
		{
			EventManager::ChangePlayerFSMState(GetFSM(), Player::ePlayerState::stand);
			return;
		}
			
		int iIndex = pBodyAnim->GetCurIndex();

		if (iIndex == 1 && m_iAttackCount == 1)
		{
			m_iAttackCount = 0;
			if (m_pFunction != nullptr)
				m_pFunction();
		}
	}
	void PlayerStab::Enter()
	{
		m_iAttackCount = 1;
	}
	void PlayerStab::Exit()
	{
	
	}
}