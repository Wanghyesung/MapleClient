#include "WDemianVine.h"
#include "WEffect.h"
#include "WResources.h"
#include "WAnimator.h"
#include "WLight.h"
#include "WTime.h"
#include "WRenderer.h"
#include "WMonster.h"
#include "WSceneManger.h"
#include "WCameraScript.h"
#include "WWhite.h"
#include "WEventManager.h"

#include "WTransform.h"


#define CLEAR_VALUE 10
namespace W
{
	DemianVine::DemianVine()
	{
		Resources::Find<Texture>(L"vine");

		std::shared_ptr<Material> pMater = std::make_shared<Material>();
		pMater->SetRenderinMode(eRenderingMode::Transparent);
		pMater->SetShader(Resources::Find<Shader>(L"SpriteAnimationShader"));
		Resources::Insert(L"DemianVineMater", pMater);

		MeshRenderer* pRenderer = AddComponent<MeshRenderer>();
		pRenderer->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
		pRenderer->SetMaterial(pMater);

		std::shared_ptr<Texture> pAtlas = Resources::Find<Texture>(L"vine");
		Animator* pAnim = AddComponent<Animator>();
		pAnim->Create(L"vine", pAtlas, Vector2(0.0f, 0.0f), Vector2(244.f, 150.f), 9, Vector2(250.f, 250.f), Vector2::Zero, 0.15f);


	
		GetComponent<Transform>()->SetScale(18.f,18.f,0.f);

	}
	DemianVine::~DemianVine()
	{
		
	}
	void DemianVine::Initialize()
	{
		Vector3 vPosition = renderer::MainCamera->GetOwner()->GetComponent<Transform>()->GetPosition();
		vPosition.y -= 1.5f;
		vPosition.z = -3.f;
		GetComponent<Transform>()->SetPosition(vPosition);


		Animator* pAnim = GetComponent<Animator>();
		pAnim->Play(L"vine", true);
	}
	void DemianVine::Update()
	{
	}

	void DemianVine::LateUpdate()
	{
		GameObject::LateUpdate();
	}

	void DemianVine::Render()
	{
		renderer::PlayerCB PlayerCB;
		PlayerCB.vDir.x = 1;
		PlayerCB.vColor = Vector4(1.f, 1.f, 1.f, 0.4f);
		ConstantBuffer* pConstBuffer = renderer::constantBuffer[(UINT)eCBType::Player];
		//Vector4 vPosition(m_vPosition.x, m_vPosition.y, m_vPosition.z, 1.f);
		pConstBuffer->SetData(&PlayerCB);
		pConstBuffer->Bind(eShaderStage::PS);

		GameObject::Render();
	}

}