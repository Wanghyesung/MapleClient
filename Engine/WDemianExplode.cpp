#include "WDemianExplode.h"
#include "WResources.h"
#include "WAnimator.h"
#include "WRenderer.h"
#include "WSceneManger.h"
#include "WMonster.h"

namespace W
{
	DemianExplode::DemianExplode()
	{
		std::shared_ptr<Material> pMater = std::make_shared<Material>();
		pMater->SetRenderinMode(eRenderingMode::Transparent);
		pMater->SetShader(Resources::Find<Shader>(L"ObjectAnimShader"));
		Resources::Insert(L"DemianExpoldeMater", pMater);

		MeshRenderer* pRenderer = AddComponent<MeshRenderer>();
		pRenderer->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
		pRenderer->SetMaterial(pMater);

		std::shared_ptr<Texture> pAtlas = Resources::Find<Texture>(L"demianExplode");
		Animator* pAnim = AddComponent<Animator>();
		pAnim->Create(L"Explode", pAtlas, Vector2(0.0f, 0.0f), Vector2(439.f, 432.0f), 36, Vector2(440.f, 440.f), Vector2::Zero, 0.15f);

		pAnim->Play(L"Explode", true);

	}
	DemianExplode::~DemianExplode()
	{

	}
	void DemianExplode::Initialize()
	{
		
	}
	void DemianExplode::Update()
	{
		GameObject::Update();
	}
	void DemianExplode::LateUpdate()
	{
		GameObject::LateUpdate();
	}
	void DemianExplode::Render()
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