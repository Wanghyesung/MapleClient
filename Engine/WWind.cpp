#include "WWind.h"
#include "WResources.h"
#include "WRenderer.h"
#include "WTime.h"
#include "WAnimator.h"
#include "WTransform.h"

#include "WEventManager.h"
namespace W
{
	Wind::Wind()
	{
		MeshRenderer* mr = AddComponent<MeshRenderer>();
		mr->SetMesh(Resources::Find<Mesh>(L"RectMesh"));

		std::shared_ptr<Material> pMater = std::make_shared<Material>();
		pMater->SetRenderinMode(eRenderingMode::Transparent);
		pMater->SetShader(Resources::Find<Shader>(L"ObjectAnimShader"));
		Resources::Insert(L"WindMater", pMater);

		Animator* pAnim = AddComponent<Animator>();
		std::shared_ptr<Texture> pAtlas = Resources::Find<Texture>(L"windTex"); 
		pAnim->Create(L"move_left", pAtlas, Vector2(0.0f, 0.0f), Vector2(402.0f, 316.0f), 6, Vector2(600.f, 600.f), Vector2::Zero, 0.06f);
		pAnim->Create(L"stop_left", pAtlas, Vector2(0.0f, 316.0f), Vector2(460.0f, 460.0f), 6, Vector2(600.f, 600.f), Vector2::Zero, 0.06f);
		pAnim->Create(L"finish_left", pAtlas, Vector2(0.0f, 776.0f), Vector2(612.0f, 580.0f), 18, Vector2(600.f, 600.f), Vector2::Zero, 0.06f);
		
		pAnim->Create(L"move_right", pAtlas, Vector2(10614.f, 0.0f), Vector2(-402.0f, 316.0f), 6, Vector2(600.f, 600.f), Vector2::Zero, 0.06f);
		pAnim->Create(L"stop_right", pAtlas, Vector2(10556.f, 316.0f), Vector2(-460.0f, 460.0f), 6, Vector2(600.f, 600.f), Vector2::Zero, 0.06f);
		pAnim->Create(L"finish_right", pAtlas, Vector2(10404.f, 776.0f), Vector2(-612.0f, 580.0f), 18, Vector2(600.f, 600.f), Vector2::Zero, 0.06f);

		
		mr->SetMaterial(pMater);

	}
	Wind::~Wind()
	{

	}
	void Wind::Initialize()
	{
		

		GetComponent<Transform>()->SetScale(6.f, 6.f, 0.f);
		
	}
	void Wind::Update()
	{
		
	}

	void Wind::LateUpdate()
	{
		
		GameObject::LateUpdate();
	}
	void Wind::Render()
	{
		renderer::ObjectCB ObjcetCB;
		ObjcetCB.vObjectColor = Vector4::One;
		ObjcetCB.vObjectDir.x = m_iDir * -1;
		ConstantBuffer* pConstBuffer = renderer::constantBuffer[(UINT)eCBType::Object];
	
		pConstBuffer->SetData(&ObjcetCB);
		pConstBuffer->Bind(eShaderStage::PS);

		GameObject::Render();
	}
	
	
}