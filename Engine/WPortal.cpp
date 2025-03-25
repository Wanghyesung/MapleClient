#include "WPortal.h"
#include "WPortalScript.h"
#include "WResources.h"
#include "WAnimator.h"
#include "WRenderer.h"

namespace W
{
	Portal::Portal()
	{
		std::shared_ptr<Material> pMater = std::make_shared<Material>();
		pMater->SetShader(Resources::Find<Shader>(L"ObjectAnimShader"));
		//pMater->SetTexture(pTex);
		Resources::Insert(L"Portal_0Mater", pMater);

		MeshRenderer* pRenderer = AddComponent<MeshRenderer>();
		pRenderer->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
		pRenderer->SetMaterial(pMater);

		AddComponent<PortalScript>();
		Collider2D* pCollider = AddComponent<Collider2D>();
		pCollider->SetSize(Vector2(0.8f, 0.8f));

		std::shared_ptr<Texture> pAtlas =
			Resources::Load<Texture>(L"Portal_0Tex", L"..\\Resources\\Texture\\Portal\\portal_0.png");
		Animator* pAnim = AddComponent<Animator>();
		pAnim->Create(L"portal0_left", pAtlas, Vector2(0.0f, 0.0f), Vector2(104.0f, 142.0f), 8, Vector2(120.f, 120.f),Vector2::Zero,0.2f);
		
		pAnim->Play(L"portal0_left", true);

		GetComponent<Transform>()->SetScale(Vector3(1.2f, 1.2f, 0.f));
	}
	Portal::~Portal()
	{

	}
	void Portal::Initialize()
	{

	}
	void Portal::Update()
	{
		GameObject::Update();
	}
	void Portal::LateUpdate()
	{
		GameObject::LateUpdate();
	}
	void Portal::Render()
	{
		renderer::ObjectCB ObjectCB;
		ObjectCB.vObjectDir.x = -1;
		ObjectCB.vObjectColor = Vector4::One;

		ConstantBuffer* pConstBuffer = renderer::constantBuffer[(UINT)eCBType::Object];
		//Vector4 vPosition(m_vPosition.x, m_vPosition.y, m_vPosition.z, 1.f);
		pConstBuffer->SetData(&ObjectCB);
		pConstBuffer->Bind(eShaderStage::PS);

		GameObject::Render();
	}
}