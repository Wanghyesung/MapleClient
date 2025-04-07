#include "WSleepGas.h"
#include "WResources.h"
#include "WAnimator.h"
//#include "WMonsterAttackScript.h"
#include "WTime.h"
#include "WRenderer.h"
#include "WTransform.h"

namespace W
{
	SleepGas::SleepGas() 
	{
	
		GetComponent<Transform>()->SetScale(4.f, 4.f, 0.f);

		MeshRenderer* mr = GetComponent<MeshRenderer>();
	

		std::shared_ptr<Material> pMater = std::make_shared<Material>();
		pMater->SetRenderinMode(eRenderingMode::Transparent);
		pMater->SetShader(Resources::Find<Shader>(L"ObjectAnimShader"));
		Resources::Insert(L"MagnusStoneMater", pMater);

		//25
		Animator* pAnim = AddComponent<Animator>();
		std::shared_ptr<Texture> pAtlas = Resources::Find<Texture>(L"sleepGas");
		pAnim->Create(L"sleepGas_start", pAtlas, Vector2(0.0f, 0.0f), Vector2(135.0f, 210.0f), 25, Vector2(450.f, 450.f), Vector2::Zero, 0.12f);
		pAnim->Create(L"sleepGas_end", pAtlas, Vector2(0.0f, 210.f), Vector2(420.0f, 271.0f), 6, Vector2(450.f, 450.f), Vector2::Zero, 0.12f);

		mr->SetMaterial(pMater);
	}

	SleepGas::~SleepGas()
	{

	}
	void SleepGas::Initialize()
	{
		
	}
	void SleepGas::Update()
	{
		
	}
	void SleepGas::LateUpdate()
	{
		GameObject::LateUpdate();
	}
	void SleepGas::Render()
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