#include "WLadder.h"
#include "WCollider2D.h"
#include "WLadderScript.h"
#include "WCollider2D.h"
#include "WRenderer.h"

namespace W
{
	Ladder::Ladder()
	{
		Collider2D* pDcollider = AddComponent<Collider2D>();
		AddComponent<LadderScript>();
	}

	Ladder::~Ladder()
	{

	}

	void Ladder::Initialize()
	{
		Collider2D* pDcollider = GetComponent<Collider2D>();
		Vector3 vScale = GetComponent<Transform>()->GetScale();
		pDcollider->SetSize(Vector2(0.3f, 1.f));
		//pDcollider->SetCenter(Vector2(0.f, 0.3f));
		GetScript<LadderScript>()->Initialize();
	}

	void Ladder::Update()
	{
		GameObject::Update();
	}

	void Ladder::LateUpdate()
	{
		GameObject::LateUpdate();
	}

	void Ladder::Render()
	{
		renderer::ObjectCB ObjectCB;
		ObjectCB.vObjectDir.x = 1;
		ObjectCB.vObjectColor = Vector4::One;

		ConstantBuffer* pConstBuffer = renderer::constantBuffer[(UINT)eCBType::Object];
		//Vector4 vPosition(m_vPosition.x, m_vPosition.y, m_vPosition.z, 1.f);
		pConstBuffer->SetData(&ObjectCB);
		pConstBuffer->Bind(eShaderStage::PS);

		GameObject::Render();
	}
}