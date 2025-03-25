#include "WStone.h"
#include "WResources.h"
#include "WStoneScript.h"
#include "WAnimator.h"
#include "WRenderer.h"
namespace W
{
	Stone::Stone()
	{
		std::shared_ptr<Material> pMater = std::make_shared<Material>();
		pMater->SetShader(Resources::Find<Shader>(L"ObjectAnimShader"));
		Resources::Insert(L"StoneMater", pMater);

		MeshRenderer* pRenderer = AddComponent<MeshRenderer>();
		pRenderer->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
		pRenderer->SetMaterial(pMater);

		AddComponent<StoneScript>();
		Collider2D* pCollider = AddComponent<Collider2D>();
		pCollider->SetSize(Vector2(0.8f, 0.8f));

		
		std::shared_ptr<Texture> pAtlas = Resources::Find<Texture>(L"StoneTex");
		Animator* pAnim = AddComponent<Animator>();
		pAnim->Create(L"stone_left", pAtlas, Vector2(0.0f, 0.0f), Vector2(69.0f, 106.0f), 3, Vector2(100.f, 100.f), Vector2::Zero, 0.2f);

		pAnim->Play(L"stone_left", true);

		//GetComponent<Transform>()->SetScale(Vector3(1.2f, 1.2f, 0.f));
	}
	Stone::~Stone()
	{

	}

	void Stone::Initialize()
	{

	}

	void Stone::Update()
	{
		GameObject::Update();
	}
	void Stone::LateUpdate()
	{
		GameObject::LateUpdate();
	}
	void Stone::Render()
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