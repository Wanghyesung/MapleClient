#include "WDemianKeyAttack.h"
#include "WResources.h"
#include "WAnimator.h"
#include "WRenderer.h"
#include "WMonster.h"
#include "WSceneManger.h"
#include "WTime.h"
#include "WTransform.h"
namespace W
{
	DemianKeyAttack::DemianKeyAttack()
	{
		//기본적으로 제공하는 script를 제거하고 전용 script로

		GetComponent<Transform>()->SetScale(20.f, 20.f, 0.f);

		MeshRenderer* mr = AddComponent<MeshRenderer>();
		mr->SetMesh(Resources::Find<Mesh>(L"RectMesh"));

		std::shared_ptr<Material> pMater = std::make_shared<Material>();
		pMater->SetRenderinMode(eRenderingMode::Transparent);
		pMater->SetShader(Resources::Find<Shader>(L"ObjectAnimShader"));
		Resources::Insert(L"keyAttackMater", pMater);

		Animator* pAnim = AddComponent<Animator>();
		std::shared_ptr<Texture> pAtlas = Resources::Find<Texture>(L"demainkeyAttack");
		pAnim->Create(L"create", pAtlas, Vector2(0.0f, 0.f), Vector2(321.0f, 522.0f), 4, Vector2(2000.f, 2000.f), Vector2::Zero, 0.11f);
		pAnim->Create(L"wait", pAtlas, Vector2(0.0f, 522.0f), Vector2(321.0f, 522.0f), 11, Vector2(2000.f, 2000.f), Vector2::Zero, 0.11f);
		pAnim->Create(L"attack", pAtlas, Vector2(0.0f, 1044.0f), Vector2(321.0f, 522.0f), 18, Vector2(2000.f, 2000.f), Vector2::Zero, 0.1f);

		mr->SetMaterial(pMater);

	}
	DemianKeyAttack::~DemianKeyAttack()
	{

	}
	void DemianKeyAttack::Initialize()
	{
		
	}
	void DemianKeyAttack::Update()
	{
		
	}
	void DemianKeyAttack::LateUpdate()
	{
		GameObject::LateUpdate();
	}
	void DemianKeyAttack::Render()
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