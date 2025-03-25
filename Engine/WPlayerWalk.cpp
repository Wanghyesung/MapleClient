#include "WPlayerWalk.h"
#include "WRigidbody.h"
#include "WInput.h"
#include "WPlayerScript.h"
#include "WEventManager.h"

namespace W
{
	PlayerWalk::PlayerWalk()
	{

		SetType(Player::ePlayerState::walk);
		SetStateName(L"_walk");
	}
	PlayerWalk::~PlayerWalk()
	{

	}
	void PlayerWalk::Update()
	{
		tObjectInfo tInfo = GetPlayer()->GetScript<PlayerScript>()->GetObjectInfo();
		if (Input::GetKey(eKeyCode::X))
		{
			bool bStab = GetPlayer()->GetScript<PlayerScript>()->IsStab();
			if (bStab)
			{
				EventManager::ChangePlayerFSMState(GetFSM(), Player::ePlayerState::stab);
				return;
			}

			EventManager::ChangePlayerFSMState(GetFSM(), Player::ePlayerState::swing1);
			return;
		}

		Rigidbody* pRigidbody = GetPlayer()->GetComponent<Rigidbody>();
		if (Input::GetKey(eKeyCode::RIGHT))
		{
			pRigidbody->AddForce(Vector2(tInfo.fSpeed, 0.f));
			GetPlayer()->SetDir(1);
		}
		else if (Input::GetKeyUp(eKeyCode::RIGHT))
		{
			EventManager::ChangePlayerFSMState(GetFSM(), Player::ePlayerState::stand);
		}

		if (Input::GetKey(eKeyCode::LEFT))
		{
			pRigidbody->AddForce(Vector2(-tInfo.fSpeed, 0.f));
			GetPlayer()->SetDir(-1);
		}

		else if (Input::GetKeyUp(eKeyCode::LEFT))
		{
			EventManager::ChangePlayerFSMState(GetFSM(), Player::ePlayerState::stand);
		}

		if (Input::GetKeyDown(eKeyCode::SPACE))
		{
			Rigidbody* pRigidbody = GetPlayer()->GetComponent<Rigidbody>();
			if (!pRigidbody->IsGround())
				return;
			EventManager::ChangePlayerFSMState(GetFSM(), Player::ePlayerState::jump);

			int iDir = GetPlayer()->GetDir();
			pRigidbody->SetVelocity(Vector2(iDir * 1.5f, 3.5f));
			pRigidbody->SetGround(false);
		}

	}
	void PlayerWalk::Enter()
	{

	}
	void PlayerWalk::Exit()
	{

	}
}