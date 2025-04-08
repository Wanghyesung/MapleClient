#include "WRexThunder.h"
#include "WSceneManger.h"
#include "WResources.h"
#include "WAnimator.h"
#include "WRenderer.h"
#include "WTransform.h"

#include "WMonster.h"

namespace W
{
	RexThunder::RexThunder() 
	{
		std::shared_ptr<Material> pMater = std::make_shared<Material>();
		pMater->SetRenderinMode(eRenderingMode::Transparent);
		pMater->SetShader(Resources::Find<Shader>(L"ObjectAnimShader"));
		Resources::Insert(L"RexThunderMater", pMater);

		MeshRenderer* pRenderer = AddComponent<MeshRenderer>();
		pRenderer->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
		pRenderer->SetMaterial(pMater);

		
		GetComponent<Transform>()->SetScale(8.f, 8.f, 0.f);

		std::shared_ptr<Texture> pAtlas =
			Resources::Find<Texture>(L"Rex_attack1");
		Animator* pAnim = AddComponent<Animator>();
		pAnim->Create(L"Thunder_left", pAtlas, Vector2(0.0f, 0.0f), Vector2(174.f, 821.0f), 5, Vector2(800.f, 800.f), Vector2::Zero, 0.3f);

		pAnim->Play(L"Thunder_left", true);

	}

	RexThunder::~RexThunder()
	{

	}

	void RexThunder::Initialize()
	{
		
	}
	void RexThunder::Update()
	{
		
	}
	void RexThunder::LateUpdate()
	{
		
		GameObject::LateUpdate();
	}
	void RexThunder::Render()
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