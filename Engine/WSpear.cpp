#include "WSpear.h"
#include "WResources.h"
#include "WAnimator.h"
#include "WRenderer.h"
#include "WObject.h"
#include "WSceneManger.h"
#include "WMonster.h"
namespace W
{
	Spear::Spear()
	{
		std::shared_ptr<Material> pMater = std::make_shared<Material>();
		pMater->SetRenderinMode(eRenderingMode::Transparent);
		pMater->SetShader(Resources::Find<Shader>(L"ObjectAnimShader"));
		Resources::Insert(L"SpearMater", pMater);

		MeshRenderer* pRenderer = AddComponent<MeshRenderer>();
		pRenderer->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
		pRenderer->SetMaterial(pMater);

		GetComponent<Transform>()->SetScale(2.1f, 2.1f, 0.f);

		std::shared_ptr<Texture> pAtlas = Resources::Find<Texture>(L"SpearTex");
		Animator* pAnim = AddComponent<Animator>();
		pAnim->Create(L"Spear_left", pAtlas, Vector2(0.0f, 0.0f), Vector2(185.f, 160.0f), 17, Vector2(220.f, 220.f), Vector2::Zero, 0.15f);

		pAnim->Play(L"Spear_left", true);
	}

	Spear::~Spear()
	{

	}

	void Spear::Initialize()
	{
		
	}

	void Spear::Update()
	{
		
		GameObject::Update();
	}
	void Spear::LateUpdate()
	{
		
		GameObject::LateUpdate();
	}
	void Spear::Render()
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