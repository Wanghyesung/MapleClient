#include "WHorntailHeadB.h"
#include "WResources.h"
#include "WAnimator.h"
#include "WRenderer.h"
#include "WFire.h"
#include "WSceneManger.h"
#include "WEffect.h"
#include "WEventManager.h"

namespace W
{
	HorntailHeadB::HorntailHeadB() 
	{
		SetRender(false);

		SetName(L"HeadB");

		MeshRenderer* pRenderer = AddComponent<MeshRenderer>();
		pRenderer->SetMesh(Resources::Find<Mesh>(L"RectMesh"));


		std::shared_ptr<Material> pMater = std::make_shared<Material>();
		pMater->SetRenderinMode(eRenderingMode::Transparent);
		pMater->SetShader(Resources::Find<Shader>(L"MonsterShader"));
		Resources::Insert(L"horntailHeadBMater", pMater);

		pRenderer->SetMaterial(pMater);

	
		Animator* pAnim = AddComponent<Animator>();
		pAnim->Create(L"HeadB_stand", nullptr, Vector2(0.f, 0.f), Vector2(500.f, 800.f), 10, Vector2(1000.f, 1000.f), Vector2::Zero, Vector2(13000.f, 4000.f), 0.15f);
		pAnim->Create(L"HeadB_attack0", nullptr, Vector2(0.f, 800.f), Vector2(500.f, 800.f), 26, Vector2(1000.f, 1000.f), Vector2::Zero, Vector2(13000.f, 4000.f), 0.15f);
		pAnim->Create(L"HeadB_attack1", nullptr, Vector2(0.f, 1600.f), Vector2(500.f, 800.f), 15, Vector2(1000.f, 1000.f), Vector2::Zero, Vector2(13000.f, 4000.f), 0.15f);
		pAnim->Create(L"HeadB_attack2", nullptr, Vector2(0.f, 2400.f), Vector2(500.f, 800.f), 13, Vector2(1000.f, 1000.f), Vector2::Zero, Vector2(13000.f, 4000.f), 0.15f);
		pAnim->Create(L"HeadB_dead", nullptr, Vector2(0.f, 3200.f), Vector2(500.f, 800.f), 14, Vector2(1000.f, 1000.f), Vector2::Zero, Vector2(13000.f, 4000.f), 0.15f);

		MonsterAttackObject* breath = new MonsterAttackObject();
		breath->SetName(L"firebreath");
		ObjectPoolManager::AddObjectPool(breath->GetName(), breath);

		//2
		for (int i = 0; i < 8; ++i)
		{
			Fire* pFire = new Fire();
			pFire->SetName(L"fire");
			ObjectPoolManager::AddObjectPool(pFire->GetName(), pFire);
		}

		GetComponent<Transform>()->SetScale(11.f, 11.f, 0.f);
	}

	HorntailHeadB::~HorntailHeadB()
	{
		
	}


	void HorntailHeadB::Initialize()
	{
		std::shared_ptr<Texture> pAtlas = Resources::Find<Texture>(L"HeadBTex");
		Animator* pAnimator = GetComponent<Animator>();
		pAnimator->SetTexture(pAtlas);
	}

	void HorntailHeadB::Update()
	{
		
	}

	void HorntailHeadB::LateUpdate()
	{

		Monster::LateUpdate();
	}

	void HorntailHeadB::Render()
	{
		renderer::MonsterCB MonsterCB;
		MonsterCB.vMonsterDir.x = 1;

		ConstantBuffer* pConstBuffer = renderer::constantBuffer[(UINT)eCBType::Monster];
		//Vector4 vPosition(m_vPosition.x, m_vPosition.y, m_vPosition.z, 1.f);
		pConstBuffer->SetData(&MonsterCB);
		pConstBuffer->Bind(eShaderStage::PS);

		GameObject::Render();
	}

	void HorntailHeadB::UpdateState(const wstring& _strStateName, int _iState)
	{
		Monster::UpdateState(_strStateName, _iState);
	}
	
}