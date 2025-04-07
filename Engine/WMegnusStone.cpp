#include "WMegnusStone.h"
#include "WResources.h"
#include "WAnimator.h"

#include "WRenderer.h"

#include "WMonster.h"
#include "WSceneManger.h"
#include "WTransform.h"
namespace W
{
	MegnusStone::MegnusStone() 
	{
		//기본적으로 제공하는 script를 제거하고 전용 script로

		GetComponent<Transform>()->SetScale(10.f, 10.f, 0.f);

		MeshRenderer* mr = AddComponent<MeshRenderer>();
		mr->SetMesh(Resources::Find<Mesh>(L"RectMesh"));

		std::shared_ptr<Material> pMater = Resources::Find<Material>(L"MagnusStoneMater");
		if (pMater == nullptr)
		{
			pMater = std::make_shared<Material>();
			pMater->SetRenderinMode(eRenderingMode::Transparent);
			pMater->SetShader(Resources::Find<Shader>(L"ObjectAnimShader"));
			Resources::Insert(L"MagnusStoneMater", pMater);
		}

		Animator* pAnim = AddComponent<Animator>();
		std::shared_ptr<Texture> pAtlas
			= Resources::Find<Texture>(L"magnus_stone");
		pAnim->Create(L"stone_start", pAtlas, Vector2(0.0f, 0.0f), Vector2(350.0f, 350.0f), 7, Vector2(1100.f, 1100.f), Vector2::Zero, 0.12f);
		pAnim->Create(L"stone_move", pAtlas, Vector2(0.0f, 350.0f), Vector2(350.0f, 350.0f), 8, Vector2(1100.f, 1100.f), Vector2::Zero, 0.12f);
		pAnim->Create(L"stone_end", pAtlas, Vector2(0.0f, 700.f), Vector2(350.0f, 350.0f), 6, Vector2(1100.f, 1100.f), Vector2::Zero, 0.1f);


		mr->SetMaterial(pMater);
	}
	MegnusStone::~MegnusStone()
	{

	}
	void MegnusStone::Initialize()
	{
		
	}
	void MegnusStone::Update()
	{
		
	}
	void MegnusStone::LateUpdate()
	{
		GameObject::LateUpdate();
	}
	void MegnusStone::Render()
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