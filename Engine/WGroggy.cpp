#include "WGroggy.h"
#include "WResources.h"
#include "WRenderer.h"
#include "WAnimator.h"
#include "WEventManager.h"
#include "WBattleManager.h"
namespace W
{
	Groggy::Groggy()
	{
		std::shared_ptr<Material> pMater = std::make_shared<Material>();
		pMater->SetShader(Resources::Find<Shader>(L"ObjectAnimShader"));
		//pMater->SetTexture(pTex);
		Resources::Insert(L"GroggyMater", pMater);
		pMater->SetRenderinMode(eRenderingMode::Transparent);

		MeshRenderer* pRenderer = AddComponent<MeshRenderer>();
		pRenderer->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
		pRenderer->SetMaterial(pMater);

		GetComponent<Transform>()->SetScale(2.f, 2.f, 0.f);

		std::shared_ptr<Texture> pAtlas =
			Resources::Load<Texture>(L"groggyTex", L"..\\Resources\\Texture\\Abnormal\\groggy.png");
		Animator* pAnim = AddComponent<Animator>();
		pAnim->Create(L"groggy", pAtlas, Vector2(0.0f, 0.0f), Vector2(129.0f, 67.0f), 8, Vector2(139.f, 130.f), Vector2::Zero, 0.2f);

		pAnim->Play(L"groggy", true);

	}
	Groggy::~Groggy()
	{

	}
	void Groggy::Initialize()
	{
		
	}
	void Groggy::Update()
	{
		GameObject::Update();
	}

	void Groggy::LateUpdate()
	{
		Abnormal::LateUpdate();
	}

	void Groggy::Render()
	{
		renderer::ObjectCB ObjectCB;
		ObjectCB.vObjectDir.x = -1;
		ObjectCB.vObjectColor = Vector4::One;

		ConstantBuffer* pConstBuffer = renderer::constantBuffer[(UINT)eCBType::Object];
		//Vector4 vPosition(m_vPosition.x, m_vPosition.y, m_vPosition.z, 1.f);
		pConstBuffer->SetData(&ObjectCB);
		pConstBuffer->Bind(eShaderStage::PS);

		Abnormal::Render();
	}
	void Groggy::Restore()
	{
		EventManager::Restore(m_pTarget, BattleManager::eAbnormalType::InputKey);
	}
}