#include "WPlayerJump.h"
#include "WInput.h"
#include "WRigidbody.h"
#include "WPlayerScript.h"
#include "WEventManager.h"
namespace W
{
	PlayerJump::PlayerJump()
	{
		SetType(Player::ePlayerState::jump);
		SetStateName(L"_jump");
	}
	PlayerJump::~PlayerJump()
	{

	}
	void PlayerJump::Update()
	{
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

		if (Input::GetKey(eKeyCode::UP))
		{
			bool bLadder = GetPlayer()->GetScript<PlayerScript>()->IsLadder();
			if (bLadder)
			{
				EventManager::ChangePlayerFSMState(GetFSM(), Player::ePlayerState::ladder);
				GetPlayer()->GetComponent<Rigidbody>()->SetGround(true);
				return;
			}
		}

		Rigidbody* pRigidbody = GetPlayer()->GetComponent<Rigidbody>();
		bool bGround = pRigidbody->IsGround();

		Vector2 vForece = Vector2::Zero;
		const tObjectInfo& tInfo = GetPlayer()->GetScript<PlayerScript>()->GetObjectInfo();
		if (bGround)
		{
			EventManager::ChangePlayerFSMState(GetFSM(), Player::ePlayerState::stand);
			return;
		}

		if (Input::GetKey(eKeyCode::RIGHT))
		{
			GetPlayer()->SetDir(1);
			vForece.x += (tInfo.fSpeed - 1.f);
		}

		else if (Input::GetKey(eKeyCode::LEFT))
		{
			GetPlayer()->SetDir(-1);
			vForece.x -= (tInfo.fSpeed - 1.f);
		}


		pRigidbody->AddForce(vForece);
	}
	void PlayerJump::Enter()
	{
		
	}
	void PlayerJump::Exit()
	{
		
	}
}