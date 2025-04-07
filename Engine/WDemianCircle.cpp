#include "WDemianCircle.h"
#include "WRenderer.h"
#include "WResources.h"
#include "WAnimator.h"
#include "WMonster.h"
#include "WSceneManger.h"
#include "WTransform.h"
#include "WTime.h"
namespace W
{
	DemianCircle::DemianCircle()
	{

		std::shared_ptr<Material> pMater = std::make_shared<Material>();
		pMater->SetRenderinMode(eRenderingMode::Transparent);
		pMater->SetShader(Resources::Find<Shader>(L"ObjectAnimShader"));
		Resources::Insert(L"DemianCircleMater", pMater);

		MeshRenderer* pRenderer = AddComponent<MeshRenderer>();
		pRenderer->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
		pRenderer->SetMaterial(pMater);

		GetComponent<Transform>()->SetScale(4.f, 4.f, 0.f);

		std::shared_ptr<Texture> pAtlas = Resources::Find<Texture>(L"DemianCircle");
		Animator* pAnim = AddComponent<Animator>();
		pAnim->Create(L"level0", pAtlas, Vector2(0.0f, 0.0f), Vector2(260.f, 272.0f), 12, Vector2(500.f, 500.f), Vector2::Zero, 0.15f);
		pAnim->Create(L"level1", pAtlas, Vector2(0.0f, 272.0f), Vector2(361.f, 374.0f), 11, Vector2(500.f, 500.f), Vector2::Zero, 0.15f);
		pAnim->Create(L"level2", pAtlas, Vector2(0.0f, 646.f), Vector2(431.f, 449.0f), 12, Vector2(500.f, 500.f), Vector2::Zero, 0.15f);

		pAnim->Play(L"level0", true);
	}

	DemianCircle::~DemianCircle()
	{

	}
	void DemianCircle::Initialize()
	{
		
	}
	void DemianCircle::Update()
	{
		
	}
	void DemianCircle::LateUpdate()
	{
		GameObject::LateUpdate();
	}
	void DemianCircle::Render()
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