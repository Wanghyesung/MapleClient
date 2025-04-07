#include "WStigmaBack.h"
#include "WResources.h"
#include "WAnimator.h"
#include "WSceneManger.h"
#include "WRenderer.h"
#include "WStigmaCount.h"
#include "WEventManager.h"
#include "WTransform.h"
namespace W
{
	StigmaBack::StigmaBack()
	{
		GetComponent<Transform>()->SetScale(1.5f, 1.5f, 0.f);


		MeshRenderer* mr = AddComponent<MeshRenderer>();
		mr->SetMesh(Resources::Find<Mesh>(L"RectMesh"));

		std::shared_ptr<Material> pMater = std::make_shared<Material>();
		pMater->SetRenderinMode(eRenderingMode::Transparent);
		pMater->SetShader(Resources::Find<Shader>(L"ObjectAnimShader"));
		Resources::Insert(L"StigamBackMater", pMater);
		mr->SetMaterial(pMater);
		Animator* pAnim = AddComponent<Animator>();
		std::shared_ptr<Texture> pAtlas = Resources::Find<Texture>(L"StigmaBack");
		pAnim->Create(L"loop", pAtlas, Vector2(0.0f, 0.0f), Vector2(80.0f, 43.0f), 11, Vector2(80.f, 80.f), Vector2::Zero, 0.13f);

		pAnim->Play(L"loop", true);
	}
	StigmaBack::~StigmaBack()
	{

	}
	void StigmaBack::Initialize()
	{
		
	}
	void StigmaBack::Update()
	{
		
	}
	void StigmaBack::LateUpdate()
	{
		
		GameObject::LateUpdate();
	}
	void StigmaBack::Render()
	{
		renderer::ObjectCB ObjectCB;
		ObjectCB.vObjectDir.x = 1;
		ObjectCB.vObjectColor = Vector4::One;

		ConstantBuffer* pConstBuffer = renderer::constantBuffer[(UINT)eCBType::Object];
		//Vector4 vPosition(m_vPosition.x, m_vPosition.y, m_vPosition.z, 1.f);
		pConstBuffer->SetData(&ObjectCB);
		pConstBuffer->Bind(eShaderStage::PS);

		GameObject::Render();
	}
}