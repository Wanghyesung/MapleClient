#include "WDemianKeyAttack.h"
#include "WMonsterAttackScript.h"
#include "WResources.h"
#include "WAnimator.h"
#include "WRigidbody.h"
#include "WCollider2D.h"
#include "WRenderer.h"
#include "WBattleManager.h"
#include "WMonster.h"
#include "WSceneManger.h"
#include "WTime.h"
namespace W
{
	DemianKeyAttack::DemianKeyAttack():
		m_fTime(5.f),
		m_fCurTime(0.f),
		m_bWait(false),
		m_bAttack(false),
		m_iCallCount(0)
	{
		//기본적으로 제공하는 script를 제거하고 전용 script로

		GetComponent<Transform>()->SetScale(20.f, 20.f, 0.f);

		MeshRenderer* mr = AddComponent<MeshRenderer>();
		mr->SetMesh(Resources::Find<Mesh>(L"RectMesh"));

		std::shared_ptr<Material> pMater = std::make_shared<Material>();
		pMater->SetRenderinMode(eRenderingMode::Transparent);
		pMater->SetShader(Resources::Find<Shader>(L"ObjectAnimShader"));
		Resources::Insert(L"keyAttackMater", pMater);

		Animator* pAnim = AddComponent<Animator>();
		std::shared_ptr<Texture> pAtlas = Resources::Find<Texture>(L"demainkeyAttack");
		pAnim->Create(L"create", pAtlas, Vector2(0.0f, 0.f), Vector2(321.0f, 522.0f), 4, Vector2(2000.f, 2000.f), Vector2::Zero, 0.11f);
		pAnim->Create(L"wait", pAtlas, Vector2(0.0f, 522.0f), Vector2(321.0f, 522.0f), 11, Vector2(2000.f, 2000.f), Vector2::Zero, 0.11f);
		pAnim->Create(L"attack", pAtlas, Vector2(0.0f, 1044.0f), Vector2(321.0f, 522.0f), 18, Vector2(2000.f, 2000.f), Vector2::Zero, 0.1f);

		pAnim->CompleteEvent(L"create") = std::bind(&DemianKeyAttack::wait, this);
		pAnim->CompleteEvent(L"attack") = std::bind(&DemianKeyAttack::off, this);

		mr->SetMaterial(pMater);

		GetComponent<MonsterAttackScript>()->SeteAbnormalType(BattleManager::eAbnormalType::InputKey);
	}
	DemianKeyAttack::~DemianKeyAttack()
	{

	}
	void DemianKeyAttack::Initialize()
	{
		m_tMonsterAttack.tAttackInfo.fAttackDamage = 12;

		m_tMonsterAttack.vPosition = GetComponent<Transform>()->GetPosition();
		m_tMonsterAttack.vScale = Vector2(0.08f, 0.2f);
		m_tMonsterAttack.vOffset = Vector2(0.f, 0.5f);

		m_tMonsterAttack.iStartFrame = 9;
		m_tMonsterAttack.iEndFrame = 11;
	}
	void DemianKeyAttack::Update()
	{
		if (m_bAttack)
		{
			int iIndex = GetComponent<Animator>()->FindAnimation(L"attack")->GetCurIndex();
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
		}

		else if (m_bWait)
		{
			m_fCurTime += Time::DeltaTime();
			if (m_fCurTime >= m_fTime)
				m_bAttack = true;
		}
			
		GameObject::Update();
	}
	void DemianKeyAttack::LateUpdate()
	{
		Animator* pAnimator = GetComponent<Animator>();

		std::wstring strState = L"create";

		if(m_bAttack)
			strState = L"attack";

		else if (m_bWait)
			strState = L"wait";


		if (m_strCurAnim != strState)
		{
			m_strCurAnim = strState;
			pAnimator->Play(strState, true);
		}

		GameObject::LateUpdate();
	}
	void DemianKeyAttack::Render()
	{
		renderer::ObjectCB ObjcetCB;
		ObjcetCB.vObjectColor = Vector4::One;
		ObjcetCB.vObjectDir.x = 1;
		ConstantBuffer* pConstBuffer = renderer::constantBuffer[(UINT)eCBType::Object];

		pConstBuffer->SetData(&ObjcetCB);
		pConstBuffer->Bind(eShaderStage::PS);

		GameObject::Render();
	}

	
	void DemianKeyAttack::off()
	{
		m_iCallCount = 0;
		m_bWait = false;
		m_bAttack = false;
		m_fCurTime = 0.f;

		GetScript<MonsterAttackScript>()->InitStack();
		EventManager::AddMonsterPool(this);
	}
}