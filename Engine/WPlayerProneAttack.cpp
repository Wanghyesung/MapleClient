#include "WPlayerProneAttack.h"
#include "WAnimator.h"
#include "WAnimation.h"
#include "WPlayerBody.h"
#include "WInput.h"
#include "WPlayerScript.h"
#include "WEventManager.h"
namespace W
{
	PlayerProneAttack::PlayerProneAttack()
	{
		SetType(Player::ePlayerState::proneattack);
		SetStateName(L"_proneattack");
	}
	PlayerProneAttack::~PlayerProneAttack()
	{

	}
	void PlayerProneAttack::Update()
	{
		Player* pPlayer = GetPlayer();
		PlayerBody* pBody = pPlayer->GetPlayerChild<PlayerBody>();
		Animation* pBodyAnim = pBody->GetComponent<Animator>()->GetActiveAnimation();

		if (pBodyAnim == nullptr)
			return;

		bool bComplete = pBodyAnim->IsComplete();
		if (bComplete)
			EventManager::ChangePlayerFSMState(GetFSM(), Player::ePlayerState::pronestab);

		if (Input::GetKeyUp(eKeyCode::DOWN))
		{
			EventManager::ChangePlayerFSMState(GetFSM(), Player::ePlayerState::stand);
		}


	}
	void PlayerProneAttack::Enter()
	{
		if(m_pFunction != nullptr)
			m_pFunction();
	}
	void PlayerProneAttack::Exit()
	{
		//GetPlayer()->SetAnimLoop(true);
	}
}