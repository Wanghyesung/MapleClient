#include "WUltimateShuriken.h"
#include "WResources.h"
#include "WAnimator.h"
#include "WTime.h"
#include "WRenderer.h"
namespace W
{
	UltimateShuriken::UltimateShuriken()
	{
		MeshRenderer* mr = AddComponent<MeshRenderer>();
		mr->SetMesh(Resources::Find<Mesh>(L"RectMesh"));

		std::shared_ptr<Material> pMater = std::make_shared<Material>();
		pMater->SetRenderinMode(eRenderingMode::Transparent);
		pMater->SetShader(Resources::Find<Shader>(L"ObjectAnimShader"));
		Resources::Insert(L"UlitShurikenMater", pMater);

		//충돌체 없음
		std::shared_ptr<Texture> pTex = Resources::Find<Texture>(L"UltiShuriken");

		Animator* pAnim = AddComponent<Animator>();
		pAnim->Create(L"shuriken", pTex, Vector2(0.f, 0.f), Vector2(581.f, 252.f), 6, Vector2(600.f, 600.f), Vector2(0.0f, 0.f), 0.1f);
		pAnim->Play(L"shuriken", true);

		mr->SetMaterial(pMater);

	}

	UltimateShuriken::~UltimateShuriken()
	{

	}
	void UltimateShuriken::Initialize()
	{
		
	}
	void UltimateShuriken::Update()
	{
		

	}
	void UltimateShuriken::LateUpdate()
	{
		GameObject::LateUpdate();

	}
	void UltimateShuriken::Render()
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