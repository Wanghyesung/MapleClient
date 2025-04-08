#include "WArielStone.h"
#include "WResources.h"
#include "WAnimator.h"
#include "WRenderer.h"
#include "WTransform.h"
#include "WMonster.h"
namespace W
{
	ArielStone::ArielStone()
	{
		std::shared_ptr<Material> pMater = std::make_shared<Material>();
		pMater->SetRenderinMode(eRenderingMode::Transparent);
		pMater->SetShader(Resources::Find<Shader>(L"ObjectAnimShader"));
		Resources::Insert(L"ArielStoneStoneMater", pMater);

		MeshRenderer* pRenderer = AddComponent<MeshRenderer>();
		pRenderer->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
		pRenderer->SetMaterial(pMater);

		GetComponent<Transform>()->SetScale(6.f, 6.f, 0.f);

		std::shared_ptr<Texture> pAtlas = Resources::Find<Texture>(L"Ariel_attack1");
		Animator* pAnim = AddComponent<Animator>();
		pAnim->Create(L"Stone", pAtlas, Vector2(0.0f, 0.0f), Vector2(306.f, 512.0f), 18, Vector2(510.f, 510.f), Vector2::Zero, 0.15f);

		pAnim->Play(L"Stone", true);

	}
	ArielStone::~ArielStone()
	{
	}

	void ArielStone::Initialize()
	{
		
	}
	void ArielStone::Update()
	{
		GameObject::Update();
	}
	void ArielStone::LateUpdate()
	{
		
		GameObject::LateUpdate();
	}
	void ArielStone::Render()
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