#include "WMunin.h"
#include "WResources.h"
#include "WAnimator.h"
#include "WEffect.h"

#include "WRenderer.h"
#include "WEventManager.h"
#include "WSceneManger.h"

#include "WMuninStone.h"
namespace W
{
	Munin::Munin()
	{
		SetName(L"Munin");

		MeshRenderer* pRenderer = AddComponent<MeshRenderer>();
		pRenderer->SetMesh(Resources::Find<Mesh>(L"RectMesh"));


		std::shared_ptr<Material> pMater = std::make_shared<Material>();
		pMater->SetRenderinMode(eRenderingMode::Transparent);
		pMater->SetShader(Resources::Find<Shader>(L"MonsterShader"));
		Resources::Insert(L"MuninMater", pMater);

		pRenderer->SetMaterial(pMater);

		std::shared_ptr<Texture> pAtlas = Resources::Find<Texture>(L"MuninTex");
		Animator* pAnim = AddComponent<Animator>();
		pAnim->Create(L"Munin_stand", pAtlas, Vector2(0.f, 0.f), Vector2(350.f, 500.f), 1, Vector2(1000.f, 1000.f), Vector2::Zero, 0.15f);
		pAnim->Create(L"Munin_start", pAtlas, Vector2(0.f, 500.f), Vector2(350.f, 500.f), 11, Vector2(1000.f, 1000.f), Vector2::Zero, 0.15f);
		pAnim->Create(L"Munin_attack0", pAtlas, Vector2(0.f, 1000.f), Vector2(350.f, 500.f), 16, Vector2(1000.f, 1000.f), Vector2::Zero, 0.15f);
		pAnim->Create(L"Munin_attack1", pAtlas, Vector2(0.f, 1500.f), Vector2(350.f, 500.f), 23, Vector2(1000.f, 1000.f), Vector2::Zero, 0.15f);
		pAnim->Create(L"Munin_attack2", pAtlas, Vector2(0.f, 2000.f), Vector2(350.f, 500.f), 14, Vector2(1000.f, 1000.f), Vector2::Zero, 0.15f);
		pAnim->Create(L"Munin_attack3", pAtlas, Vector2(0.f, 2500.f), Vector2(350.f, 500.f), 17, Vector2(1000.f, 1000.f), Vector2::Zero, 0.15f);
		pAnim->Create(L"Munin_dead", pAtlas, Vector2(0.f, 3000.f), Vector2(350.f, 500.f), 17, Vector2(1000.f, 1000.f), Vector2::Zero, 0.15f);

	}
	Munin::~Munin()
	{
		
	}

	void Munin::Initialize()
	{
		
	}
	void Munin::Update()
	{
		
	}
	void Munin::LateUpdate()
	{
		
		Monster::LateUpdate();
	}
	void Munin::Render()
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