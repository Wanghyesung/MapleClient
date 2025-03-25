#include "WDemianSword.h"
#include "WRigidbody.h"
#include "WResources.h"
#include "WAnimator.h"
#include "WSceneManger.h"
#include "WMonster.h"
#include "WBattleManager.h"
#include "WTime.h"
#include "WEffect.h"
#include "WRenderer.h"
#include "WEventManager.h"
#include "WMonsterScript.h"

namespace W
{
	DemianSword::DemianSword() :
		m_bEnd(false),
		m_bMove(false),
		m_bTargetOn(false),
		m_bAttackOn(false),
		m_bWait(false),
		//m_vArrivePos(Vector3::Zero),
		m_fAttackTime(7.f),
		m_fCurAttackTime(0.f),
		m_fChangeTime(0.7f),
		m_fCurChangeTime(0.f),
		m_fWaitTime(1.f),
		m_fCurWaitTime(0.f),
		m_iDirIndex(0)
	{
		AddComponent<Rigidbody>();

		//기본적으로 제공하는 script를 제거하고 전용 script로

		GetComponent<Transform>()->SetScale(20.f, 20.f, 0.f);

		MeshRenderer* mr = AddComponent<MeshRenderer>();
		mr->SetMesh(Resources::Find<Mesh>(L"RectMesh"));

		std::shared_ptr<Material> pMater = std::make_shared<Material>();
		pMater->SetRenderinMode(eRenderingMode::Transparent);
		pMater->SetShader(Resources::Find<Shader>(L"ObjectAnimShader"));
		Resources::Insert(L"DemianSwordMater", pMater);
		mr->SetMaterial(pMater);

		Animator* pAnim = AddComponent<Animator>();
		std::shared_ptr<Texture> pAtlas = Resources::Find<Texture>(L"DemianSword");
		pAnim->Create(L"sword_start", pAtlas, Vector2(0.0f, 0.0f), Vector2(419.0f, 342.0f), 13, Vector2(2000.f, 2000.f), Vector2::Zero, 0.12f);
		pAnim->Create(L"sword_move", pAtlas, Vector2(0.0f, 342.0f), Vector2(419.0f, 342.0f), 8, Vector2(2000.f, 2000.f), Vector2::Zero, 0.12f);
		pAnim->Create(L"sword_end", pAtlas, Vector2(0.0f, 684.f), Vector2(419.0f, 342.0f), 11, Vector2(2000.f, 2000.f), Vector2::Zero, 0.12f);

		pAnim->CompleteEvent(L"sword_start") = std::bind(&DemianSword::start, this);
		pAnim->CompleteEvent(L"sword_end") = std::bind(&DemianSword::off, this);

		pAnim->Play(L"sword_start", true);

		m_vecDir.push_back(Vector2(0.8f, 0.2f));
		m_vecDir.push_back(Vector2(0.8f, -0.2f));
		m_vecDir.push_back(Vector2(1.f, 0.f));
	}

	DemianSword::~DemianSword()
	{

	}

	void DemianSword::Initialize()
	{
		m_tMonsterAttack.tAttackInfo.fAttackDamage = 25.f;

		m_tMonsterAttack.vPosition = Vector3(0.f, -1.85f, -2.f);
		m_tMonsterAttack.vScale = Vector2(0.03f, 0.05f);
		m_tMonsterAttack.vOffset = Vector2(0.f, 0.f);
	}
	void DemianSword::Update()
	{
		if (m_bAttackOn)
			return;

		check_HP();

		if (m_bWait)
		{
			m_fCurWaitTime += Time::DeltaTime();
			if (m_fCurWaitTime >= m_fWaitTime)
			{
				m_fCurWaitTime = 0.f;
				m_bWait = false;
			}
		}

		else if (m_bTargetOn)
		{
			if (check_position())
			{
				if (m_iMoveCount >= 3.f)
				{
					m_bAttackOn = true;
					GetComponent<Collider2D>()->SetActive(false);
					attack();
					return;
				}

				set_target();
				m_bWait = true;
			}

		}

		else
		{
			m_fCurAttackTime += Time::DeltaTime();

			if (m_fCurAttackTime >= m_fAttackTime)
			{
				m_fCurAttackTime = 0.f;

				m_bTargetOn = true;
				m_bWait = true;
				set_target();
			}
		}

		if (m_bMove)
			move();

		GameObject::Update();
	}
	void DemianSword::LateUpdate()
	{
		if (m_bAttackOn)
			return;

		Animator* pAnimator = GetComponent<Animator>();

		std::wstring strState = L"_start";

		if (m_bEnd)
			strState = L"_end";


		else if (m_bMove)
			strState = L"_move";


		std::wstring strAnim = L"sword" + strState;

		if (m_strCurAnim != strAnim)
		{
			m_strCurAnim = strAnim;
			pAnimator->Play(strAnim, true);
		}

		GameObject::LateUpdate();

	}
	void DemianSword::Render()
	{
		if (m_bAttackOn)
			return;

		renderer::ObjectCB ObjcetCB;
		ObjcetCB.vObjectColor = Vector4::One;
		ObjcetCB.vObjectDir.x = 1;
		ConstantBuffer* pConstBuffer = renderer::constantBuffer[(UINT)eCBType::Object];

		pConstBuffer->SetData(&ObjcetCB);
		pConstBuffer->Bind(eShaderStage::PS);

		GameObject::Render();
	}
	void DemianSword::off()
	{
		m_bMove = false;
		m_bTargetOn = false;
		m_bAttackOn = false;
		m_bEnd = false;
		m_bWait = false;
		m_fCurAttackTime = 0.f;
		m_fCurChangeTime = 0.f;
		m_fCurWaitTime = 0.f;

		EventManager::AddMonsterPool(this);
	}

	void DemianSword::move()
	{
		if (m_bAttackOn || m_bWait)
			return;

		Transform* pTr = GetComponent<Transform>();

		if (m_bTargetOn)
		{
			GetComponent<Rigidbody>()->AddForce(m_vActiveDir * 7.f);
			return;
		}

		//맵을 넘으면 방향 반대로 전환
		int iLen = pTr->GetPosition().x;
		int iMaxLen = SceneManger::GetActiveScene()->GetMapPossibleSize().RX;
		if (fabs(iMaxLen) - fabs(iLen) <= 0.0f)
		{
			change_dir();
		}


		m_fCurChangeTime += Time::DeltaTime();
		if (m_fCurChangeTime >= m_fChangeTime)
		{
			m_fCurChangeTime = 0.f;
			//정해진 방향 정하기
			set_dir();
		}

		//내가 가고있는방향 으로 회전
		set_rotate();

		GetComponent<Rigidbody>()->AddForce(m_vActiveDir * 5.f);
	}

	void DemianSword::set_target()
	{
		GameObject* pObj = SceneManger::FindPlayer();
		Vector3 vTargetPosition = pObj->GetComponent<Collider2D>()->GetPosition();
		m_vTargetPos = Vector2(vTargetPosition.x, vTargetPosition.y);
		
		Vector3 vPosition = GetComponent<Collider2D>()->GetPosition();
		Vector2 vPos = Vector2(vPosition.x, vPosition.y);

		Effect* pEffect = BattleManager::GetEffect(L"DemianTarget");
		pEffect->StartEffect(1);
		pEffect->SetActive(true);
		pEffect->GetComponent<Transform>()->SetPosition(vTargetPosition);
		EventManager::CreateObject(pEffect, eLayerType::Effect);


		if (m_vTargetPos.y > 0)
			m_vTargetPos.y -= 0.4f;
		else
			m_vTargetPos.y += 0.4f;

		Vector2 vDiff = m_vTargetPos - vPos;
		vDiff.Normalize();

		m_vActiveDir = vDiff;
		set_rotate();
	}
	bool DemianSword::check_position()
	{
		Vector3 vPos = GetComponent<Collider2D>()->GetPosition();
		Vector2 vPosition = Vector2(vPos.x, vPos.y);

		Vector2 vDiff = m_vTargetPos - vPosition;
		float fLen = vDiff.Length();
		if (fabs(vDiff.x) < 0.25f)
		{
			++m_iMoveCount;
			return true;
		}
		return false;
	}

	void DemianSword::set_dir()
	{
		m_vActiveDir = m_vecDir[m_iDirIndex];

		++m_iDirIndex;
		if (m_iDirIndex > m_vecDir.size() - 1)
			m_iDirIndex = 0;
	}

	void DemianSword::change_dir()
	{
		for (int i = 0; i < m_vecDir.size(); ++i)
			m_vecDir[i].x *= -1;

		m_vActiveDir.x *= -1;
	}

	void DemianSword::set_rotate()
	{
		float fRadian = 0.f;
		
		fRadian = m_vActiveDir.x >0 ? -XM_PI / 2.f : XM_PI / 2.f;
		float fNewRadian = 0.f;
		if (fRadian > 0)
		{
			fNewRadian = atan2f(-m_vActiveDir.y, -m_vActiveDir.x);
		}
		else
		{
			fNewRadian = atan2f(m_vActiveDir.y, m_vActiveDir.x);
		}
		
		GetComponent<Transform>()->SetRotation(0.f, 0.f, fRadian + fNewRadian);
	}

	void DemianSword::start()
	{
		m_bMove = true;
		m_bTargetOn = false;
		m_bAttackOn = false;
		m_bWait = false;
		SetMonsterAttack(m_tMonsterAttack);

		set_dir();
	}

	void DemianSword::restart()
	{
		GetComponent<Collider2D>()->SetActive(true);
		float x = GetComponent<Transform>()->GetPosition().x;
		GetComponent<Transform>()->SetPosition(Vector3(x, -1.85f, -2.f));

		m_bTargetOn = false;
		m_bAttackOn = false;
		m_bWait = false;
		m_bEnd = false;

		m_iDirIndex = 2;
		m_vActiveDir = m_vecDir[m_iDirIndex];

		m_iMoveCount = 0;
		m_fCurAttackTime = 0.f;
		m_fCurChangeTime = 0.f;
		m_fCurWaitTime = 0.f;
	}

	void DemianSword::check_HP()
	{
		float fHP = GetOwner()->GetScript<MonsterScript>()->GetObjectInfo().fHP;
		if (fHP <= 0.f)
		{
			m_bMove = false;
			m_bEnd = true;
		}
	}

	void DemianSword::attack()
	{
		MonsterAttackObject* pObject = GetOwner()->GetMonsterSkill(L"SwordExplode");
		EventManager::CreateObject(pObject, eLayerType::MonsterAttack);

		Vector3 vPosition = GetComponent<Transform>()->GetPosition();
		vPosition.y = -1.4f;//땅 위치
		pObject->GetComponent<Transform>()->SetPosition(vPosition);

		pObject->Initialize();
	}

}