#include "WPlayerSwing1.h"
#include "WInput.h"
#include "WAnimator.h"
#include "WAnimation.h"
#include "WPlayerBody.h"
#include "WPlayerScript.h"
#include "WRigidbody.h"
#include "WEventManager.h"
#include "WShadow.h"
namespace W
{
#define ATTACK1_FRAME 2

	PlayerSwing1::PlayerSwing1():
		m_iSwingCount(1)
	{
		SetType(Player::ePlayerState::swing1);
		SetStateName(L"_swing1");
	}

	PlayerSwing1::~PlayerSwing1()
	{
				
	}

	void PlayerSwing1::Update()
	{
		Player* pPlayer = GetPlayer();
		PlayerBody* pBody = pPlayer->GetPlayerChild<PlayerBody>();
		Animation* pBodyAnim = pBody->GetComponent<Animator>()->GetActiveAnimation();

		if (pBodyAnim == nullptr)
			return;

		bool bComplete = pBodyAnim->IsComplete();
		if (bComplete)
			EventManager::ChangePlayerFSMState(GetFSM(), Player::ePlayerState::stand);

		Rigidbody* pRigidbody = pPlayer->GetComponent<Rigidbody>();

		bool bRround = pRigidbody->IsGround();

		if (!bRround)
		{
			if (Input::GetKey(eKeyCode::RIGHT))
				pRigidbody->AddForce(Vector2(1.5f, 0.f));

			if (Input::GetKey(eKeyCode::LEFT))
				pRigidbody->AddForce(Vector2(-1.5f, 0.f));
		}

		if (pBodyAnim->GetCurIndex() == ATTACK1_FRAME && m_iSwingCount == 1)
		{
			if (m_pFunction != nullptr)
			{
				if (pPlayer->IsShadow())
				{
					pPlayer->GetShadow()->Set_Attack(m_pFunction, 0.1f);
				}
				m_pFunction();
			}

			m_iSwingCount = 0;
		}
	}

	void PlayerSwing1::Enter()
	{
		if (GetPlayer()->IsDark())
			GetPlayer()->SetDark(false);

		srand(time(nullptr));
		UINT iAttackNumber = rand() % 2;
		if (iAttackNumber == 0)
			SetStateName(L"_swing1");
		else
			SetStateName(L"_swing2");

		m_iSwingCount = 1;
		GetPlayer()->GetScript<PlayerScript>()->SetAttack(true);
	}
	void PlayerSwing1::Exit()
	{
		GetPlayer()->GetScript<PlayerScript>()->SetAttack(false);
	}

}