#include "WHorntailHeadC.h"
#include "WResources.h"
#include "WAnimator.h"
#include "WRenderer.h"

#include "WThunder.h"
#include "WSceneManger.h"
#include "WEffect.h"
#include "WEventManager.h"
namespace W
{
	HorntailHeadC::HorntailHeadC() 
	{
		SetRender(false);

		SetName(L"HeadC");

		MeshRenderer* pRenderer = AddComponent<MeshRenderer>();
		pRenderer->SetMesh(Resources::Find<Mesh>(L"RectMesh"));


		std::shared_ptr<Material> pMater = std::make_shared<Material>();
		pMater->SetRenderinMode(eRenderingMode::Transparent);
		pMater->SetShader(Resources::Find<Shader>(L"MonsterShader"));
		Resources::Insert(L"horntailHeadCMater", pMater);

		pRenderer->SetMaterial(pMater);

		Animator* pAnim = AddComponent<Animator>();
		pAnim->Create(L"HeadC_stand", nullptr, Vector2(0.f, 0.f), Vector2(600.f, 700.f), 10, Vector2(1000.f, 1000.f), Vector2::Zero, Vector2(13800.f, 3500.f), 0.15f);
		pAnim->Create(L"HeadC_attack0", nullptr, Vector2(0.f, 700.f), Vector2(600.f, 700.f), 23, Vector2(1000.f, 1000.f), Vector2::Zero, Vector2(13800.f, 3500.f), 0.15f);
		pAnim->Create(L"HeadC_attack1", nullptr, Vector2(0.f, 1400.f), Vector2(600.f, 700.f), 18, Vector2(1000.f, 1000.f), Vector2::Zero, Vector2(13800.f, 3500.f), 0.15f);
		pAnim->Create(L"HeadC_attack2", nullptr, Vector2(0.f, 2100.f), Vector2(600.f, 700.f), 14, Vector2(1000.f, 1000.f), Vector2::Zero, Vector2(13800.f, 3500.f), 0.15f);
		pAnim->Create(L"HeadC_dead", nullptr, Vector2(0.f, 2800.f), Vector2(600.f, 700.f), 13, Vector2(1000.f, 1000.f), Vector2::Zero, Vector2(13800.f, 3500.f), 0.15f);
		
		MonsterAttackObject* breath = new MonsterAttackObject();
		breath->SetName(L"thunderbreath");
		ObjectPoolManager::AddObjectPool(breath->GetName(), breath);
		for (int i = 0; i < 8; ++i)
		{
			Thunder* pThunder = new Thunder();
			pThunder->SetName(L"thunder");
			ObjectPoolManager::AddObjectPool(pThunder->GetName(), pThunder);
		}

		GetComponent<Transform>()->SetScale(11.f, 11.f, 0.f);
	}

	HorntailHeadC::~HorntailHeadC()
	{
		
	}

	
	void HorntailHeadC::Initialize()
	{
		std::shared_ptr<Texture> pAtlas = Resources::Find<Texture>(L"HeadCTex");
		Animator* pAnimator = GetComponent<Animator>();
		pAnimator->SetTexture(pAtlas);

		m_strCurStateName.clear();
	}

	void HorntailHeadC::Update()
	{
		
	}

	void HorntailHeadC::LateUpdate()
	{
		
		Monster::LateUpdate();
	}

	void HorntailHeadC::Render()
	{
		renderer::MonsterCB MonsterCB;
		MonsterCB.vMonsterDir.x = 1;

		ConstantBuffer* pConstBuffer = renderer::constantBuffer[(UINT)eCBType::Monster];
		//Vector4 vPosition(m_vPosition.x, m_vPosition.y, m_vPosition.z, 1.f);
		pConstBuffer->SetData(&MonsterCB);
		pConstBuffer->Bind(eShaderStage::PS);

		GameObject::Render();
	}
	void HorntailHeadC::UpdateState(const wstring& _strStateName, int _iState)
	{
		Monster::UpdateState(_strStateName, _iState);
	}

}