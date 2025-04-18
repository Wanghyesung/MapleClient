#include "WWhite.h"
#include "WResources.h"
#include "WRenderer.h"
#include "WCameraScript.h"
#include "WSceneManger.h"
#include "WTime.h"
#include "WTransform.h"
namespace W
{
	White::White()
	{
		std::shared_ptr<Material> pMater = std::make_shared<Material>();
		pMater->SetRenderinMode(eRenderingMode::Transparent);
		pMater->SetShader(Resources::Find<Shader>(L"ObjectShader"));
		Resources::Insert(L"WhiteMater", pMater);

		MeshRenderer* pRenderer = AddComponent<MeshRenderer>();
		pRenderer->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
		pRenderer->SetMaterial(pMater);

		std::shared_ptr<Texture> pAtlas = Resources::Load<Texture>(L"fadeout", L"..\\Resources\\Texture\\white.png");
		pMater->SetTexture(pAtlas);

		GetComponent<Transform>()->SetScale(12.f * 1.52f, 22.f * 1.f, 0.f);
		GetComponent<Transform>()->SetPosition(0.f,0.f,-3.f);
	}

	White::~White()
	{

	}

	void White::Initialize()
	{
		
	}

	void White::Update()
	{
		
	}

	void White::LateUpdate()
	{
		GameObject::LateUpdate();
	}

	void White::Render()
	{
		renderer::ObjectCB ObjectCB;
		ObjectCB.vObjectDir.x = 1;
		//ObjectCB.vObjectColor = m_vColor;
		ConstantBuffer* pConstBuffer = renderer::constantBuffer[(UINT)eCBType::Object];
		//Vector4 vPosition(m_vPosition.x, m_vPosition.y, m_vPosition.z, 1.f);
		pConstBuffer->SetData(&ObjectCB);
		pConstBuffer->Bind(eShaderStage::PS);

		GameObject::Render();
	}
	
}