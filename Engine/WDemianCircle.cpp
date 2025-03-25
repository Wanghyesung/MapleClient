#include "WDemianCircle.h"
#include "WRenderer.h"
#include "WResources.h"
#include "WAnimator.h"
#include "WMonster.h"
#include "WSceneManger.h"
#include "WRigidbody.h"
#include "WPlayerScript.h"
#include "WBattleManager.h"
#include "WTime.h"
namespace W
{
	DemianCircle::DemianCircle():
		m_bEnter(false),
		m_bActive(false),
		m_pTarget(nullptr),
		m_iCurIndex(0),
		m_fCurAttackTime(0.f),
		m_fAttackTime(1.4f)
	{
		AddComponent<Rigidbody>();

		std::shared_ptr<Material> pMater = std::make_shared<Material>();
		pMater->SetRenderinMode(eRenderingMode::Transparent);
		pMater->SetShader(Resources::Find<Shader>(L"ObjectAnimShader"));
		Resources::Insert(L"DemianCircleMater", pMater);

		MeshRenderer* pRenderer = AddComponent<MeshRenderer>();
		pRenderer->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
		pRenderer->SetMaterial(pMater);

		GetComponent<Transform>()->SetScale(4.f, 4.f, 0.f);

		std::shared_ptr<Texture> pAtlas = Resources::Find<Texture>(L"DemianCircle");
		Animator* pAnim = AddComponent<Animator>();
		pAnim->Create(L"level0", pAtlas, Vector2(0.0f, 0.0f), Vector2(260.f, 272.0f), 12, Vector2(500.f, 500.f), Vector2::Zero, 0.15f);
		pAnim->Create(L"level1", pAtlas, Vector2(0.0f, 272.0f), Vector2(361.f, 374.0f), 11, Vector2(500.f, 500.f), Vector2::Zero, 0.15f);
		pAnim->Create(L"level2", pAtlas, Vector2(0.0f, 646.f), Vector2(431.f, 449.0f), 12, Vector2(500.f, 500.f), Vector2::Zero, 0.15f);

		pAnim->Play(L"level0", true);
	}

	DemianCircle::~DemianCircle()
	{

	}
	void DemianCircle::Initialize()
	{
		m_vecColliderSize.push_back(Vector2(0.85f, 0.85f));
		m_vecColliderSize.push_back(Vector2(1.1f, 1.1f));
		m_vecColliderSize.push_back(Vector2(1.35f, 1.35f));

		Vector3 vPosition = Vector3(0.1f, -1.85f, -1.5f);
		GetComponent<Transform>()->SetPosition(vPosition);

		m_tMonsterAttack.tAttackInfo.fAttackDamage = 3;
		m_tMonsterAttack.tAttackInfo.fAttRcnt = 0.f;//¸ÂÀ¸
		m_tMonsterAttack.tAttackInfo.fAttUpperRcnt = 0.f;
	}
	void DemianCircle::Update()
	{
		move();

		check_enter();

		GameObject::Update();
	}
	void DemianCircle::LateUpdate()
	{
		GameObject::LateUpdate();
	}
	void DemianCircle::Render()
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
	void DemianCircle::LevelUp(UINT _iLevel)
	{
		m_iCurIndex = _iLevel;
		std::wstring strNum = std::to_wstring(m_iCurIndex);
		GetComponent<Animator>()->Play(L"level"+ strNum, true);
	}
	
	void DemianCircle::check_enter()
	{
		m_fCurAttackTime += Time::DeltaTime();

		Vector3 vPos = m_pTarget->GetComponent<Transform>()->GetPosition();
		Vector2 vTargerPos = Vector2(vPos.x, vPos.y);
		Vector3 vPosition = GetComponent<Transform>()->GetPosition();
		Vector2 vCirclePos = Vector2(vPosition.x, vPosition.y);

		float fLen = (vTargerPos - vCirclePos).Length();

		bool bEnter = false;
		if (fabs(fLen) <= (m_vecColliderSize[m_iCurIndex]).Length())
		{
			bEnter = true;
			if (m_fCurAttackTime >= m_fAttackTime)
			{
				m_pTarget->GetScript<PlayerScript>()->Hit(m_tMonsterAttack.tAttackInfo, L"Circle");
				m_fCurAttackTime = 0.f;
			}
		}
			
		if (m_bEnter == bEnter)
			return;

		m_bEnter = bEnter;

		Collider2D* pCollider = GetComponent<Collider2D>();
		if (m_bEnter)
		{
			BattleManager::Player_DeBuff_Attack(m_pTarget, BattleManager::eUpStatType::Defense, 9);
		}
			
		else
		{
			BattleManager::Player_DeBuff_Attack(m_pTarget, BattleManager::eUpStatType::Defense, -9);
		}
	}
	void DemianCircle::move()
	{
		m_pTarget = SceneManger::FindPlayer();
 
	 	Vector3 vTargetPos = m_pTarget->GetComponent<Transform>()->GetPosition();
		Vector3 vPosition = GetComponent<Transform>()->GetPosition();

		Vector3 vLen = vTargetPos - vPosition;
		int iDir = vLen.x > 0.f ? 1 : -1;

		GetComponent<Rigidbody>()->AddForce(Vector2(iDir * m_fSpeed, 0.f));
	}
}