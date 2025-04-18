#include "WUltimateFog.h"
#include "WResources.h"
#include "WRenderer.h"
#include "WAnimator.h"
#include "WTransform.h"
namespace W
{
	UltimateFog::UltimateFog()
	{
		MeshRenderer* mr = AddComponent<MeshRenderer>();
		mr->SetMesh(Resources::Find<Mesh>(L"RectMesh"));

		std::shared_ptr<Material> pMater = std::make_shared<Material>();
		pMater->SetRenderinMode(eRenderingMode::Transparent);
		pMater->SetShader(Resources::Find<Shader>(L"ObjectAnimShader"));
		Resources::Insert(L"FogMater", pMater);

		//충돌체 없음
		std::shared_ptr<Texture> pTex = Resources::Find<Texture>(L"ultimate2");

		Animator* pAnim = AddComponent<Animator>();
		pAnim->Create(L"ultimate2",pTex, Vector2(0.f,0.f), Vector2(1412.f, 812.f),10, Vector2(1500.f, 1500.f), Vector2(0.0f, 0.f), 0.13f);
		pAnim->FindAnimation(L"ultimate2")->Create(L"ultimate2", pTex, Vector2(0.f, 812.f), Vector2(1412.f, 812.f), 6, Vector2(1500.f, 1500.f), Vector2(0.0f, 0.f), 0.13f);

		mr->SetMaterial(pMater);

	}
	UltimateFog::~UltimateFog()
	{
	}
	void UltimateFog::Initialize()
	{
		

		GetComponent<Transform>()->SetScale(Vector3(15.5f, 15.f, 0.f));

		GetComponent<Animator>()->Play(L"ultimate2", true);
	}
	void UltimateFog::Update()
	{
		
	}
	void UltimateFog::LateUpdate()
	{
		GameObject::LateUpdate();
	}
	void UltimateFog::Render()
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