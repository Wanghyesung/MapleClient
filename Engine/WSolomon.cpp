#include "WSolomon.h"
#include "WResources.h"
#include "WAnimator.h"
#include "WEffect.h"

#include "WRenderer.h"
#include "WEventManager.h"
#include "WSceneManger.h"
#include "WSolThunder.h"
#include "WTransform.h"
namespace W
{
	Solomon::Solomon()
	{
		SetName(L"Solomon");

		MeshRenderer* pRenderer = AddComponent<MeshRenderer>();
		pRenderer->SetMesh(Resources::Find<Mesh>(L"RectMesh"));


		std::shared_ptr<Material> pMater = std::make_shared<Material>();
		pMater->SetRenderinMode(eRenderingMode::Transparent);
		pMater->SetShader(Resources::Find<Shader>(L"MonsterShader"));
		Resources::Insert(L"SolomonMater", pMater);

		pRenderer->SetMaterial(pMater);

		std::shared_ptr<Texture> pAtlas = Resources::Find<Texture>(L"SolomonTex");
		Animator* pAnim = AddComponent<Animator>();
		pAnim->Create(L"Solomon_stand", pAtlas, Vector2(0.f, 0.f), Vector2(500.f, 1000.f), 1, Vector2(1000.f, 1000.f), Vector2::Zero, 0.15f);
		pAnim->Create(L"Solomon_start", pAtlas, Vector2(0.f, 1000.f), Vector2(500.f, 1000.f), 10, Vector2(1000.f, 1000.f), Vector2::Zero, 0.15f);
		pAnim->Create(L"Solomon_attack0", pAtlas, Vector2(0.f, 2000.f), Vector2(500.f, 1000.f), 18, Vector2(1000.f, 1000.f), Vector2::Zero, 0.15f);
		pAnim->Create(L"Solomon_attack1", pAtlas, Vector2(0.f, 3000.f), Vector2(500.f, 1000.f), 20, Vector2(1000.f, 1000.f), Vector2::Zero, 0.15f);
		pAnim->Create(L"Solomon_attack2", pAtlas, Vector2(0.f, 4000.f), Vector2(500.f, 1000.f), 19, Vector2(1000.f, 1000.f), Vector2::Zero, 0.15f);
		pAnim->Create(L"Solomon_dead", pAtlas, Vector2(0.f, 5000.f), Vector2(500.f, 1000.f), 16, Vector2(1000.f, 1000.f), Vector2::Zero, 0.15f);
	}
	Solomon::~Solomon()
	{
	}



	void Solomon::Initialize()
	{
		GetComponent<Transform>()->SetScale(10.f, 10.f, 0.f);
		GetComponent<Transform>()->SetPosition(-5.32f, 2.05f, -1.3f);
		
	}
	void Solomon::Update()
	{
		
	}
	void Solomon::LateUpdate()
	{
		Monster::LateUpdate();
	}
	void Solomon::Render()
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