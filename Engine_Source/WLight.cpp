#include "WLight.h"
#include "WRenderer.h"
#include "WTransform.h"
#include "WGameObject.h"

namespace W
{
	Light::Light() :
		Component(eComponentType::Light)
	{
	}
	Light::~Light()
	{
	}
	void Light::Initialize()
	{
	}
	void Light::Update()
	{
	}
	void Light::LateUpdate()
	{
		renderer::m_vecLights.push_back(this);

		Transform* pTr = GetOwner()->GetComponent<Transform>();
		Vector3 vPos = pTr->GetPosition();
		m_eAttribute.position = Vector4(vPos.x, vPos.y, vPos.z, 1.f);
		m_eAttribute.direction = Vector4(pTr->Foward().x, pTr->Foward().y, pTr->Foward().z, 1.f);

	}
	void Light::Render()
	{
	}
}
