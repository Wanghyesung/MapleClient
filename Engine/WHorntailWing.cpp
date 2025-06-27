#include "WHorntailWing.h"
#include "WResources.h"
#include "WAnimator.h"

#include "WRenderer.h"
namespace W
{
	HorntailWing::HorntailWing()
	{
		SetRender(false);

		SetName(L"Wing");

		MeshRenderer* pRenderer = AddComponent<MeshRenderer>();
		pRenderer->SetMesh(Resources::Find<Mesh>(L"RectMesh"));


		std::shared_ptr<Material> pMater = std::make_shared<Material>();
		pMater->SetRenderinMode(eRenderingMode::Transparent);
		pMater->SetShader(Resources::Find<Shader>(L"MonsterShader"));
		Resources::Insert(L"horntailWingMater", pMater);

		pRenderer->SetMaterial(pMater);


		Animator* pAnim = AddComponent<Animator>();
		pAnim->Create(L"Wing_stand", nullptr, Vector2(0.f, 0.f), Vector2(1000.f, 600.f), 8, Vector2(1000.f, 1000.f), Vector2::Zero, Vector2(15000.f, 3600.f), 0.15f);
		pAnim->Create(L"Wing_attack0", nullptr, Vector2(0.f, 600.f), Vector2(1000.f, 600.f), 10, Vector2(1000.f, 1000.f), Vector2::Zero, Vector2(15000.f, 3600.f), 0.15f);
		pAnim->FindAnimation(L"Wing_attack0")->Create(L"Wing_attack0", nullptr, Vector2(0.f, 1200.f), Vector2(1000.f, 600.f), 11, Vector2(1000.f, 1000.f), Vector2::Zero, Vector2(15000.f, 3600.f), 0.15f);

		pAnim->Create(L"Wing_attack1", nullptr, Vector2(0.f, 1800.f), Vector2(1000.f, 600.f), 10, Vector2(1000.f, 1000.f), Vector2::Zero, Vector2(15000.f, 3600.f), 0.15f);
		pAnim->FindAnimation(L"Wing_attack1")->Create(L"Wing_attack1", nullptr, Vector2(0.f, 2400.f), Vector2(1000.f, 600.f), 9, Vector2(1000.f, 1000.f), Vector2::Zero, Vector2(15000.f, 3600.f), 0.15f);
		pAnim->Create(L"Wing_dead", nullptr, Vector2(0.f, 3000.f), Vector2(1000.f, 600.f), 15, Vector2(1000.f, 1000.f), Vector2::Zero, Vector2(15000.f, 3600.f), 0.15f);

		GetComponent<Transform>()->SetScale(11.f, 11.f, 0.f);
	}

	HorntailWing::~HorntailWing()
	{
	
	}
	void HorntailWing::Initialize()
	{
		std::shared_ptr<Texture> pAtlas = Resources::Find<Texture>(L"WingTex");
		Animator* pAnimator = GetComponent<Animator>();
		pAnimator->SetTexture(pAtlas);
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
	
	void HorntailWing::UpdateState(const wstring& _strStateName, int _iState)
	{
		Monster::UpdateState(_strStateName, _iState);
	}
}