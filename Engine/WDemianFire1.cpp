#include "WDemianFire1.h"
#include "WMonster.h"
#include "WSceneManger.h"
#include "WRigidbody.h"
#include "WAnimator.h"
#include "WBattleManager.h"
#include "WMonsterAttackScript.h"
#include "WRenderer.h"
#include "WTime.h"
namespace W
{
	DemianFire1::DemianFire1() :
		m_vVelocity(Vector2::Zero),
		m_fCurTime(0.f),
		m_fDeleteTime(3.f)
	{
		AddComponent<Rigidbody>();
		AddComponent<Collider2D>()->SetActive(false);

		//기본적으로 제공하는 script를 제거하고 전용 script로

		GetComponent<Transform>()->SetScale(18.f, 18.f, 0.f);

		MeshRenderer* mr = AddComponent<MeshRenderer>();
		mr->SetMesh(Resources::Find<Mesh>(L"RectMesh"));

		std::shared_ptr<Material> pMater = std::make_shared<Material>();
		pMater->SetRenderinMode(eRenderingMode::Transparent);
		pMater->SetShader(Resources::Find<Shader>(L"ObjectAnimShader"));
		Resources::Insert(L"demainfire1", pMater);

		Animator* pAnim = AddComponent<Animator>();
		std::shared_ptr<Texture> pAtlas = Resources::Find<Texture>(L"demainfire1");
		pAnim->Create(L"fire1", pAtlas, Vector2(0.0f, 0.0f), Vector2(78.f, 78.0f), 6, Vector2(2000.f, 2000.f), Vector2::Zero, 0.12f);

		pAnim->Play(L"fire1", true);

		mr->SetMaterial(pMater);
	}
	DemianFire1::~DemianFire1()
	{

	}
	void DemianFire1::Initialize()
	{
		m_tMonsterAttack.tAttackInfo.fAttackDamage = BattleManager::GetMaxDamage();

		m_tMonsterAttack.vPosition = GetComponent<Transform>()->GetPosition();
		m_tMonsterAttack.vScale = Vector2(0.03f, 0.03f);
		m_tMonsterAttack.vOffset = Vector2(0.f, 0.f);

		SetMonsterAttack(m_tMonsterAttack);

		m_vVelocity = GetComponent<Rigidbody>()->GetVelocity();
	}
	void DemianFire1::Update()
	{
		Rigidbody* pRigidbody = GetComponent<Rigidbody>();
		pRigidbody->AddForce(m_vVelocity);

		m_fCurTime += Time::DeltaTime();
		if (m_fCurTime >= m_fDeleteTime)
		{
			off();
		}
			
		else
		{
			bool bEnter = GetScript<MonsterAttackScript>()->IsEnter();

			if (bEnter)
				m_fCurTime = m_fDeleteTime;
		}

		GameObject::Update();
	}
	void DemianFire1::LateUpdate()
	{
		GameObject::LateUpdate();
	}
	void DemianFire1::Render()
	{
		renderer::ObjectCB ObjcetCB;
		ObjcetCB.vObjectColor = Vector4::One;
		ObjcetCB.vObjectDir.x = 1;
		ConstantBuffer* pConstBuffer = renderer::constantBuffer[(UINT)eCBType::Object];

		pConstBuffer->SetData(&ObjcetCB);
		pConstBuffer->Bind(eShaderStage::PS);

		GameObject::Render();
	}

	void DemianFire1::off()
	{
		m_fCurTime = 0.f;
		GetScript<MonsterAttackScript>()->SetEnter(false);
		EventManager::AddMonsterPool(this);
	}
}