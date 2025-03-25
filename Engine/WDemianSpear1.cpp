#include "WDemianSpear1.h"
#include "WResources.h"
#include "WAnimator.h"
#include "WRenderer.h"
#include "WObject.h"
#include "WMonsterAttackScript.h"
#include "WMonster.h"
#include "WBattleManager.h"
namespace W
{
	DemianSpear1::DemianSpear1() :
		m_iCallCount(0),
		m_tMonsterAttack{}
	{
		std::shared_ptr<Material> pMater = std::make_shared<Material>();
		pMater->SetRenderinMode(eRenderingMode::Transparent);
		pMater->SetShader(Resources::Find<Shader>(L"ObjectAnimShader"));
		Resources::Insert(L"DemianSpaerMater", pMater);

		MeshRenderer* pRenderer = AddComponent<MeshRenderer>();
		pRenderer->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
		pRenderer->SetMaterial(pMater);

		Collider2D* pCollider = GetComponent<Collider2D>();
		pCollider->SetActive(false);

		GetComponent<Transform>()->SetScale(18.f, 18.f, 0.f);

		std::shared_ptr<Texture> pAtlas = Resources::Find<Texture>(L"demianspear1");
		Animator* pAnim = AddComponent<Animator>();
		pAnim->Create(L"Spear", pAtlas, Vector2(0.0f, 0.0f), Vector2(258.f, 538.0f), 29, Vector2(2000.f, 2000.f), Vector2::Zero, 0.15f);

		pAnim->CompleteEvent(L"Spear") = std::bind(&DemianSpear1::off, this);
		pAnim->Play(L"Spear", true);

	}

	DemianSpear1::~DemianSpear1()
	{

	}

	void DemianSpear1::Initialize()
	{
		m_tMonsterAttack.tAttackInfo.fAttackDamage = BattleManager::GetMaxDamage();

		m_tMonsterAttack.vPosition = GetComponent<Transform>()->GetPosition();
		
		m_tMonsterAttack.vScale = Vector2(0.05f, 0.2f);
		m_tMonsterAttack.vOffset = Vector2(0.f, 0.f);
		int iDir = GetOwner()->GetDir();
		Vector3 vRotate = Vector3(0.f, 0.f, -iDir * XM_PI / 7.f);
		m_tMonsterAttack.vRoatate = vRotate;
		GetComponent<Transform>()->SetRotation(vRotate);

		m_tMonsterAttack.iStartFrame = 19;
		m_tMonsterAttack.iEndFrame = 23;
	}

	void DemianSpear1::Update()
	{
		GameObject::Update();
	}

	void DemianSpear1::LateUpdate()
	{
		Animation* pAnim = GetComponent<Animator>()->GetActiveAnimation();

		int iIndex = pAnim->GetCurIndex();
		if (iIndex >= m_tMonsterAttack.iStartFrame && m_iCallCount == 0)
		{
			m_iCallCount = 1;
			//지금 실행중인 데미지 정보 넘기기
			SetMonsterAttack(m_tMonsterAttack);
			GetComponent<Collider2D>()->SetActive(true);
		}

		if (m_iCallCount == 1 && iIndex >= m_tMonsterAttack.iEndFrame)
		{
			m_iCallCount = 2;
			GetComponent<Collider2D>()->SetActive(false);
		}

		GameObject::LateUpdate();
	}
	void DemianSpear1::Render()
	{
		renderer::ObjectCB ObjectCB;
		ObjectCB.vObjectDir.x = 1;
		ObjectCB.vObjectColor = Vector4::One;

		ConstantBuffer* pConstBuffer = renderer::constantBuffer[(UINT)eCBType::Object];
		//Vector4 vPosition(m_vPosition.x, m_vPosition.y, m_vPosition.z, 1.f);
		pConstBuffer->SetData(&ObjectCB);
		pConstBuffer->Bind(eShaderStage::PS);

		GameObject::Render();
	}
	void DemianSpear1::off()
	{
		m_iCallCount = 0;
		GetScript<MonsterAttackScript>()->InitStack();
		EventManager::AddMonsterPool(this);
	}
}