#include "WDemianFire0.h"
#include "WMonster.h"
#include "WSceneManger.h"
#include "WAnimator.h"
#include "WRenderer.h"
#include "WTransform.h"
namespace W
{
	DemianFire0::DemianFire0()
	{
	
		GetComponent<Transform>()->SetScale(18.f, 18.f, 0.f);

		MeshRenderer* mr = AddComponent<MeshRenderer>();
		mr->SetMesh(Resources::Find<Mesh>(L"RectMesh"));

		std::shared_ptr<Material> pMater = std::make_shared<Material>();
		pMater->SetRenderinMode(eRenderingMode::Transparent);
		pMater->SetShader(Resources::Find<Shader>(L"ObjectAnimShader"));
		Resources::Insert(L"demainfire0", pMater);

		Animator* pAnim = AddComponent<Animator>();
		pAnim->Create(L"fire_start", nullptr, Vector2(0.0f, 0.0f), Vector2(144.f, 142.0f), 9, Vector2(2000.f, 2000.f), Vector2::Zero, Vector2(2695.f, 351.f), 0.12f);
		pAnim->Create(L"fire_end", nullptr, Vector2(0.0f, 142.f), Vector2(385.f, 209.0f), 7, Vector2(2000.f, 2000.f), Vector2::Zero, Vector2(2695.f, 351.f), 0.1f);

		mr->SetMaterial(pMater);
	}
	DemianFire0::~DemianFire0()
	{

	}
	void DemianFire0::Initialize()
	{
		std::shared_ptr<Texture> pAtlas = Resources::Find<Texture>(L"demainfire0");
		GetComponent<Animator>()->SetTexture(pAtlas);
	}
	void DemianFire0::Update()
	{
	}
	void DemianFire0::LateUpdate()
	{
		GameObject::LateUpdate();
	}
	void DemianFire0::Render()
	{
		renderer::ObjectCB ObjcetCB;
		ObjcetCB.vObjectColor = Vector4::One;
		ObjcetCB.vObjectDir.x = 1;
		ConstantBuffer* pConstBuffer = renderer::constantBuffer[(UINT)eCBType::Object];

		pConstBuffer->SetData(&ObjcetCB);
		pConstBuffer->Bind(eShaderStage::PS);

		GameObject::Render();
	}

	void DemianFire0::UpdateState(const wstring& _strStateName, int _iState)
	{
		MonsterAttackObject::UpdateState(_strStateName, _iState);
	}
	
}