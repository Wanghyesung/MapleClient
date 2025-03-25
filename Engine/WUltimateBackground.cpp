#include "WUltimateBackground.h"
#include "WResources.h"
#include "WRenderer.h"
#include "WAnimator.h"
#include "WAttackScript.h"
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
		std::shared_ptr<Texture> pTex =
			Resources::Load<Texture>(L"ultimate1", L"..\\Resources\\Texture\\Player\\skill\\ultimate\\ultimate1.png");

		Animator* pAnim = AddComponent<Animator>();
		pAnim->Create(L"ultimate1", pTex, Vector2(0.f, 0.f), Vector2(1412.f, 812.f), 10, Vector2(1500.f, 1500.f), Vector2(0.0f, 0.f), 0.13f);
		pAnim->FindAnimation(L"ultimate1")->Create(L"ultimate1", pTex, Vector2(0.f, 812.f), Vector2(1412.f, 812.f), 6, Vector2(1500.f, 1500.f), Vector2(0.0f, 0.f), 0.13f);

		mr->SetMaterial(pMater);

		AddComponent<Collider2D>()->SetSize(Vector2(0.f, 0.f));
		AddComponent<AttackScript>()->SetDeleteTime(20.f);
		GetComponent<AttackScript>()->SetDeleteObject(false);
	}
	UltimateBackground::~UltimateBackground()
	{
	}
	void UltimateBackground::Initialize()
	{
		//Vector3 vCamPos = renderer::MainCamera->GetOwner()->GetComponent<Transform>()->GetPosition();

		//GetComponent<Transform>()->SetPosition(Vector3(vCamPos.x, vCamPos.y, -3.9f));
		//GetComponent<AttackScript>()->SetDeleteTime(20.f);
		GetComponent<Transform>()->SetScale(Vector3(15.5f, 15.f, 0.f));

		GetComponent<Animator>()->Play(L"ultimate1", true);
	}
	void UltimateBackground::Update()
	{
		Vector3 vCamPos = renderer::MainCamera->GetOwner()->GetComponent<Transform>()->GetPosition();
		
		GetComponent<Transform>()->SetPosition(Vector3(vCamPos.x, vCamPos.y, -4.0f));

		GameObject::Update();
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