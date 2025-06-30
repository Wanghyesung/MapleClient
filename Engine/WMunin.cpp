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

		Animator* pAnim = AddComponent<Animator>();
		pAnim->Create(L"Munin_stand", nullptr, Vector2(0.f, 0.f), Vector2(350.f, 500.f), 1, Vector2(1000.f, 1000.f), Vector2::Zero, Vector2(8050.f, 3500.f), 0.15f);
		pAnim->Create(L"Munin_start", nullptr, Vector2(0.f, 500.f), Vector2(350.f, 500.f), 11, Vector2(1000.f, 1000.f), Vector2::Zero, Vector2(8050.f, 3500.f), 0.15f);
		pAnim->Create(L"Munin_attack0", nullptr, Vector2(0.f, 1000.f), Vector2(350.f, 500.f), 16, Vector2(1000.f, 1000.f), Vector2::Zero, Vector2(8050.f, 3500.f), 0.15f);
		pAnim->Create(L"Munin_attack1", nullptr, Vector2(0.f, 1500.f), Vector2(350.f, 500.f), 23, Vector2(1000.f, 1000.f), Vector2::Zero,  Vector2(8050.f, 3500.f),0.15f);
		pAnim->Create(L"Munin_attack2", nullptr, Vector2(0.f, 2000.f), Vector2(350.f, 500.f), 14, Vector2(1000.f, 1000.f), Vector2::Zero,  Vector2(8050.f, 3500.f),0.15f);
		pAnim->Create(L"Munin_attack3", nullptr, Vector2(0.f, 2500.f), Vector2(350.f, 500.f), 17, Vector2(1000.f, 1000.f), Vector2::Zero,  Vector2(8050.f, 3500.f),0.15f);
		pAnim->Create(L"Munin_dead", nullptr, Vector2(0.f, 3000.f), Vector2(350.f, 500.f), 17, Vector2(1000.f, 1000.f), Vector2::Zero, Vector2(8050.f, 3500.f), 0.15f);

		MonsterAttackObject* attack1 = new MonsterAttackObject();
		attack1->SetName(L"Munin_attack0");
		ObjectPoolManager::AddObjectPool(attack1->GetName(), attack1);

		MuninStone* pStone = new MuninStone();
		pStone->SetName(L"Munin_attack1");
		ObjectPoolManager::AddObjectPool(pStone->GetName(), pStone);


		GetComponent<Transform>()->SetScale(10.f, 10.f, 0.f);
		GetComponent<Transform>()->SetPosition(2.7f, -0.75f, -1.3f);
	}
	Munin::~Munin()
	{
		
	}

	void Munin::Initialize()
	{
		std::shared_ptr<Texture> pAtlas = Resources::Find<Texture>(L"MuninTex");
		GetComponent<Animator>()->SetTexture(pAtlas);
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
		pConstBuffer->SetData(&MonsterCB);
		pConstBuffer->Bind(eShaderStage::PS);

		GameObject::Render();
	}

	void Munin::UpdateState(const wstring& _strStateName, int _iState)
	{
		Monster::UpdateState(_strStateName, _iState);
	}
	
}