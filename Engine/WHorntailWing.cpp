#include "WHorntailWing.h"
#include "WResources.h"
#include "WAnimator.h"

#include "WRenderer.h"
namespace W
{
	HorntailWing::HorntailWing(Horntail* _pOwner)
	{
		SetName(L"Wing");

		MeshRenderer* pRenderer = AddComponent<MeshRenderer>();
		pRenderer->SetMesh(Resources::Find<Mesh>(L"RectMesh"));


		std::shared_ptr<Material> pMater = std::make_shared<Material>();
		pMater->SetRenderinMode(eRenderingMode::Transparent);
		pMater->SetShader(Resources::Find<Shader>(L"MonsterShader"));
		Resources::Insert(L"horntailWingMater", pMater);

		pRenderer->SetMaterial(pMater);

		std::shared_ptr<Texture> pAtlas =
			Resources::Find<Texture>(L"WingTex");
		pAtlas->BindShaderResource(eShaderStage::PS, 12);

		Animator* pAnim = AddComponent<Animator>();
		pAnim->Create(L"Wing_stand", pAtlas, Vector2(0.f, 0.f), Vector2(1000.f, 600.f), 8, Vector2(1000.f, 1000.f), Vector2::Zero, 0.15f);
		pAnim->Create(L"Wing_attack0", pAtlas, Vector2(0.f, 600.f), Vector2(1000.f, 600.f), 10, Vector2(1000.f, 1000.f), Vector2::Zero, 0.15f);
		pAnim->FindAnimation(L"Wing_attack0")->Create(L"Wing_attack0", pAtlas, Vector2(0.f, 1200.f), Vector2(1000.f, 600.f), 11, Vector2(1000.f, 1000.f), Vector2::Zero, 0.15f);

		pAnim->Create(L"Wing_attack1", pAtlas, Vector2(0.f, 1800.f), Vector2(1000.f, 600.f), 10, Vector2(1000.f, 1000.f), Vector2::Zero, 0.15f);
		pAnim->FindAnimation(L"Wing_attack1")->Create(L"Wing_attack1", pAtlas, Vector2(0.f, 2400.f), Vector2(1000.f, 600.f), 9, Vector2(1000.f, 1000.f), Vector2::Zero, 0.15f);
		pAnim->Create(L"Wing_dead", pAtlas, Vector2(0.f, 3000.f), Vector2(1000.f, 600.f), 15, Vector2(1000.f, 1000.f), Vector2::Zero, 0.15f);
	}

	HorntailWing::~HorntailWing()
	{
	
	}
	void HorntailWing::Initialize()
	{
	
	}
	void HorntailWing::Update()
	{
		
	}
	void HorntailWing::LateUpdate()
	{
		
		Monster::LateUpdate();
	}
	void HorntailWing::Render()
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