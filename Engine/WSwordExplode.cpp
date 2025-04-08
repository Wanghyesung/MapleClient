#include "WSwordExplode.h"
#include "WResources.h"
#include "WAnimator.h"
#include "WRenderer.h"
#include "WTransform.h"

//#include "WMonsterAttackScript.h"
#include "WMonster.h",
#include "WDemianSword.h"
namespace W
{
	SwordExplode::SwordExplode()
	{
		
		std::shared_ptr<Material> pMater = std::make_shared<Material>();
		pMater->SetRenderinMode(eRenderingMode::Transparent);
		pMater->SetShader(Resources::Find<Shader>(L"ObjectAnimShader"));
		Resources::Insert(L"SwordExplodeMater", pMater);

		MeshRenderer* pRenderer = AddComponent<MeshRenderer>();
		pRenderer->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
		pRenderer->SetMaterial(pMater);


		GetComponent<Transform>()->SetScale(18.f, 18.f, 0.f);

		std::shared_ptr<Texture> pAtlas = Resources::Find<Texture>(L"swordExplodeTex");
		Animator* pAnim = AddComponent<Animator>();
		pAnim->Create(L"start", pAtlas, Vector2(0.0f, 0.0f), Vector2(614.f, 557.0f), 3, Vector2(2000.f, 2000.f), Vector2::Zero, 0.15f);
		pAnim->Create(L"explode", pAtlas, Vector2(0.0f, 557.0f), Vector2(614.f, 557.0f), 23, Vector2(2000.f, 2000.f), Vector2::Zero, 0.1f);
	}

	SwordExplode::~SwordExplode()
	{

	}

	void SwordExplode::Initialize()
	{
		GetComponent<Animator>()->Play(L"start", true);
	}

	void SwordExplode::Update()
	{
		
	}

	void SwordExplode::LateUpdate()
	{

		GameObject::LateUpdate();
	}
	void SwordExplode::Render()
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