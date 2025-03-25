#include "WGroundScript.h"
#include "WGameObject.h"
#include "WTransform.h"
#include "WRigidbody.h"
#include "WPlayerScript.h"
#include "WPlayer.h"

//directional 전역 빛
//point 전구
//spot 원뿔모양

//상수버퍼로만은 빛을 계산하기 부족하기 때문에 11부터 구조체버퍼를 사용
//데이터 크기 데이터 배열 사이즈 배열로 넘길 수 있음 



namespace W
{
	GroundScript::GroundScript():
		m_bPass(false),
		m_bFinalGround(false)
	{
	}
	GroundScript::~GroundScript()
	{
	}
	void GroundScript::Initialize()
	{

	}
	void GroundScript::Update()
	{
		
	}
	void GroundScript::LateUpdate()
	{

	}
	void GroundScript::Render()
	{

	}
	void GroundScript::OnCollisionEnter(Collider2D* other)
	{
		GameObject* pGameObj = other->GetOwner();
		Rigidbody* pOtherRigidbody = pGameObj->GetComponent<Rigidbody>();
		if (pGameObj->GetLayerType() == eLayerType::Player ||
			pGameObj->GetLayerType() == eLayerType::ItemObject)
		{
			if (pGameObj->GetLayerType() == eLayerType::Player)
			{
				Player* pPlayer = dynamic_cast<Player*>(pGameObj);
				PlayerScript* pPlayerScript = pGameObj->GetScript<PlayerScript>();

				if (pPlayer->GetCurPlayerState() == Player::ePlayerState::ladder)
				{
					if (!check_ladder(other))
						return;
					m_bPass = true;
				}

				else if (!check_position(other))
				{
					return;
				}
				pPlayerScript->SetOnGround(true);
			}
			Collider2D* pGroundCollider = GetOwner()->GetComponent<Collider2D>();
			Collider2D* pOtherCollider = pGameObj->GetComponent<Collider2D>();

			Vector3 vPos = pGroundCollider->GetPosition();
			Vector3 vOtherPos = pOtherCollider->GetPosition();

			Vector2 vSize = pGroundCollider->GetSize();
			Vector2 vOthersize = pOtherCollider->GetSize();

			Vector3 vScale = GetOwner()->GetComponent<Transform>()->GetScale();
			Vector3 vOtherSclae = pGameObj->GetComponent<Transform>()->GetScale();

			float fDiff = (vPos.y - vOtherPos.y);
			float value = fabs(fDiff) - (vSize.y * vScale.y + vOthersize.y * vOtherSclae.y) / 2.f;

			vOtherPos.y -= value;
			pGameObj->GetComponent<Transform>()->SetPosition(vOtherPos);

			pOtherRigidbody->SetGround(true);
		}
	}
	void GroundScript::OnCollisionStay(Collider2D* other)
	{
		if (!m_bFinalGround)
			return;
		
		GameObject* pGameObj = other->GetOwner();
		
		if (pGameObj->GetLayerType() == eLayerType::Player)
		{
			Player* pPlayer = dynamic_cast<Player*>(pGameObj);
			if (pPlayer->GetPrevPlayerState() == Player::ePlayerState::pronestab &&
				pPlayer->GetCurPlayerState() == Player::ePlayerState::jump)
			{
				Collider2D* pGroundCollider = GetOwner()->GetComponent<Collider2D>();
				Collider2D* pOtherCollider = pGameObj->GetComponent<Collider2D>();

				Vector3 vPos = pGroundCollider->GetPosition();
				Vector3 vOtherPos = pOtherCollider->GetPosition();

				Vector2 vSize = pGroundCollider->GetSize();
				Vector2 vOthersize = pOtherCollider->GetSize();

				Vector3 vScale = GetOwner()->GetComponent<Transform>()->GetScale();
				Vector3 vOtherSclae = pGameObj->GetComponent<Transform>()->GetScale();

				float fDiff = (vPos.y - vOtherPos.y);
				float value = fabs(fDiff) - (vSize.y * vScale.y + vOthersize.y * vOtherSclae.y) / 2.f;

				vOtherPos.y -= value;
				pGameObj->GetComponent<Transform>()->SetPosition(vOtherPos);

				pGameObj->GetComponent<Rigidbody>()->SetGround(true);
			}
		}
	}


	void GroundScript::OnCollisionExit(Collider2D* other)
	{
		GameObject* pGameObj = other->GetOwner();
		if (pGameObj->GetLayerType() == eLayerType::Player)
		{
			Player* pPlayer = dynamic_cast<Player*>(pGameObj);
			PlayerScript* pPlayerScript = pGameObj->GetScript<PlayerScript>();

			if (pPlayer->GetCurPlayerState() == Player::ePlayerState::walk)
				pPlayerScript->ActiveJump();

			pPlayerScript->SetOnGround(false);
			
		}
	}
	bool GroundScript::check_position(Collider2D* other)
	{
		GameObject* pGameObj = other->GetOwner();
		Player* pPlayer = dynamic_cast<Player*>(pGameObj);
		PlayerScript* pPlayerScript = pPlayer->GetScript<PlayerScript>();

		Rigidbody* pOtherRigidbody = pGameObj->GetComponent<Rigidbody>();
		Vector2 vPlayerVel = pOtherRigidbody->GetVelocity();
		
		if (vPlayerVel.y > 0)
			return false;

		Transform* pTr = pPlayer->GetComponent<Transform>();
		Collider2D* pCollider = pPlayer->GetComponent<Collider2D>();
		Vector3 vPlayerY = pTr->Up() * (pCollider->GetSize().y * pTr->GetScale().y * 0.4f);
		float fPlayerPos = pTr->GetPosition().y - vPlayerY.y;

		Transform* pGroundTr = GetOwner()->GetComponent<Transform>();
		Collider2D* pGroundCollider = GetOwner()->GetComponent<Collider2D>();
		Vector3 vGroundY = pGroundTr->Up() * (pGroundCollider->GetSize().y * pGroundTr->GetScale().y * 0.5f);
		float fGroundPos = pGroundTr->GetPosition().y + vGroundY.y;

		if (fGroundPos >= fPlayerPos)
			return false;

		return true;
	}
	bool GroundScript::check_ladder(Collider2D* other)
	{
		GameObject* pGameObj = other->GetOwner();
		PlayerScript* pPlayerScript = pGameObj->GetScript<PlayerScript>();
		Vector2 vPlayerVel = pGameObj->GetComponent<Rigidbody>()->GetVelocity();
		
		if (vPlayerVel.y < 0.f)
		{
			pPlayerScript->SetLadder(false);
		}


		return true;
	}
}