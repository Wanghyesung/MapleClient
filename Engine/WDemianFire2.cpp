#include "WDemianFire2.h"
#include "WMonster.h"
#include "WSceneManger.h"
#include "WRigidbody.h"
#include "WAnimator.h"
#include "WBattleManager.h"
#include "WMonsterAttackScript.h"
#include "WRenderer.h"
namespace W
{
	DemianFire2::DemianFire2() :
		m_bMove(false),
		m_bEnd(false),
		m_strCurAnim{},
		m_vVelocity(Vector2::Zero)
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
		Resources::Insert(L"demainfire2", pMater);

		Animator* pAnim = AddComponent<Animator>();
		std::shared_ptr<Texture> pAtlas = Resources::Find<Texture>(L"demainfire2");
		pAnim->Create(L"fire_start", pAtlas, Vector2(0.0f, 0.0f), Vector2(62.f, 64.0f), 9, Vector2(2000.f, 2000.f), Vector2::Zero, 0.12f);
		pAnim->Create(L"fire_end", pAtlas, Vector2(0.0f, 64.f), Vector2(167.f, 291.0f), 10, Vector2(2000.f, 2000.f), Vector2::Zero, 0.1f);

		pAnim->CompleteEvent(L"fire_start") = std::bind(&DemianFire2::start, this);
		pAnim->CompleteEvent(L"fire_end") = std::bind(&DemianFire2::off, this);

		mr->SetMaterial(pMater);
	}

	DemianFire2::~DemianFire2()
	{

	}
	void DemianFire2::Initialize()
	{
		m_tMonsterAttack.tAttackInfo.fAttackDamage = BattleManager::GetMaxDamage();

		m_tMonsterAttack.vPosition = GetComponent<Transform>()->GetPosition();
		m_tMonsterAttack.vScale = Vector2(0.06f, 0.06f);
		m_tMonsterAttack.vOffset = Vector2(0.f, 0.f);

		SetMonsterAttack(m_tMonsterAttack);

		m_vVelocity = GetComponent<Rigidbody>()->GetVelocity();
	}
	void DemianFire2::Update()
	{
		if (m_bMove)
			move();

		if (!m_bEnd)
		{
			m_bEnd = GetScript<MonsterAttackScript>()->IsEnter();

			if (m_bEnd)
			{
				m_bMove = false;
				//Vector3 vPosition = GetComponent<Transform>()->GetPosition();
				//vPosition.y += 0.35f;
				//GetComponent<Transform>()->SetPosition(vPosition);
			}

		}

		GameObject::Update();
	}
	void DemianFire2::LateUpdate()
	{
		Animator* pAnimator = GetComponent<Animator>();

		std::wstring strState = L"_start";

		if (m_bEnd)
			strState = L"_end";

		else if (m_bMove)
			strState = L"_move";


		std::wstring strAnim = L"fire" + strState;

		if (m_strCurAnim != strAnim)
		{
			m_strCurAnim = strAnim;
			pAnimator->Play(strAnim, true);
		}

		GameObject::LateUpdate();
	}
	void DemianFire2::Render()
	{
		renderer::ObjectCB ObjcetCB;
		ObjcetCB.vObjectColor = Vector4::One;
		ObjcetCB.vObjectDir.x = 1;
		ConstantBuffer* pConstBuffer = renderer::constantBuffer[(UINT)eCBType::Object];

		pConstBuffer->SetData(&ObjcetCB);
		pConstBuffer->Bind(eShaderStage::PS);

		GameObject::Render();
	}
	void DemianFire2::off()
	{
		m_bMove = false;
		m_bEnd = false;
		GetScript<MonsterAttackScript>()->SetEnter(false);
		GetScript<MonsterAttackScript>()->InitStack();

		EventManager::AddMonsterPool(this);
	}
	void DemianFire2::start()
	{
		m_bMove = true;
		//SetMonsterAttack(m_tMonsterAttack);
	}

	void DemianFire2::move()
	{
		Rigidbody* pRigidbody = GetComponent<Rigidbody>();
		pRigidbody->AddForce(m_vVelocity);
	}
}