#include "WRex.h"
#include "WResources.h"
#include "WAnimator.h"
#include "WEffect.h"
#include "WRenderer.h"
#include "WEventManager.h"
#include "WSceneManger.h"
#include "WRexThunder.h"
#include "WTransform.h"

namespace W
{
	Rex::Rex()
	{
		SetName(L"Rex");

		MeshRenderer* pRenderer = AddComponent<MeshRenderer>();
		pRenderer->SetMesh(Resources::Find<Mesh>(L"RectMesh"));


		std::shared_ptr<Material> pMater = std::make_shared<Material>();
		pMater->SetRenderinMode(eRenderingMode::Transparent);
		pMater->SetShader(Resources::Find<Shader>(L"MonsterShader"));
		Resources::Insert(L"RexMater", pMater);

		pRenderer->SetMaterial(pMater);

		Animator* pAnim = AddComponent<Animator>();
		pAnim->Create(L"Rex_stand", nullptr, Vector2(0.f, 0.f), Vector2(500.f, 1000.f), 1, Vector2(1000.f, 1000.f), Vector2::Zero, Vector2(10000.f, 6000.f), 0.15f);
		pAnim->Create(L"Rex_start", nullptr, Vector2(0.f, 1000.f), Vector2(500.f, 1000.f), 11, Vector2(1000.f, 1000.f), Vector2::Zero, Vector2(10000.f, 6000.f), 0.15f);
		pAnim->Create(L"Rex_attack0", nullptr, Vector2(0.f, 2000.f), Vector2(500.f, 1000.f), 18, Vector2(1000.f, 1000.f), Vector2::Zero, Vector2(10000.f, 6000.f), 0.15f);
		pAnim->Create(L"Rex_attack1", nullptr, Vector2(0.f, 3000.f), Vector2(500.f, 1000.f), 20, Vector2(1000.f, 1000.f), Vector2::Zero, Vector2(10000.f, 6000.f), 0.15f);
		pAnim->Create(L"Rex_attack2", nullptr, Vector2(0.f, 4000.f), Vector2(500.f, 1000.f), 20, Vector2(1000.f, 1000.f), Vector2::Zero, Vector2(10000.f, 6000.f), 0.15f);
		pAnim->Create(L"Rex_dead", nullptr, Vector2(0.f, 5000.f), Vector2(500.f, 1000.f), 15, Vector2(1000.f, 1000.f), Vector2::Zero, Vector2(10000.f, 6000.f), 0.15f);

		MonsterAttackObject* attack1 = new MonsterAttackObject();
		attack1->SetName(L"Rex_attack0");
		ObjectPoolManager::AddObjectPool(attack1->GetName(), attack1);

		RexThunder* pThunder = new RexThunder();
		pThunder->SetName(L"Rex_attack1");
		ObjectPoolManager::AddObjectPool(pThunder->GetName(), pThunder);

		MonsterAttackObject* attack3 = new MonsterAttackObject();
		attack3->SetName(L"Rex_attack2");
		ObjectPoolManager::AddObjectPool(attack3->GetName(), attack3);


		GetComponent<Transform>()->SetScale(10.f, 10.f, 0.f);
		GetComponent<Transform>()->SetPosition(5.55f, 2.05f, -1.3f);
	}
	Rex::~Rex()
	{
		
	}


	void Rex::Initialize()
	{
		Animator* pAnim = GetComponent<Animator>();

		std::shared_ptr<Texture> pAtlas = Resources::Find<Texture>(L"RexTex");
		pAnim->SetTexture(pAtlas);

		m_strCurStateName.clear();
	}
	void Rex::Update()
	{
		
	}
	void Rex::LateUpdate()
	{
		
		Monster::LateUpdate();
	}
	void Rex::Render()
	{
		renderer::MonsterCB MonsterCB;
		MonsterCB.vMonsterDir.x = 1;

		ConstantBuffer* pConstBuffer = renderer::constantBuffer[(UINT)eCBType::Monster];
		//Vector4 vPosition(m_vPosition.x, m_vPosition.y, m_vPosition.z, 1.f);
		pConstBuffer->SetData(&MonsterCB);
		pConstBuffer->Bind(eShaderStage::PS);

		GameObject::Render();
	}
	
	void Rex::UpdateState(const wstring& _strStateName, int _iState)
	{
		Monster::UpdateState(_strStateName, _iState);
	}
}