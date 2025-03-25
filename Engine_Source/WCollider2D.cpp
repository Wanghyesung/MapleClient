#include "WCollider2D.h"
#include "WGameObject.h"
#include "WTransform.h"
#include "WRenderer.h"
namespace W
{
	UINT Collider2D::ColliderNumber = 0;
	Collider2D::Collider2D():
		Component(eComponentType::Collider2D),
		m_pTransform(nullptr),
		m_vSize(Vector2::One),
		m_vCenter(Vector2::Zero),
		m_bActive(true)
	{
		++ColliderNumber;
		m_iColliderID = ColliderNumber;
	}
	Collider2D::~Collider2D()
	{

	}
	void Collider2D::Initialize()
	{
		m_pTransform = GetOwner()->GetComponent<Transform>();
	}
	void Collider2D::Update()
	{
	}
	void Collider2D::LateUpdate()
	{
		Transform* pTransform = GetOwner()->GetComponent<Transform>();

		Vector3 vScale = pTransform->GetScale();
		vScale.x *= m_vSize.x;
		vScale.y *= m_vSize.y;

		Vector3 vPos = pTransform->GetPosition();
		vPos.x += m_vCenter.x;
		vPos.y += m_vCenter.y;

		m_vPosition = vPos;

		graphics::DebugMesh mesh = {};
		mesh.position = vPos;
		mesh.scale = vScale;
		mesh.rotation = pTransform->GetRotation();
		mesh.type = eColliderType::Rect;
		mesh.active = m_bActive;

		//매 프레임마다 editor에 메시정보 넘기기
		renderer::PushDebugMeshAttribute(mesh);

	}
	void Collider2D::Render()
	{
	}
	void Collider2D::OnCollisionEnter(Collider2D* other)
	{
		Script* pScript = GetOwner()->GetScript<Script>();
		pScript->OnCollisionEnter(other);
		//스크립트는 하나만 가지게
		//const std::vector<Script*>& scripts =
		//	GetOwner()->GetComponents<Script>();
		//
		//for (Script* script : scripts)
		//{
		//	script->OnCollisionEnter(other);
		//}
		//pScript->OnCollisionEnter(other);
	}
	void Collider2D::OnCollisionStay(Collider2D* other)
	{
		Script* pScript = GetOwner()->GetScript<Script>();
		pScript->OnCollisionStay(other);
		//const std::vector<Script*>& scripts =
		//	GetOwner()->GetComponents<Script>();
		//
		//for (Script* script : scripts)
		//{
		//	script->OnCollisionStay(other);
		//}
	}
	void Collider2D::OnCollisionExit(Collider2D* other)
	{
		Script* pScript = GetOwner()->GetScript<Script>();
		pScript->OnCollisionExit(other);
		//const std::vector<Script*>& scripts =
		//	GetOwner()->GetComponents<Script>();
		//
		//for (Script* script : scripts)
		//{
		//	script->OnCollisionExit(other);
		//}
	}
}