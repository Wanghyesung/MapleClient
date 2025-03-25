#include "WRigidbody.h"
#include "WTime.h"
#include "WTransform.h"
#include "WCollider2D.h"
#include "WGameObject.h"
#include "WSceneManger.h"
#include "WScene.h"

namespace W
{
	Rigidbody::Rigidbody() :
		Component(eComponentType::Rigidbody),
		m_vForce(Vector2::Zero),
		m_vAccelation(Vector2::Zero),
		m_vVelocity(Vector2::Zero),
		m_vLimitedVelocity(Vector2::Zero),
		m_fMass(1.f),
		m_bGround(true),
		m_bAccumulation(false)
	{
		m_vLimitedVelocity.x = 10.0f;
		m_vLimitedVelocity.y = 10.0f;
		m_vGravity = Vector2(0.0f, -9.0f);
		m_vFriction = Vector2::Zero; //사용하지 않음
	}
	Rigidbody::~Rigidbody()
	{

	}
	void Rigidbody::Initialize()
	{

	}
	void Rigidbody::Update()
	{
		Transform* pTransform = GetOwner()->GetComponent<Transform>();
		Vector3 vPosition = pTransform->GetPosition();

		Vector2 vTemPosition = Vector2(vPosition.x, vPosition.y);

		Vector2 fForce = m_vForce;
		float fLen = fForce.Length();

		if (fLen != 0.f)
		{
			fForce.Normalize();
			float fAccel = fLen / m_fMass;

			m_vAccelation = fForce * fAccel;
		}

		if (m_bAccumulation)
		{
			m_vVelocity += m_vAccelation * Time::DeltaTime();
			m_vVelocity.y = 0.f;

			vTemPosition = vTemPosition + m_vVelocity * Time::DeltaTime();
		}
		
		else if (!m_bGround)
		{
			m_vVelocity += m_vAccelation * Time::DeltaTime();
			m_vVelocity.y += m_vGravity.y * Time::DeltaTime();

			vTemPosition = vTemPosition + m_vVelocity * Time::DeltaTime();
		}
		else
		{
			m_vVelocity = m_vAccelation * Time::DeltaTime();

			Vector2 vGravity = m_vGravity;
			vGravity.Normalize();

			float dot = m_vVelocity.Dot(vGravity);
			m_vVelocity += vGravity * dot;

			if ((m_vVelocity + m_vFriction).Length() <= m_vFriction.Length())
				m_vVelocity = Vector2::Zero;
			else
				m_vVelocity.x += m_vFriction.x;

			vTemPosition = vTemPosition + m_vVelocity;
		}
		pTransform->SetPosition(vTemPosition.x, vTemPosition.y, vPosition.z);
		
		check_map();

		m_vForce = Vector2::Zero;
		m_vAccelation = Vector2::Zero;
	}
	void Rigidbody::LateUpdate()
	{

	}
	void Rigidbody::Render()
	{

	}
	void Rigidbody::AddForce(Vector2 _vForce)
	{
		m_vForce = _vForce;
	}

	void Rigidbody::check_map()
	{
		Scene::tMapPossibleSize tMapSize = SceneManger::GetActiveScene()->GetMapPossibleSize();

		GameObject* pGameObj = GetOwner();

		Transform* pTr = pGameObj->GetComponent<Transform>();	
		Collider2D* pCollider = pGameObj->GetComponent<Collider2D>();

		Vector3 vPosition = pTr->GetPosition();
		Vector3 vScale = pTr->GetScale();

		Vector3 vRightScale;
		if (pCollider)
			vRightScale = pTr->Right() * (pCollider->GetSize().x * pTr->GetScale().x * 0.5f);
		else
			vRightScale = pTr->Right() * (pTr->GetScale().x * 0.5f);


		tMapSize.RX -= vRightScale.x;
		tMapSize.LX += vRightScale.x;

		if (vPosition.x >= tMapSize.RX)
			pTr->SetPosition(tMapSize.RX, vPosition.y, vPosition.z);
		
		
		else if(vPosition.x <= tMapSize.LX)
			pTr->SetPosition(tMapSize.LX, vPosition.y, vPosition.z);


	}
}