#include "WIce.h"
#include "WResources.h"
#include "WAnimator.h"
#include "WRenderer.h"
#include "WTransform.h"

#include "WMonster.h"
namespace W
{
	Ice::Ice()
	{
		std::shared_ptr<Material> pMater = std::make_shared<Material>();
		pMater->SetRenderinMode(eRenderingMode::Transparent);
		pMater->SetShader(Resources::Find<Shader>(L"ObjectAnimShader"));
		Resources::Insert(L"IceMater", pMater);

		MeshRenderer* pRenderer = AddComponent<MeshRenderer>();
		pRenderer->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
		pRenderer->SetMaterial(pMater);

		GetComponent<Transform>()->SetScale(2.1f, 2.1f, 0.f);

		std::shared_ptr<Texture> pAtlas = Resources::Find<Texture>(L"IceTex");
		Animator* pAnim = AddComponent<Animator>();
		pAnim->Create(L"Ice_left", pAtlas, Vector2(0.0f, 0.0f), Vector2(216.f, 242.0f), 30, Vector2(220.f, 220.f), Vector2::Zero, 0.15f);

		pAnim->Play(L"Ice_left", true);

	}

	Ice::~Ice()
	{

	}

	void Ice::Initialize()
	{
		
	}

	void Ice::Update()
	{
		
	}

	void Ice::LateUpdate()
	{
		GameObject::LateUpdate();
	}
	void Ice::Render()
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