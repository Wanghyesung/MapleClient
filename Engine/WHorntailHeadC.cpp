#include "WHorntailHeadC.h"
#include "WResources.h"
#include "WAnimator.h"
#include "WRenderer.h"

#include "WThunder.h"
#include "WSceneManger.h"
#include "WEffect.h"
#include "WEventManager.h"
namespace W
{
	HorntailHeadC::HorntailHeadC(Horntail* _pOwner) 
	{
		SetName(L"HeadC");

		MeshRenderer* pRenderer = AddComponent<MeshRenderer>();
		pRenderer->SetMesh(Resources::Find<Mesh>(L"RectMesh"));


		std::shared_ptr<Material> pMater = std::make_shared<Material>();
		pMater->SetRenderinMode(eRenderingMode::Transparent);
		pMater->SetShader(Resources::Find<Shader>(L"MonsterShader"));
		Resources::Insert(L"horntailHeadCMater", pMater);

		pRenderer->SetMaterial(pMater);

		std::shared_ptr<Texture> pAtlas =
			Resources::Find<Texture>(L"HeadCTex");
		pAtlas->BindShaderResource(eShaderStage::PS, 12);

		Animator* pAnim = AddComponent<Animator>();
		pAnim->Create(L"HeadC_stand", pAtlas, Vector2(0.f, 0.f), Vector2(600.f, 700.f), 10, Vector2(1000.f, 1000.f), Vector2::Zero, 0.15f);
		pAnim->Create(L"HeadC_attack0", pAtlas, Vector2(0.f, 700.f), Vector2(600.f, 700.f), 23, Vector2(1000.f, 1000.f), Vector2::Zero, 0.15f);
		pAnim->Create(L"HeadC_attack1", pAtlas, Vector2(0.f, 1400.f), Vector2(600.f, 700.f), 18, Vector2(1000.f, 1000.f), Vector2::Zero, 0.15f);
		pAnim->Create(L"HeadC_attack2", pAtlas, Vector2(0.f, 2100.f), Vector2(600.f, 700.f), 14, Vector2(1000.f, 1000.f), Vector2::Zero, 0.15f);
		pAnim->Create(L"HeadC_dead", pAtlas, Vector2(0.f, 2800.f), Vector2(600.f, 700.f), 13, Vector2(1000.f, 1000.f), Vector2::Zero, 0.15f);
		
	}

	HorntailHeadC::~HorntailHeadC()
	{
		
	}

	
	void HorntailHeadC::Initialize()
	{
		
	}

	void HorntailHeadC::Update()
	{
		
	}

	void HorntailHeadC::LateUpdate()
	{
		
		Monster::LateUpdate();
	}

	void HorntailHeadC::Render()
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