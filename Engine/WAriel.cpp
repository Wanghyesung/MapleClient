#include "WAriel.h"
#include "WResources.h"
#include "WAnimator.h"
#include "WEffect.h"
#include "WRenderer.h"
#include "WEventManager.h"
#include "WSceneManger.h"
#include "WArielLaser.h"
#include "WArielStone.h"
#include "WPullObject.h"
#include "WPinkBean.h"
namespace W
{
	Ariel::Ariel()
	{
		SetName(L"Ariel");

		MeshRenderer* pRenderer = AddComponent<MeshRenderer>();
		pRenderer->SetMesh(Resources::Find<Mesh>(L"RectMesh"));


		std::shared_ptr<Material> pMater = std::make_shared<Material>();
		pMater->SetRenderinMode(eRenderingMode::Transparent);
		pMater->SetShader(Resources::Find<Shader>(L"MonsterShader"));
		Resources::Insert(L"ArielMater", pMater);

		pRenderer->SetMaterial(pMater);

		std::shared_ptr<Texture> pAtlas =
			Resources::Load<Texture>(L"ArielTex", L"..\\Resources\\Texture\\Monster\\Pinkbean\\Ariel\\Ariel.png");
		Animator* pAnim = AddComponent<Animator>();
		pAnim->Create(L"Ariel_stand", pAtlas, Vector2(0.f, 0.f), Vector2(400.f, 400.f), 1, Vector2(1000.f, 1000.f), Vector2::Zero, 0.15f);
		pAnim->Create(L"Ariel_start", pAtlas, Vector2(0.f, 400.f), Vector2(400.f, 400.f), 11, Vector2(1000.f, 1000.f), Vector2::Zero, 0.15f);
		pAnim->Create(L"Ariel_attack0", pAtlas, Vector2(0.f, 800.f), Vector2(400.f, 400.f), 16, Vector2(1000.f, 1000.f), Vector2::Zero, 0.15f);
		pAnim->Create(L"Ariel_attack1", pAtlas, Vector2(0.f, 1200.f), Vector2(400.f, 400.f), 23, Vector2(1000.f, 1000.f), Vector2::Zero, 0.15f);
		pAnim->Create(L"Ariel_attack2", pAtlas, Vector2(0.f, 1600.f), Vector2(400.f, 400.f), 14, Vector2(1000.f, 1000.f), Vector2::Zero, 0.15f);
		pAnim->Create(L"Ariel_attack3", pAtlas, Vector2(0.f, 2000.f), Vector2(400.f, 400.f), 17, Vector2(1000.f, 1000.f), Vector2::Zero, 0.15f);
		pAnim->Create(L"Ariel_dead", pAtlas, Vector2(0.f, 2400.f), Vector2(400.f, 400.f), 17, Vector2(1000.f, 1000.f), Vector2::Zero, 0.15f);
	}

	Ariel::~Ariel()
	{
		
	}
	

	void Ariel::Initialize()
	{
		
	}

	void Ariel::Update()
	{
		
	}

	void Ariel::LateUpdate()
	{
		
		Monster::LateUpdate();
	}
	void Ariel::Render()
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