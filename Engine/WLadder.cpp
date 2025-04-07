#include "WLadder.h"

#include "WRenderer.h"

namespace W
{
	Ladder::Ladder()
	{
		
	}

	Ladder::~Ladder()
	{

	}

	void Ladder::Initialize()
	{
	
	}

	void Ladder::Update()
	{
		
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