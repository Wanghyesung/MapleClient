#include "WMuninStone.h"
#include "WResources.h"
#include "WAnimator.h"
#include "WRenderer.h"
#include "WTransform.h"

#include "WMonster.h"
namespace W
{
	MuninStone::MuninStone() 
	{
		std::shared_ptr<Material> pMater = std::make_shared<Material>();
		pMater->SetRenderinMode(eRenderingMode::Transparent);
		pMater->SetShader(Resources::Find<Shader>(L"ObjectAnimShader"));
		Resources::Insert(L"MuninStoneMater", pMater);

		MeshRenderer* pRenderer = AddComponent<MeshRenderer>();
		pRenderer->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
		pRenderer->SetMaterial(pMater);

		GetComponent<Transform>()->SetScale(6.f, 6.f, 0.f);

		std::shared_ptr<Texture> pAtlas = Resources::Find<Texture>(L"MuninStoneTex");
		Animator* pAnim = AddComponent<Animator>();
		pAnim->Create(L"Stone_left", pAtlas, Vector2(0.0f, 0.0f), Vector2(145.f, 514.0f), 20, Vector2(510.f, 510.f), Vector2::Zero, 0.15f);

		pAnim->Play(L"Stone_left", true);

	}
	MuninStone::~MuninStone()
	{
	}
	void MuninStone::Initialize()
	{
		
	}
	void MuninStone::Update()
	{
		
	}
	void MuninStone::LateUpdate()
	{
		
		GameObject::LateUpdate();
	}
	void MuninStone::Render()
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