#include "WLoad.h"
#include "WResources.h"
#include "WAnimator.h"
#include "WTransform.h"
#include "WTime.h"
#include "WAutoShuriken.h"
#include "WEventManager.h"
#include "WRenderer.h"

namespace W
{
	Load::Load()
	{
		MeshRenderer* mr = AddComponent<MeshRenderer>();
		mr->SetMesh(Resources::Find<Mesh>(L"RectMesh"));

		std::shared_ptr<Material> pMater = std::make_shared<Material>();
		pMater->SetRenderinMode(eRenderingMode::Transparent);
		pMater->SetShader(Resources::Find<Shader>(L"ObjectAnimShader"));
		Resources::Insert(L"loadMater", pMater);
		mr->SetMaterial(pMater);

		Animator* pAnim = AddComponent<Animator>();
		std::shared_ptr<Texture> pAtlas
			= Resources::Find<Texture>(L"loadTex");
		pAnim->Create(L"active", pAtlas, Vector2(0.0f, 0.0f), Vector2(1700.0f, 1200.0f), 5, Vector2(1700.f, 1700.f), Vector2::Zero, 0.1f);
		pAnim->FindAnimation(L"active")->Create(L"active",pAtlas, Vector2(0.0f, 1200.0f), Vector2(1700.0f, 1200.0f), 5, Vector2(1700.f, 1700.f), Vector2::Zero, 0.1f);

		pAnim->Create(L"end", pAtlas, Vector2(0.0f, 2400.0f), Vector2(1700.0f, 1200.0f), 6, Vector2(1700.f, 1700.f), Vector2::Zero, 0.01f);
		pAnim->FindAnimation(L"end")->Create(L"end", pAtlas, Vector2(0.0f, 3600.0f), Vector2(1700.0f, 1200.0f), 6, Vector2(1700.f, 1700.f), Vector2::Zero, 0.1f);
		pAnim->FindAnimation(L"end")->Create(L"end", pAtlas, Vector2(0.0f, 4800.0f), Vector2(1700.0f, 1200.0f), 6, Vector2(1700.f, 1700.f), Vector2::Zero, 0.1f);
		pAnim->FindAnimation(L"end")->Create(L"end", pAtlas, Vector2(0.0f, 6000.0f), Vector2(1700.0f, 1200.0f), 6, Vector2(1700.f, 1700.f), Vector2::Zero, 0.1f);

		
		//test
		pAtlas->BindShaderResource(eShaderStage::PS, 12);

		GetComponent<Transform>()->SetScale(11.f, 11.f, 0.f);
	}
	Load::~Load()
	{

	}
	void Load::Initialize()
	{
		
	}
	void Load::Update()
	{
		
	}
	void Load::LateUpdate()
	{
		GameObject::LateUpdate();
	}

	void Load::Render()
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