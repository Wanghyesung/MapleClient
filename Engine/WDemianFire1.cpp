#include "WDemianFire1.h"
#include "WMonster.h"
#include "WSceneManger.h"
#include "WAnimator.h"
#include "WRenderer.h"
#include "WTime.h"
#include "WTransform.h"

namespace W
{
	DemianFire1::DemianFire1()
	{
		GetComponent<Transform>()->SetScale(18.f, 18.f, 0.f);

		MeshRenderer* mr = AddComponent<MeshRenderer>();
		mr->SetMesh(Resources::Find<Mesh>(L"RectMesh"));

		std::shared_ptr<Material> pMater = std::make_shared<Material>();
		pMater->SetRenderinMode(eRenderingMode::Transparent);
		pMater->SetShader(Resources::Find<Shader>(L"ObjectAnimShader"));
		Resources::Insert(L"demainfire1", pMater);

		Animator* pAnim = AddComponent<Animator>();
		std::shared_ptr<Texture> pAtlas = Resources::Find<Texture>(L"demainfire1");
		pAnim->Create(L"fire1", pAtlas, Vector2(0.0f, 0.0f), Vector2(78.f, 78.0f), 6, Vector2(2000.f, 2000.f), Vector2::Zero, 0.12f);

		pAnim->Play(L"fire1", true);

		mr->SetMaterial(pMater);
	}
	DemianFire1::~DemianFire1()
	{

	}
	void DemianFire1::Initialize()
	{
	
	}
	void DemianFire1::Update()
	{
	}
	void DemianFire1::LateUpdate()
	{
		GameObject::LateUpdate();
	}
	void DemianFire1::Render()
	{
		renderer::ObjectCB ObjcetCB;
		ObjcetCB.vObjectColor = Vector4::One;
		ObjcetCB.vObjectDir.x = 1;
		ConstantBuffer* pConstBuffer = renderer::constantBuffer[(UINT)eCBType::Object];

		pConstBuffer->SetData(&ObjcetCB);
		pConstBuffer->Bind(eShaderStage::PS);

		GameObject::Render();
	}

}