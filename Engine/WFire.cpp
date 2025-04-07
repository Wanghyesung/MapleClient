#include "WFire.h"
#include "WResources.h"
#include "WAnimator.h"
#include "WRenderer.h"
#include "WObject.h"
#include "WMonster.h"
namespace W
{
	Fire::Fire() 
	{
		std::shared_ptr<Material> pMater = std::make_shared<Material>();
		pMater->SetRenderinMode(eRenderingMode::Transparent);
		pMater->SetShader(Resources::Find<Shader>(L"ObjectAnimShader"));
		Resources::Insert(L"FireMater", pMater);

		MeshRenderer* pRenderer = AddComponent<MeshRenderer>();
		pRenderer->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
		pRenderer->SetMaterial(pMater);

		GetComponent<Transform>()->SetScale(1.1f, 1.1f, 0.f);

		std::shared_ptr<Texture> pAtlas = Resources::Find<Texture>(L"FireTex");
		Animator* pAnim = AddComponent<Animator>();
		pAnim->Create(L"Fire_left", pAtlas, Vector2(0.0f, 0.0f), Vector2(111.f, 110.0f), 30, Vector2(110.f, 110.f), Vector2::Zero, 0.15f);

		pAnim->Play(L"Fire_left", true);

	}

	Fire::~Fire()
	{

	}

	void Fire::Initialize()
	{
	
	}

	void Fire::Update()
	{
		
	}

	void Fire::LateUpdate()
	{
		GameObject::LateUpdate();
	}
	void Fire::Render()
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