#include "WPlayerLadder.h"
#include "WInput.h"
#include "WRigidbody.h"
#include "WPlayerScript.h"
#include "WEventManager.h"


namespace W
{
	PlayerLadder::PlayerLadder()
	{
		SetType(Player::ePlayerState::ladder);
		SetStateName(L"_ladder");
	}
	PlayerLadder::~PlayerLadder()
	{

	}
	void PlayerLadder::Update()
	{
		UINT iStopCount = 2;

		Player* pPlayer = GetPlayer();
		PlayerScript* pScript = pPlayer->GetScript<PlayerScript>();
		Rigidbody* pRigidbody = pPlayer->GetComponent<Rigidbody>();
		bool bGround = pRigidbody->IsGround();
		bool bLadder = pScript->IsLadder();
		
		if(!bLadder)
			EventManager::ChangePlayerFSMState(GetFSM(), Player::ePlayerState::jump);


		if (Input::GetKeyDown(eKeyCode::SPACE))
		{
			int iDir = pPlayer->GetDir();
			if (Input::GetKey(eKeyCode::RIGHT))
				iDir = 1;
			else if (Input::GetKey(eKeyCode::LEFT))
				iDir = -1;

			EventManager::ChangePlayerFSMState(GetFSM(), Player::ePlayerState::jump);
			pRigidbody->SetVelocity(Vector2(iDir * 1.2f, 3.5f));
			pRigidbody->SetGround(false);
			pScript->SetLadder(false);
		
			pPlayer->SetAnimStop(false);
			pPlayer->SetDir(iDir);
			return;
		}

		if (Input::GetKey(eKeyCode::UP))
			pRigidbody->AddForce(Vector2(0.f, 1.f));
		else
			--iStopCount;
			
		if (Input::GetKey(eKeyCode::DOWN))
			pRigidbody->AddForce(Vector2(0.f, -1.f));
		else
			--iStopCount;

		if (iStopCount == 0)
			pPlayer->SetAnimStop(true);
		else
			pPlayer->SetAnimStop(false);
		
	}
	void PlayerLadder::Enter()
	{
		//GetPlayer()->GetScript<PlayerScript>()->SetLadder(true);
		
	}
	void PlayerLadder::Exit()
	{
		Rigidbody* pRigidbody = GetPlayer()->GetComponent<Rigidbody>();
		//현재 땅인지
		bool bOnGround = GetPlayer()->GetScript<PlayerScript>()->IsOnGround();

		//중력
		bool bGround = pRigidbody->IsGround();
		if (bGround && !bOnGround)
			pRigidbody->SetGround(false);

		GetPlayer()->SetAnimStop(false);
	}
}