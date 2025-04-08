#include "WHorntailLeg.h"
#include "WResources.h"
#include "WAnimator.h"
#include "WRenderer.h"
#include "WEffect.h"
#include "WSceneManger.h"
#include "WEventManager.h"
namespace W
{
	HorntailLeg::HorntailLeg()
	{
		SetName(L"Leg");

		MeshRenderer* pRenderer = AddComponent<MeshRenderer>();
		pRenderer->SetMesh(Resources::Find<Mesh>(L"RectMesh"));


		std::shared_ptr<Material> pMater = std::make_shared<Material>();
		pMater->SetRenderinMode(eRenderingMode::Transparent);
		pMater->SetShader(Resources::Find<Shader>(L"MonsterShader"));
		Resources::Insert(L"horntailLegMater", pMater);

		pRenderer->SetMaterial(pMater);

		std::shared_ptr<Texture> pAtlas =
			Resources::Find<Texture>(L"LegTex");
		pAtlas->BindShaderResource(eShaderStage::PS, 12);

		Animator* pAnim = AddComponent<Animator>();
		pAnim->Create(L"Leg_stand", pAtlas, Vector2(0.f, 0.f), Vector2(600.f, 300.f), 1, Vector2(1000.f, 1000.f), Vector2::Zero, 0.15f);
		pAnim->Create(L"Leg_attack0", pAtlas, Vector2(0.f, 300.f), Vector2(600.f, 300.f), 14, Vector2(1000.f, 1000.f), Vector2::Zero, 0.15f);
		pAnim->Create(L"Leg_attack1", pAtlas, Vector2(0.f, 600.f), Vector2(600.f, 300.f), 18, Vector2(1000.f, 1000.f), Vector2::Zero, 0.15f);
		pAnim->Create(L"Leg_dead", pAtlas, Vector2(0.f, 900.f), Vector2(600.f, 300.f), 14, Vector2(1000.f, 1000.f), Vector2::Zero, 0.15f);

	}
	HorntailLeg::~HorntailLeg()
	{
		
	}


	void HorntailLeg::Initialize()
	{
		
	}
	void HorntailLeg::Update()
	{
		
	}
	void HorntailLeg::LateUpdate()
	{
		
		Monster::LateUpdate();
	}
	void HorntailLeg::Render()
	{
		renderer::MonsterCB MonsterCB;
		MonsterCB.vMonsterDir.x = 1;

		ConstantBuffer* pConstBuffer = renderer::constantBuffer[(UINT)eCBType::Monster];
		//Vector4 vPosition(m_vPosition.x, m_vPosition.y, m_vPosition.z, 1.f);
		pConstBuffer->SetData(&MonsterCB);
		pConstBuffer->Bind(eShaderStage::PS);

		GameObject::Render();
	}
	
}