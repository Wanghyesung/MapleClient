#include "WDemianFire2.h"
#include "WMonster.h"
#include "WSceneManger.h"
#include "WAnimator.h"
#include "WRenderer.h"
#include "WTransform.h"
namespace W
{
	DemianFire2::DemianFire2()
	{

		//기본적으로 제공하는 script를 제거하고 전용 script로

		GetComponent<Transform>()->SetScale(18.f, 18.f, 0.f);

		MeshRenderer* mr = AddComponent<MeshRenderer>();
		mr->SetMesh(Resources::Find<Mesh>(L"RectMesh"));

		std::shared_ptr<Material> pMater = std::make_shared<Material>();
		pMater->SetRenderinMode(eRenderingMode::Transparent);
		pMater->SetShader(Resources::Find<Shader>(L"ObjectAnimShader"));
		Resources::Insert(L"demainfire2", pMater);

		Animator* pAnim = AddComponent<Animator>();
		std::shared_ptr<Texture> pAtlas = Resources::Find<Texture>(L"demainfire2");
		pAnim->Create(L"fire_start", pAtlas, Vector2(0.0f, 0.0f), Vector2(62.f, 64.0f), 9, Vector2(2000.f, 2000.f), Vector2::Zero, 0.12f);
		pAnim->Create(L"fire_end", pAtlas, Vector2(0.0f, 64.f), Vector2(167.f, 291.0f), 10, Vector2(2000.f, 2000.f), Vector2::Zero, 0.1f);

		mr->SetMaterial(pMater);
	}

	DemianFire2::~DemianFire2()
	{

	}
	void DemianFire2::Initialize()
	{
		
	}
	void DemianFire2::Update()
	{
	
	}
	void DemianFire2::LateUpdate()
	{
		GameObject::LateUpdate();
	}
	void DemianFire2::Render()
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