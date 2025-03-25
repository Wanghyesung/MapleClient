#include "WLadderScript.h"
#include "WPlayer.h"
#include "WPlayerScript.h"
#include "WInput.h"
#include "WCollider2D.h"

namespace W
{
	LadderScript::LadderScript()
	{

	}
	LadderScript::~LadderScript()
	{

	}
	void LadderScript::Initialize()
	{


	}
	void LadderScript::Update()
	{

	}
	void LadderScript::LateUpdate()
	{

	}
	void LadderScript::Render()
	{

	}
	void LadderScript::OnCollisionEnter(Collider2D* other)
	{
		//if (other->GetOwner()->GetLayerType() == eLayerType::Player)
		//{
		//	Player* pPlayer = dynamic_cast<Player*>(other->GetOwner());
		//	pPlayer->GetScript<PlayerScript>()->SetLadder(true);
		//}
	}
	void LadderScript::OnCollisionStay(Collider2D* other)
	{
		if (other->GetOwner()->GetLayerType() == eLayerType::Player)
		{
			Player* pPlayer = dynamic_cast<Player*>(other->GetOwner());
			Vector3 vPlayerCollPos = pPlayer->GetComponent<Collider2D>()->GetPosition();
			Vector3 vCollPos = GetOwner()->GetComponent<Collider2D>()->GetPosition();

			Transform* pTr = pPlayer->GetComponent<Transform>();
			Vector3 vPlayerPos = pTr->GetPosition();
			if (pPlayer->GetCurPlayerState() == Player::ePlayerState::ladder)
			{
				Vector3 vPos = GetOwner()->GetComponent<Transform>()->GetPosition();
				vPlayerPos.x = vPos.x;
				pTr->SetPosition(vPlayerPos);

			}

			if (Input::GetKeyDown(eKeyCode::UP))
			{
				if (vPlayerCollPos.y > vCollPos.y)
					return;
			}

			else if (Input::GetKeyDown(eKeyCode::DOWN))
			{
				if (vPlayerCollPos.y < vCollPos.y)
					return;
			}
			else
				return;

			pPlayer->GetScript<PlayerScript>()->SetLadder(true);
		}
	}
	void LadderScript::OnCollisionExit(Collider2D* other)
	{
		if (other->GetOwner()->GetLayerType() == eLayerType::Player)
		{
			Player* pPlayer = dynamic_cast<Player*>(other->GetOwner());
			pPlayer->GetScript<PlayerScript>()->SetLadder(false);
		}
	}
}