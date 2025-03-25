#include "WPullObject.h"
#include "WTime.h"
#include "WRigidbody.h"
#include "WObject.h"
namespace W
{
	PullObject::PullObject():
		m_pTarget(nullptr),
		m_vPullPosition(Vector2::Zero),
		m_vForece(Vector2::Zero),
		m_fCurTime(0.f),
		m_fDeleteTime(0.f)
	{

	}

	PullObject::~PullObject()
	{

	}

	void PullObject::Initialize()
	{
		if (m_pTarget)
		{
			Rigidbody* pRigidbody = m_pTarget->GetComponent<Rigidbody>();
			Vector2 vVel = pRigidbody->GetVelocity();

			Vector3 vTargetPos = m_pTarget->GetComponent<Transform>()->GetPosition();

			Vector2 vDiff = Vector2(m_vPullPosition.x - vTargetPos.x, 0.f);
			float fLen = vDiff.Length();
			vDiff.Normalize();
			int iDir = vDiff.x > 0 ? 1 : -1;

			if (fLen > 0.f)
			{
				pRigidbody->SetAccumulation(true);
				pRigidbody->SetVelocity(Vector2(iDir * 10.f, vVel.y));
			}
		}
	}
	void PullObject::Update()
	{
		m_fCurTime += Time::DeltaTime();

		if (m_fCurTime >= m_fDeleteTime)
		{
			m_pTarget->GetComponent<Rigidbody>()->SetAccumulation(false);
			object::Destroy(this);
			return;
		}

		Vector3 vTargetPos = m_pTarget->GetComponent<Transform>()->GetPosition();

		Vector2 vDiff = Vector2(m_vPullPosition.x - vTargetPos.x, 0.f);
		float fLen = vDiff.Length();
		Rigidbody* pRigidbody = m_pTarget->GetComponent<Rigidbody>();
		Vector2 vVel = pRigidbody->GetVelocity();

		if (fLen <= 0.5f)
		{
			m_pTarget->GetComponent<Rigidbody>()->SetVelocity(Vector2(0.f, vVel.y));
		}

		GameObject::Update();
	}
	void PullObject::LateUpdate()
	{
		GameObject::LateUpdate();
	}
	void PullObject::Render()
	{
		GameObject::Render();

	}
}