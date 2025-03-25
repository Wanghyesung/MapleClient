#include "WNPC.h"
#include "WRenderer.h"
namespace W
{
	NPC::NPC()
	{

	}
	NPC::~NPC()
	{

	}
	void NPC::Initialize()
	{

	}
	void NPC::Update()
	{
		GameObject::Update();
	}
	void NPC::LateUpdate()
	{
		GameObject::LateUpdate();
	}
	void NPC::Render()
	{
		renderer::ObjectCB ObjectCB;
		ObjectCB.vObjectDir.x = -1;
		ObjectCB.vObjectColor = Vector4::One;

		ConstantBuffer* pConstBuffer = renderer::constantBuffer[(UINT)eCBType::Object];
		
		pConstBuffer->SetData(&ObjectCB);
		pConstBuffer->Bind(eShaderStage::PS);

		GameObject::Render();
	}
}