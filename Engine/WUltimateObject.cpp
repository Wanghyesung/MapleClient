#include "WUltimateObject.h"
#include "WSceneManger.h"
#include "WTime.h"
#include "WAnimator.h"
#include "WRenderer.h"
#include "WEventManager.h"
namespace W
{
	UltimateObject::UltimateObject()
	{
		MeshRenderer* mr = AddComponent<MeshRenderer>();
		mr->SetMesh(Resources::Find<Mesh>(L"RectMesh"));

		std::shared_ptr<Material> pMater = std::make_shared<Material>();
		pMater->SetRenderinMode(eRenderingMode::Transparent);
		pMater->SetShader(Resources::Find<Shader>(L"ObjectAnimShader"));
		Resources::Insert(L"UitimateMater", pMater);
		mr->SetMaterial(pMater);

		Animator* pAnim = AddComponent<Animator>();
		std::shared_ptr<Texture> pAtlas = Resources::Find<Texture>(L"ultimate0");
		pAnim->Create(L"ultimate", pAtlas, Vector2(0.f, 0.f), Vector2(1456.f, 860.f), 10, Vector2(1500.f, 1500.f), Vector2(0.0f, 0.f), 0.08f);
		pAnim->FindAnimation(L"ultimate")->Create(L"ultimate", pAtlas, Vector2(0.f, 860.f), Vector2(1456.f, 860.f), 10, Vector2(1500.f, 1500.f), Vector2(0.0f, 0.f), 0.08f);
		pAnim->FindAnimation(L"ultimate")->Create(L"ultimate", pAtlas, Vector2(0.f, 1720.f), Vector2(1456.f, 860.f), 10, Vector2(1500.f, 1500.f), Vector2(0.0f, 0.f), 0.08f);
		pAnim->FindAnimation(L"ultimate")->Create(L"ultimate", pAtlas, Vector2(0.f, 2580.f), Vector2(1456.f, 860.f), 10, Vector2(1500.f, 1500.f), Vector2(0.0f, 0.f), 0.08f);
		pAnim->FindAnimation(L"ultimate")->Create(L"ultimate", pAtlas, Vector2(0.f, 3440.f), Vector2(1456.f, 860.f), 10, Vector2(1500.f, 1500.f), Vector2(0.0f, 0.f), 0.08f);

		
	}
	UltimateObject::~UltimateObject()
	{

	}
	void UltimateObject::Initialize()
	{
		GetComponent<Animator>()->Play(L"ultimate", false);
	}
	void UltimateObject::Update()
	{
		
	}
	void UltimateObject::LateUpdate()
	{
		GameObject::LateUpdate();
	}
	void UltimateObject::Render()
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