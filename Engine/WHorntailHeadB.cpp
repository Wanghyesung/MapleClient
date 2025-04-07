#include "WHorntailHeadB.h"
#include "WResources.h"
#include "WAnimator.h"
#include "WRenderer.h"
#include "WFire.h"
#include "WSceneManger.h"
#include "WEffect.h"
#include "WEventManager.h"

namespace W
{
	HorntailHeadB::HorntailHeadB(Horntail* _pOwner) 
	{
		SetName(L"HeadB");

		MeshRenderer* pRenderer = AddComponent<MeshRenderer>();
		pRenderer->SetMesh(Resources::Find<Mesh>(L"RectMesh"));


		std::shared_ptr<Material> pMater = std::make_shared<Material>();
		pMater->SetRenderinMode(eRenderingMode::Transparent);
		pMater->SetShader(Resources::Find<Shader>(L"MonsterShader"));
		Resources::Insert(L"horntailHeadBMater", pMater);

		pRenderer->SetMaterial(pMater);

		std::shared_ptr<Texture> pAtlas =
			Resources::Find<Texture>(L"HeadBTex");
		Animator* pAnim = AddComponent<Animator>();
		pAnim->Create(L"HeadB_stand", pAtlas, Vector2(0.f, 0.f), Vector2(500.f, 800.f), 10, Vector2(1000.f, 1000.f), Vector2::Zero, 0.15f);
		pAnim->Create(L"HeadB_attack0", pAtlas, Vector2(0.f, 800.f), Vector2(500.f, 800.f), 26, Vector2(1000.f, 1000.f), Vector2::Zero, 0.15f);
		pAnim->Create(L"HeadB_attack1", pAtlas, Vector2(0.f, 1600.f), Vector2(500.f, 800.f), 15, Vector2(1000.f, 1000.f), Vector2::Zero, 0.15f);
		pAnim->Create(L"HeadB_attack2", pAtlas, Vector2(0.f, 2400.f), Vector2(500.f, 800.f), 13, Vector2(1000.f, 1000.f), Vector2::Zero, 0.15f);
		pAnim->Create(L"HeadB_dead", pAtlas, Vector2(0.f, 3200.f), Vector2(500.f, 800.f), 14, Vector2(1000.f, 1000.f), Vector2::Zero, 0.15f);

		//pAnim->Play(L"HeadA_stand", true);
	}

	HorntailHeadB::~HorntailHeadB()
	{
		
	}


	void HorntailHeadB::Initialize()
	{


	}

	void HorntailHeadB::Update()
	{
		
	}

	void HorntailHeadB::LateUpdate()
	{

		Monster::LateUpdate();
	}

	void HorntailHeadB::Render()
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