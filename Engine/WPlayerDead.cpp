#include "WPlayerDead.h"
#include "WInput.h"
#include "WRigidbody.h"
#include "WPlayerScript.h"
#include "WEventManager.h"
#include "WRigidbody.h"
namespace W
{
	PlayerDead::PlayerDead():
		m_fRadian(0.f)
	{
		SetType(Player::ePlayerState::dead);
		SetStateName(L"_dead");
	}
	PlayerDead::~PlayerDead()
	{

	}
	void PlayerDead::Update()
	{
		
	}
	void PlayerDead::Enter()
	{
		GetPlayer()->SetState(GameObject::eState::Paused);

		m_fRadian = 0.f;
	}
	void PlayerDead::Exit()
	{

	}
}