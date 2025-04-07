#include "WArielLaser.h"
#include "WResources.h"
#include "WAnimator.h"
#include "WRenderer.h"
#include "WObject.h"
#include "WMonster.h"
namespace W
{
	ArielLaser::ArielLaser()
	{
		std::shared_ptr<Material> pMater = std::make_shared<Material>();
		pMater->SetRenderinMode(eRenderingMode::Transparent);
		pMater->SetShader(Resources::Find<Shader>(L"ObjectAnimShader"));
		Resources::Insert(L"ArileStoneMater", pMater);

		MeshRenderer* pRenderer = AddComponent<MeshRenderer>();
		pRenderer->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
		pRenderer->SetMaterial(pMater);

		GetComponent<Transform>()->SetScale(8.5f, 8.5f, 0.f);

		std::shared_ptr<Texture> pAtlas = Resources::Find<Texture>(L"Ariel_attack0");
		Animator* pAnim = AddComponent<Animator>();
		pAnim->Create(L"Laser", pAtlas, Vector2(0.0f, 0.0f), Vector2(189.f, 847.0f), 20, Vector2(850.f, 850.f), Vector2::Zero, 0.15f);

		pAnim->Play(L"Laser", true);

	}
	ArielLaser::~ArielLaser()
	{

	}
	void ArielLaser::Initialize()
	{
		
	}
	void ArielLaser::Update()
	{
		GameObject::Update();
	}
	void ArielLaser::LateUpdate()
	{
		GameObject::LateUpdate();
	}
	void ArielLaser::Render()
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