#include "WDemianSword.h"
#include "WResources.h"
#include "WAnimator.h"
#include "WSceneManger.h"
#include "WMonster.h"
#include "WTransform.h"
#include "WTime.h"
#include "WEffect.h"
#include "WRenderer.h"
#include "WEventManager.h"

namespace W
{
	DemianSword::DemianSword()
	{
		GetComponent<Transform>()->SetScale(20.f, 20.f, 0.f);

		MeshRenderer* mr = AddComponent<MeshRenderer>();
		mr->SetMesh(Resources::Find<Mesh>(L"RectMesh"));

		std::shared_ptr<Material> pMater = std::make_shared<Material>();
		pMater->SetRenderinMode(eRenderingMode::Transparent);
		pMater->SetShader(Resources::Find<Shader>(L"ObjectAnimShader"));
		Resources::Insert(L"DemianSwordMater", pMater);
		mr->SetMaterial(pMater);

		Animator* pAnim = AddComponent<Animator>();
		std::shared_ptr<Texture> pAtlas = Resources::Find<Texture>(L"DemianSword");
		pAnim->Create(L"sword_start", pAtlas, Vector2(0.0f, 0.0f), Vector2(419.0f, 342.0f), 13, Vector2(2000.f, 2000.f), Vector2::Zero, 0.12f);
		pAnim->Create(L"sword_move", pAtlas, Vector2(0.0f, 342.0f), Vector2(419.0f, 342.0f), 8, Vector2(2000.f, 2000.f), Vector2::Zero, 0.12f);
		pAnim->Create(L"sword_end", pAtlas, Vector2(0.0f, 684.f), Vector2(419.0f, 342.0f), 11, Vector2(2000.f, 2000.f), Vector2::Zero, 0.12f);

	
		pAnim->Play(L"sword_start", true);
	}

	DemianSword::~DemianSword()
	{

	}

	void DemianSword::Initialize()
	{
	}
	void DemianSword::Update()
	{
		
	}
	void DemianSword::LateUpdate()
	{
		GameObject::LateUpdate();
	}
	void DemianSword::Render()
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