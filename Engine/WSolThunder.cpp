#include "WSolThunder.h"
#include "WSceneManger.h"
#include "WResources.h"
#include "WAnimator.h"
#include "WRenderer.h"
#include "WObject.h"
#include "WMonster.h"
namespace W
{
	SolThunder::SolThunder()
	{
		std::shared_ptr<Material> pMater = std::make_shared<Material>();
		pMater->SetRenderinMode(eRenderingMode::Transparent);
		pMater->SetShader(Resources::Find<Shader>(L"ObjectAnimShader"));
		Resources::Insert(L"SolThunderMater", pMater);

		MeshRenderer* pRenderer = AddComponent<MeshRenderer>();
		pRenderer->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
		pRenderer->SetMaterial(pMater);

		GetComponent<Transform>()->SetScale(8.f, 8.f, 0.f);

		std::shared_ptr<Texture> pAtlas =
			Resources::Find<Texture>(L"Solomon_attack1");
		Animator* pAnim = AddComponent<Animator>();
		pAnim->Create(L"Thunder_left", pAtlas, Vector2(0.0f, 0.0f), Vector2(172.f, 817.0f), 5, Vector2(800.f, 800.f), Vector2::Zero, 0.3f);
	
		pAnim->Play(L"Thunder_left", true);

	}

	SolThunder::~SolThunder()
	{

	}

	void SolThunder::Initialize()
	{
		
	}
	void SolThunder::Update()
	{
		
	}
	void SolThunder::LateUpdate()
	{
		
		GameObject::LateUpdate();
	}
	void SolThunder::Render()
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