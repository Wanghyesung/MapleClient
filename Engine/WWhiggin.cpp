#include "WWhiggin.h"
#include "WResources.h"
#include "WAnimator.h"
#include "WEffect.h"
#include "WRenderer.h"
#include "WEventManager.h"
#include "WSceneManger.h"
#include "WMuninStone.h"
namespace W
{
	Whiggin::Whiggin()
	{
		SetName(L"Whiggin");

		MeshRenderer* pRenderer = AddComponent<MeshRenderer>();
		pRenderer->SetMesh(Resources::Find<Mesh>(L"RectMesh"));


		std::shared_ptr<Material> pMater = std::make_shared<Material>();
		pMater->SetRenderinMode(eRenderingMode::Transparent);
		pMater->SetShader(Resources::Find<Shader>(L"MonsterShader"));
		Resources::Insert(L"WhigginMater", pMater);

		pRenderer->SetMaterial(pMater);

		Animator* pAnim = AddComponent<Animator>();
		pAnim->Create(L"Whiggin_stand", nullptr, Vector2(0.f, 0.f), Vector2(350.f, 500.f), 1, Vector2(1000.f, 1000.f), Vector2::Zero, Vector2(8050.f, 3500.f), 0.15f);
		pAnim->Create(L"Whiggin_start", nullptr, Vector2(0.f, 500.f), Vector2(350.f, 500.f), 11, Vector2(1000.f, 1000.f), Vector2::Zero, Vector2(8050.f, 3500.f), 0.15f);
		pAnim->Create(L"Whiggin_attack0", nullptr, Vector2(0.f, 1000.f), Vector2(350.f, 500.f), 16, Vector2(1000.f, 1000.f), Vector2::Zero, Vector2(8050.f, 3500.f), 0.15f);
		pAnim->Create(L"Whiggin_attack1", nullptr, Vector2(0.f, 1500.f), Vector2(350.f, 500.f), 23, Vector2(1000.f, 1000.f), Vector2::Zero, Vector2(8050.f, 3500.f), 0.15f);
		pAnim->Create(L"Whiggin_attack2", nullptr, Vector2(0.f, 2000.f), Vector2(350.f, 500.f), 15, Vector2(1000.f, 1000.f), Vector2::Zero, Vector2(8050.f, 3500.f), 0.15f);
		pAnim->Create(L"Whiggin_attack3", nullptr, Vector2(0.f, 2500.f), Vector2(350.f, 500.f), 18, Vector2(1000.f, 1000.f), Vector2::Zero, Vector2(8050.f, 3500.f), 0.15f);
		pAnim->Create(L"Whiggin_dead", nullptr, Vector2(0.f, 3000.f), Vector2(350.f, 500.f), 16, Vector2(1000.f, 1000.f), Vector2::Zero, Vector2(8050.f, 3500.f), 0.15f);

		MonsterAttackObject* attack1 = new MonsterAttackObject();
		attack1->SetName(L"Whiggin_attack0");
		ObjectPoolManager::AddObjectPool(attack1->GetName(), attack1);

		MuninStone* pStone = new MuninStone();
		pStone->SetName(L"Whiggin_attack1");
		ObjectPoolManager::AddObjectPool(pStone->GetName(), pStone);

		GetComponent<Transform>()->SetScale(10.f, 10.f, 0.f);
		GetComponent<Transform>()->SetPosition(-2.7f, -0.72f, -1.3f);
	}


	Whiggin::~Whiggin()
	{
		
	}
	void Whiggin::Initialize()
	{
		Animator* pAnim = GetComponent<Animator>();

		std::shared_ptr<Texture> pAtlas = Resources::Find<Texture>(L"WhigginTex");

		pAnim->SetTexture(pAtlas);	
		pAnim->Play(L"Whiggin_stand", true);
	}
	void Whiggin::Update()
	{
		
	}
	void Whiggin::LateUpdate()
	{
		
		Monster::LateUpdate();
	}
	void Whiggin::Render()
	{
		renderer::MonsterCB MonsterCB;
		MonsterCB.vMonsterDir.x = 1;

		ConstantBuffer* pConstBuffer = renderer::constantBuffer[(UINT)eCBType::Monster];
		//Vector4 vPosition(m_vPosition.x, m_vPosition.y, m_vPosition.z, 1.f);
		pConstBuffer->SetData(&MonsterCB);
		pConstBuffer->Bind(eShaderStage::PS);

		GameObject::Render();
	}

	void Whiggin::UpdateState(const wstring& _strStateName, int _iState)
	{
		Monster::UpdateState(_strStateName, _iState);
	}
	
}