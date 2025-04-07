#include "WDemianSpear0.h"
#include "WResources.h"
#include "WAnimator.h"
#include "WRenderer.h"
#include "WObject.h"
#include "WMonster.h"
namespace W
{
	DemianSpear0::DemianSpear0()
	{
		std::shared_ptr<Material> pMater = std::make_shared<Material>();
		pMater->SetRenderinMode(eRenderingMode::Transparent);
		pMater->SetShader(Resources::Find<Shader>(L"ObjectAnimShader"));
		Resources::Insert(L"DemianSpaerMater", pMater);

		MeshRenderer* pRenderer = AddComponent<MeshRenderer>();
		pRenderer->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
		pRenderer->SetMaterial(pMater);

		GetComponent<Transform>()->SetScale(18.f, 18.f, 0.f);

		std::shared_ptr<Texture> pAtlas = Resources::Find<Texture>(L"demianspear0");
		Animator* pAnim = AddComponent<Animator>();
		pAnim->Create(L"Spear", pAtlas, Vector2(0.0f, 0.0f), Vector2(258.f, 538.0f), 29, Vector2(2000.f, 2000.f), Vector2::Zero, 0.15f);

		pAnim->Play(L"Spear", true);

	}

	DemianSpear0::~DemianSpear0()
	{

	}

	void DemianSpear0::Initialize()
	{
		
	}

	void DemianSpear0::Update()
	{
	}

	void DemianSpear0::LateUpdate()
	{
		
		GameObject::LateUpdate();
	}
	void DemianSpear0::Render()
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