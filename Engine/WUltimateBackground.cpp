#include "WUltimateBackground.h"
#include "WResources.h"
#include "WRenderer.h"
#include "WAnimator.h"
namespace W
{
	UltimateBackground::UltimateBackground()
	{
		MeshRenderer* mr = AddComponent<MeshRenderer>();
		mr->SetMesh(Resources::Find<Mesh>(L"RectMesh"));

		std::shared_ptr<Material> pMater = std::make_shared<Material>();
		pMater->SetRenderinMode(eRenderingMode::Transparent);
		pMater->SetShader(Resources::Find<Shader>(L"SpriteAnimationShader"));
		Resources::Insert(L"UltiBackMater", pMater);

		//충돌체 없음
		std::shared_ptr<Texture> pTex = Resources::Find<Texture>(L"ultimate1");

		Animator* pAnim = AddComponent<Animator>();
		pAnim->Create(L"ultimate1", pTex, Vector2(0.f, 0.f), Vector2(1412.f, 812.f), 10, Vector2(1500.f, 1500.f), Vector2(0.0f, 0.f), 0.13f);
		pAnim->FindAnimation(L"ultimate1")->Create(L"ultimate1", pTex, Vector2(0.f, 812.f), Vector2(1412.f, 812.f), 6, Vector2(1500.f, 1500.f), Vector2(0.0f, 0.f), 0.13f);

		mr->SetMaterial(pMater);

		
	}
	UltimateBackground::~UltimateBackground()
	{
	}
	void UltimateBackground::Initialize()
	{
		GetComponent<Animator>()->Play(L"ultimate1", true);
	}
	void UltimateBackground::Update()
	{
		
	}
	void UltimateBackground::LateUpdate()
	{
		GameObject::LateUpdate();
	}
	void UltimateBackground::Render()
	{
		renderer::PlayerCB PlayerCB;
		PlayerCB.vColor = Vector4(1.f, 1.f, 1.f, 0.5f);
		PlayerCB.vDir.x = 1;
		ConstantBuffer* pConstBuffer = renderer::constantBuffer[(UINT)eCBType::Player];

		pConstBuffer->SetData(&PlayerCB);
		pConstBuffer->Bind(eShaderStage::PS);

		GameObject::Render();
	}
}