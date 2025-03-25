#include "WPlayerPronestab.h"
#include "WInput.h"
#include "WRigidbody.h"
#include "WPlayerScript.h"
#include "WTime.h"
#include "WEventManager.h"
namespace W
{
	PlayerPronestab::PlayerPronestab():
		m_fTime(0.f)
	{
		SetType(Player::ePlayerState::pronestab);
		SetStateName(L"_pronestab");
	}
	PlayerPronestab::~PlayerPronestab()
	{
	}
	void PlayerPronestab::Update()
	{
		m_fTime += Time::DeltaTime();

		if (Input::GetKey(eKeyCode::X) && m_fTime>= 0.25f)
		{
			m_fTime = 0.f;
			EventManager::ChangePlayerFSMState(GetFSM(), Player::ePlayerState::proneattack);
		}

		if (Input::GetKeyUp(eKeyCode::DOWN))
		{
			EventManager::ChangePlayerFSMState(GetFSM(), Player::ePlayerState::stand);
		}

		if (Input::GetKeyDown(eKeyCode::SPACE))
		{
			EventManager::ChangePlayerFSMState(GetFSM(), Player::ePlayerState::jump);
			GetPlayer()->GetComponent<Rigidbody>()->SetGround(false);
		}
	}
	void PlayerPronestab::Enter()
	{

	}
	void PlayerPronestab::Exit()
	{
		m_fTime = 0.f;
	}
}