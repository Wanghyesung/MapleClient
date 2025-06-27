#include "WHorntailHeadA.h"
#include "WResources.h"
#include "WAnimator.h"
#include "WRenderer.h"
#include "WIce.h"
#include "WSceneManger.h"
#include "WEffect.h"
#include "WEventManager.h"

namespace W
{
	HorntailHeadA::HorntailHeadA()
	{
		SetRender(false);

		SetName(L"HeadA");

		MeshRenderer* pRenderer = AddComponent<MeshRenderer>();
		pRenderer->SetMesh(Resources::Find<Mesh>(L"RectMesh"));


		std::shared_ptr<Material> pMater = std::make_shared<Material>();
		pMater->SetRenderinMode(eRenderingMode::Transparent);
		pMater->SetShader(Resources::Find<Shader>(L"MonsterShader"));
		Resources::Insert(L"horntailMater", pMater);

		pRenderer->SetMaterial(pMater);

		//std::shared_ptr<Texture> pAtlas = Resources::Find<Texture>(L"HeadATex");
		Animator* pAnim = AddComponent<Animator>();
		pAnim->Create(L"HeadA_stand", nullptr, Vector2(0.f, 0.f), Vector2(550.f, 650.f), 10, Vector2(1000.f, 1000.f), Vector2::Zero, Vector2(11550.f, 3250.f), 0.15f);
		pAnim->Create(L"HeadA_attack0", nullptr, Vector2(0.f, 650.f), Vector2(550.f, 650.f), 21, Vector2(1000.f, 1000.f), Vector2::Zero, Vector2(11550.f, 3250.f), 0.15f);
		pAnim->Create(L"HeadA_attack1", nullptr, Vector2(0.f, 1300.f), Vector2(550.f, 650.f), 17, Vector2(1000.f, 1000.f), Vector2::Zero, Vector2(11550.f, 3250.f), 0.15f);
		pAnim->Create(L"HeadA_attack2", nullptr, Vector2(0.f, 1950.f), Vector2(550.f, 650.f), 16, Vector2(1000.f, 1000.f), Vector2::Zero, Vector2(11550.f, 3250.f), 0.15f);
		pAnim->Create(L"HeadA_dead", nullptr, Vector2(0.f, 2600.f), Vector2(550.f, 650.f), 15, Vector2(1000.f, 1000.f), Vector2::Zero, Vector2(11550.f, 3250.f), 0.15f);


		MonsterAttackObject* breath = new MonsterAttackObject();
		breath->SetName(L"icebreath");
		ObjectPoolManager::AddObjectPool(breath->GetName(), breath);

		for (int i = 0; i < 5; ++i)
		{
			Ice* pIce = new Ice();
			pIce->SetName(L"ice");
			ObjectPoolManager::AddObjectPool(pIce->GetName(), pIce);
		}

		GetComponent<Transform>()->SetScale(11.f, 11.f, 0.f);
	}

	HorntailHeadA::~HorntailHeadA()
	{
		
	}


	void HorntailHeadA::Initialize()
	{
		std::shared_ptr<Texture> pAtlas = Resources::Find<Texture>(L"HeadATex");
		Animator* pAnimator = GetComponent<Animator>();
		pAnimator->SetTexture(pAtlas);
	}

	void HorntailHeadA::Update()
	{
	
	}

	void HorntailHeadA::LateUpdate()
	{
		Monster::LateUpdate();
	}

	void HorntailHeadA::Render()
	{
		renderer::MonsterCB MonsterCB;
		MonsterCB.vMonsterDir.x = 1;

		ConstantBuffer* pConstBuffer = renderer::constantBuffer[(UINT)eCBType::Monster];
		//Vector4 vPosition(m_vPosition.x, m_vPosition.y, m_vPosition.z, 1.f);
		pConstBuffer->SetData(&MonsterCB);
		pConstBuffer->Bind(eShaderStage::PS);

		GameObject::Render();
	}

	void HorntailHeadA::UpdateState(const wstring& _strStateName, int _iState)
	{
		Monster::UpdateState(_strStateName, _iState);
	}

}