#include "WHorntailLeftHand.h"
#include "WRenderer.h"
#include "WResources.h"
#include "WAnimator.h"
#include "WSceneManger.h"
#include "WSpear.h"
#include "WEventManager.h"

namespace W
{
	HorntailLeftHand::HorntailLeftHand()
	{
		SetName(L"LeftHand");

		MeshRenderer* pRenderer = AddComponent<MeshRenderer>();
		pRenderer->SetMesh(Resources::Find<Mesh>(L"RectMesh"));


		std::shared_ptr<Material> pMater = std::make_shared<Material>();
		pMater->SetRenderinMode(eRenderingMode::Transparent);
		pMater->SetShader(Resources::Find<Shader>(L"MonsterShader"));
		Resources::Insert(L"horntailLeftHandMater", pMater);

		pRenderer->SetMaterial(pMater);

	

		Animator* pAnim = AddComponent<Animator>();
		pAnim->Create(L"LeftHand_stand", nullptr, Vector2(0.f, 0.f), Vector2(500.f, 300.f), 5, Vector2(1000.f, 1000.f), Vector2::Zero, Vector2(9000.f, 1500.f), 0.15f);
		pAnim->Create(L"LeftHand_attack0", nullptr, Vector2(0.f, 300.f), Vector2(500.f, 300.f), 18, Vector2(1000.f, 1000.f), Vector2::Zero, Vector2(9000.f, 1500.f), 0.15f);
		pAnim->Create(L"LeftHand_attack1", nullptr, Vector2(0.f, 600.f), Vector2(500.f, 300.f), 16, Vector2(1000.f, 1000.f), Vector2::Zero, Vector2(9000.f, 1500.f), 0.15f);
		pAnim->Create(L"LeftHand_attack2", nullptr, Vector2(0.f, 900.f), Vector2(500.f, 300.f), 17, Vector2(1000.f, 1000.f), Vector2::Zero, Vector2(9000.f, 1500.f), 0.15f);
		pAnim->Create(L"LeftHand_dead", nullptr, Vector2(0.f, 1200.f), Vector2(500.f, 300.f), 16, Vector2(1000.f, 1000.f), Vector2::Zero, Vector2(9000.f, 1500.f), 0.15f);

		Spear* pSpear = new Spear();
		pSpear->SetName(L"spear");
		ObjectPoolManager::AddObjectPool(pSpear->GetName(), pSpear);

	}
	HorntailLeftHand::~HorntailLeftHand()
	{
	
	}

	
	void HorntailLeftHand::Initialize()
	{
		std::shared_ptr<Texture> pAtlas = Resources::Find<Texture>(L"LeftHandTex");
		Animator* pAnimator = GetComponent<Animator>();
		pAnimator->SetTexture(pAtlas);
	}
	void HorntailLeftHand::Update()
	{
		
	}

	void HorntailLeftHand::LateUpdate()
	{
		Monster::LateUpdate();
	}

	void HorntailLeftHand::Render()
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