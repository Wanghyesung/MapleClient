#include "WHorntailTail.h"
#include "WResources.h"
#include "WAnimator.h"
#include "WRenderer.h"
#include "WEffect.h"
#include "WSceneManger.h"
#include "WHorntail.h"

namespace W
{
	HorntailTail::HorntailTail()
	{
		SetName(L"Tail");

		MeshRenderer* pRenderer = AddComponent<MeshRenderer>();
		pRenderer->SetMesh(Resources::Find<Mesh>(L"RectMesh"));


		std::shared_ptr<Material> pMater = std::make_shared<Material>();
		pMater->SetRenderinMode(eRenderingMode::Transparent);
		pMater->SetShader(Resources::Find<Shader>(L"MonsterShader"));
		Resources::Insert(L"horntailTailMater", pMater);

		pRenderer->SetMaterial(pMater);

		Animator* pAnim = AddComponent<Animator>();
		pAnim->Create(L"Tail_stand", nullptr, Vector2(0.f, 0.f), Vector2(550, 450.f), 1, Vector2(1000.f, 1000.f), Vector2::Zero, Vector2(11000.f, 1350.f), 0.15f);
		pAnim->Create(L"Tail_attack0", nullptr, Vector2(0.f, 450.f), Vector2(550, 450.f), 21, Vector2(1000.f, 1000.f), Vector2::Zero, Vector2(11000.f, 1350.f), 0.15f);
		pAnim->Create(L"Tail_dead", nullptr, Vector2(0.f, 900.f), Vector2(550, 450.f), 10, Vector2(1000.f, 1000.f), Vector2::Zero, Vector2(11000.f, 1350.f), 0.15f);
	
		MonsterAttackObject* attack1 = new MonsterAttackObject();
		attack1->SetName(L"tailattack");
		ObjectPoolManager::AddObjectPool(attack1->GetName(), attack1);
	}
	HorntailTail::~HorntailTail()
	{
		
	}
	void HorntailTail::Initialize()
	{
		std::shared_ptr<Texture> pAtlas = Resources::Find<Texture>(L"TailTex");
		Animator* pAnimator = GetComponent<Animator>();
		pAnimator->SetTexture(pAtlas);
	}

	

	void HorntailTail::Update()
	{
		
	}
	void HorntailTail::LateUpdate()
	{
		

		Monster::LateUpdate();
	}
	void HorntailTail::Render()
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