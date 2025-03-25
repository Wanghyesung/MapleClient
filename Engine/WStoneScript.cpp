#include "WStoneScript.h"
#include "WGameObject.h"
#include "WObject.h"
#include "WPlayerAttackObject.h"
#include "WPlayer.h"
#include "WPlayerScript.h"
namespace W
{
	StoneScript::StoneScript():
		m_pFunction(nullptr)
	{

	}
	StoneScript::~StoneScript()
	{

	}
	void StoneScript::Initialize()
	{

	}
	void StoneScript::Update()
	{

	}
	void StoneScript::LateUpdate()
	{

	}

	void StoneScript::Render()
	{

	}

	void StoneScript::OnCollisionEnter(Collider2D* other)
	{
		GameObject* pGameObj = other->GetOwner();
		PlayerAttackObject* pAttackObj = dynamic_cast<PlayerAttackObject*>(pGameObj);

		if (pAttackObj != nullptr)
		{
			if (pAttackObj->GetPlayer()->GetCurPlayerState() == 
				Player::ePlayerState::stab)
			{
				m_pFunction();
				object::Destroy(GetOwner());
				pAttackObj->GetPlayer()->GetScript<PlayerScript>()->SetStab(false);
			}
		}
	}
	void StoneScript::OnCollisionStay(Collider2D* other)
	{

	}
	void StoneScript::OnCollisionExit(Collider2D* other)
	{

	}
}