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

		Animator* pAnim = AddComponent<Animator>();
		pAnim->Create(L"Explode", nullptr, Vector2(0.0f, 0.0f), Vector2(439.f, 432.0f), 36, Vector2(440.f, 440.f), Vector2::Zero, Vector2(15804.f, 432.f), 0.15f);

		GetComponent<Transform>()->SetScale(4.f, 4.f, 0.f);

	}
	DemianExplode::~DemianExplode()
	{

	}
	void DemianExplode::Initialize()
	{
		std::shared_ptr<Texture> pAtlas = Resources::Find<Texture>(L"demianExplode");
		GetComponent<Animator>()->SetTexture(pAtlas);
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
	
	void DemianExplode::UpdateState(const wstring& _strStateName, int _iState)
	{
		MonsterAttackObject::UpdateState(_strStateName, _iState);
	}

}