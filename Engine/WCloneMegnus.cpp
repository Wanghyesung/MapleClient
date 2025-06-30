#include "WCloneMegnus.h"
#include "WResources.h"
#include "WAnimator.h"
#include "WMonster.h"
#include "WSceneManger.h"
#include "WRenderer.h"
#include "WTransform.h"

namespace W
{
	CloneMegnus::CloneMegnus()
	{
		std::shared_ptr<Material> pMater = std::make_shared<Material>();
		pMater->SetRenderinMode(eRenderingMode::Transparent);
		pMater->SetShader(Resources::Find<Shader>(L"ObjectAnimShader"));
		Resources::Insert(L"CloneMegnusMater", pMater);

		MeshRenderer* pRenderer = AddComponent<MeshRenderer>();
		pRenderer->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
		pRenderer->SetMaterial(pMater);

		GetComponent<Transform>()->SetScale(10.f, 10.f, 0.f);

		Animator* pAnim = AddComponent<Animator>();
		pAnim->Create(L"Clone_Megnus", nullptr, Vector2(0.0f, 0.0f), Vector2(408.f, 354.0f), 27, Vector2(1100.f, 1100.f), Vector2::Zero, Vector2(11016.f, 354.f), 0.15f);

		//pAnim->Play(L"Clone_Megnus", true);
	}
	CloneMegnus::~CloneMegnus()
	{
		
	}
	void CloneMegnus::Initialize()
	{
		std::shared_ptr<Texture> pAtlas = Resources::Find<Texture>(L"Megnus_attack1_effect");
		GetComponent<Animator>()->SetTexture(pAtlas);
	}
	void CloneMegnus::Update()
	{
		
	}
	void CloneMegnus::LateUpdate()
	{
		
		GameObject::LateUpdate();
	}
	void CloneMegnus::Render()
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

	void CloneMegnus::UpdateState(const wstring& _strStateName, int _iState)
	{
		MonsterAttackObject::UpdateState(_strStateName, _iState);
	}
	
}