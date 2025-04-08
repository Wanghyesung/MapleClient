#include "WHorntailRightHand.h"
#include "WRenderer.h"
#include "WResources.h"
#include "WAnimator.h"
#include "WSceneManger.h"
#include "WSpear.h"

namespace W
{
	HorntailRightHand::HorntailRightHand()
	{
		SetName(L"RightHand");

		MeshRenderer* pRenderer = AddComponent<MeshRenderer>();
		pRenderer->SetMesh(Resources::Find<Mesh>(L"RectMesh"));


		std::shared_ptr<Material> pMater = std::make_shared<Material>();
		pMater->SetRenderinMode(eRenderingMode::Transparent);
		pMater->SetShader(Resources::Find<Shader>(L"MonsterShader"));
		Resources::Insert(L"horntailLeftHandMater", pMater);

		pRenderer->SetMaterial(pMater);

		std::shared_ptr<Texture> pAtlas =
			Resources::Find<Texture>(L"RightHandTex");
		pAtlas->BindShaderResource(eShaderStage::PS, 12);

		Animator* pAnim = AddComponent<Animator>();
		pAnim->Create(L"RightHand_stand", pAtlas, Vector2(0.f, 0.f), Vector2(500.f, 300.f), 5, Vector2(1000.f, 1000.f), Vector2::Zero, 0.15f);
		pAnim->Create(L"RightHand_attack0", pAtlas, Vector2(0.f, 300.f), Vector2(500.f, 300.f), 18, Vector2(1000.f, 1000.f), Vector2::Zero, 0.15f);
		pAnim->Create(L"RightHand_attack1", pAtlas, Vector2(0.f, 600.f), Vector2(500.f, 300.f), 17, Vector2(1000.f, 1000.f), Vector2::Zero, 0.15f);
		pAnim->Create(L"RightHand_attack2", pAtlas, Vector2(0.f, 900.f), Vector2(500.f, 300.f), 16, Vector2(1000.f, 1000.f), Vector2::Zero, 0.15f);
		pAnim->Create(L"RightHand_dead", pAtlas, Vector2(0.f, 1200.f), Vector2(500.f, 300.f), 16, Vector2(1000.f, 1000.f), Vector2::Zero, 0.15f);

	}
	HorntailRightHand::~HorntailRightHand()
	{

	}

	
	void HorntailRightHand::Initialize()
	{
		
	}
	void HorntailRightHand::Update()
	{
		
	}
	void HorntailRightHand::LateUpdate()
	{
		
		Monster::LateUpdate();

	}
	void HorntailRightHand::Render()
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