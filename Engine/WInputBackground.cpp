#include "WInputBackground.h"
#include "WResources.h"
#include "WObject.h"
#include "WGroggy.h"
#include "WInputObject.h"
#include "WRenderer.h"
#include "WObject.h"
#include "WSceneManger.h"

namespace W
{
	InputBackground::InputBackground()
	{
		std::shared_ptr<Material> pMater = std::make_shared<Material>();
		pMater->SetShader(Resources::Find<Shader>(L"ObjectShader"));
		//pMater->SetTexture(pTex);
		Resources::Insert(L"DefenseMater", pMater);
		pMater->SetRenderinMode(eRenderingMode::Transparent);

		MeshRenderer* pRenderer = AddComponent<MeshRenderer>();
		pRenderer->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
		pRenderer->SetMaterial(pMater);

		std::shared_ptr<Texture> pAtlas = Resources::Find<Texture>(L"demainInputBack");
		pMater->SetTexture(pAtlas);

		GetComponent<Transform>()->SetScale(2.5f * 1.8f, 2.5f * 0.5f, 0.f);
	}
	InputBackground::~InputBackground()
	{
		
	}
	void InputBackground::Initialize()
	{
		
	}
	void InputBackground::Update()
	{
		

	}
	void InputBackground::LateUpdate()
	{

		GameObject::LateUpdate();

	}
	void InputBackground::Render()
	{
		renderer::ObjectCB ObjectCB;
		ObjectCB.vObjectColor = Vector4::One;

		ConstantBuffer* pConstBuffer = renderer::constantBuffer[(UINT)eCBType::Object];
		//Vector4 vPosition(m_vPosition.x, m_vPosition.y, m_vPosition.z, 1.f);
		pConstBuffer->SetData(&ObjectCB);
		pConstBuffer->Bind(eShaderStage::PS);

		GameObject::Render();
	}
}