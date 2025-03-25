#include "WPlayerScript.h"
#include "WRigidbody.h"
#include "WGameObject.h"
#include "WInput.h"
#include "WPlayer.h"
#include "WAnimator.h"
#include "WPlayerFSM.h"
#include "WPlayerState.h"
#include "WShuriken.h"
#include "WSceneManger.h"
#include "WTime.h"
#include "WAttackScript.h"
#include "WMonsterAttackScript.h"
#include "WPlayerAttackObject.h"
#include "WMonsterScript.h"
#include "WPlayerSkill.h"
#include "WSkillState.h"
#include "WBattleManager.h"
#include "WEventManager.h"
#include "WObjectPoolManager.h"

namespace W
{
	PlayerScript::PlayerScript() :
		m_pPlayer(nullptr),
		m_pFSM(nullptr),
		m_pSkill(nullptr),
		m_bLadder(false),
		m_bStab(false),
		m_bAbnormal(false),
		m_bSuperKnockback(false),
		m_bOnGround(false),
		m_iAccAttCnt(20),
		m_fCurAccTime(20.f),
		m_fAccAttackTime(20.f),
		m_fHitTime(2.f),
		m_fknockbackTime(0.f),
		m_tHitInfo{},
		m_tObjectInfo{}
		//m_mapAttackObjs{}
	{
		m_tObjectInfo.fHP = 100.f;
		m_tObjectInfo.fMP = 100.f;
		m_tObjectInfo.fSpeed = 2.5f;
	}
	PlayerScript::~PlayerScript()
	{
		if (m_pFSM)
		{
			delete m_pFSM;
			m_pFSM = nullptr;
		}

		if (m_pSkill)
		{
			delete m_pSkill;
			m_pSkill = nullptr;
		}

		//std::map < std::wstring, std::queue<PlayerAttackObject*>>::iterator iter =
		//	m_mapAttackObjs.begin();
		//
		//for (iter; iter != m_mapAttackObjs.end(); ++iter)
		//{
		//	std::queue< PlayerAttackObject*> queue = iter->second;
		//	while (!queue.empty())
		//	{
		//		PlayerAttackObject* pObj = queue.front();
		//		delete pObj;
		//		pObj = nullptr;
		//		queue.pop();
		//	}
		//
		//}
	}

	void PlayerScript::Initialize()
	{
		tObjectInfo tObjInfo = {};
		tObjInfo.fDefense = 10.f;

		m_pPlayer = dynamic_cast<Player*>(GetOwner());
		
		m_pFSM = new PlayerFSM();
		m_pFSM->SetPlayer(m_pPlayer);
		m_pFSM->Initialize();
		m_pFSM->SetActiveState(Player::ePlayerState::jump);

		m_pSkill = new PlayerSkill();
		m_pSkill->SetPlayer(m_pPlayer);
		m_pSkill->Initialize();

		add_skill();
	}
	void PlayerScript::Update()
	{
		check_time();		

		//상태이상
		if (m_bAbnormal || m_bSuperKnockback)
			return;

		
		bool bSkillOn = m_pSkill->IsSkillOn();
		if(bSkillOn)
			m_pSkill->Update();
		else
			m_pFSM->Update();
	}

	void PlayerScript::LateUpdate()
	{

	}

	void PlayerScript::Render()
	{

	}

	void PlayerScript::OnCollisionEnter(Collider2D* other)
	{

	}

	void PlayerScript::OnCollisionStay(Collider2D* other)
	{
		GameObject* pGameObj = other->GetOwner();
		
		tAttackInfo tAttack;
		bool bDark = m_pPlayer->IsDark();
		if (pGameObj->GetLayerType() == eLayerType::MonsterAttack)
		{
			if (bDark) return;

			bool bNowHit = IsHit();
			if (!bNowHit)
			{
				MonsterAttackScript* pScript = pGameObj->GetScript<MonsterAttackScript>();
				if (pScript == nullptr)
					return;
				tAttack = pScript->GetAttackInfo();
				
				Hit(tAttack, pGameObj->GetName());
			}
		}

		else if (pGameObj->GetLayerType() == eLayerType::Monster)
		{
			if (bDark) return;

			//근접 공격
			m_bStab = true;

			MonsterScript* pScript = pGameObj->GetScript<MonsterScript>();
			if (pScript == nullptr)
				return;

			tAttack = pScript->GetAttackInfo();

			bool bNowHit = IsHit();
			if (!bNowHit)
			{
				tAttack = pGameObj->GetScript<MonsterScript>()->GetAttackInfo();
				Hit(tAttack, pGameObj->GetName());
			}
		}
		else if (pGameObj->GetLayerType() == eLayerType::Box)
		{
			m_bStab = true;
		}
	}

	void PlayerScript::OnCollisionExit(Collider2D* other)
	{
		GameObject* pGameObj = other->GetOwner();
		if (pGameObj->GetLayerType() == eLayerType::Monster || 
			pGameObj->GetLayerType() == eLayerType::Box)
			m_bStab = false;
	}

	void PlayerScript::ActiveJump()
	{
		
		Rigidbody* pRigidbody = m_pPlayer->GetComponent<Rigidbody>();
		pRigidbody->SetGround(false);
		pRigidbody->AddVelocity(Vector2(m_pPlayer->GetDir() * 1.8f, 0.1f));

		m_pFSM->ChangeState(Player::ePlayerState::jump);
	}

	const std::wstring& PlayerScript::GetCurStateName()
	{
		return m_pFSM->GetActiveState()->GetStateName();
	}

	void PlayerScript::MinusAttackCnt()
	{
		--m_iAccAttCnt;
		if (m_iAccAttCnt <= 0)
			m_fCurAccTime = m_fAccAttackTime;
	}

	void PlayerScript::SetActiveState(Player::ePlayerState _eState)
	{
		m_pFSM->SetActiveState(_eState);
	}

	Shuriken* PlayerScript::CreateShuriken()
	{
		//int iDir = m_pPlayer->GetDir();
		Shuriken* pShuriken = new Shuriken();
		//pShuriken->SetDir(iDir);
		pShuriken->SetPlayer(m_pPlayer);
		pShuriken->Initialize();

		tAttackInfo AttackInfo;
		AttackInfo.fAttackDamage = 1.f;
		AttackInfo.fAttack = m_tAttackInfo.fAttack;
		AttackInfo.fDex = m_tAttackInfo.fDex;

		AttackInfo.fAttRcnt = 0.7f;
		AttackInfo.fAttRigidityTime = 0.3f;
		AttackInfo.fAttUpperRcnt = 0.f;

		AttackInfo.iDamageCount = 1;

		pShuriken->GetScript<AttackScript>()->SetAttackInfo(AttackInfo);

		return pShuriken;
	}

	PlayerAttackObject* PlayerScript::CreateAttackObject()
	{
		PlayerAttackObject* pAttackObject = new PlayerAttackObject();
		pAttackObject->Initialize();
		pAttackObject->SetName(L"Normal_Attack");
		pAttackObject->SetPlayer(m_pPlayer);

		int iDir = m_pPlayer->GetDir();
		Transform* pTr = pAttackObject->GetComponent<Transform>();
		Vector3 vPosition = m_pPlayer->GetComponent<Transform>()->GetPosition();
		vPosition.z -= 0.02f;
		vPosition.x += (iDir * 0.6f);

		if (m_pFSM->GetActiveState()->GetType() == Player::ePlayerState::proneattack)
			vPosition.y -= 0.3f;

		pTr->SetPosition(vPosition);

		tAttackInfo AttackInfo;
		AttackInfo.fAttackDamage = 5.f;
		AttackInfo.fAttack = m_tAttackInfo.fAttack;
		AttackInfo.fDex = m_tAttackInfo.fDex;

		AttackInfo.fAttRcnt = 1.f;
		AttackInfo.fAttRigidityTime = 0.3f;
		AttackInfo.fAttUpperRcnt = 0.f;

		AttackInfo.iDamageCount = 1;

		pAttackObject->GetScript<AttackScript>()->SetAttackInfo(AttackInfo);

		return pAttackObject;
	}

	void PlayerScript::AddPlayerSkill(PlayerAttackObject* _pObj)
	{
		ObjectPoolManager::AddObjectPool(_pObj->GetName(), _pObj);
		//std::map<std::wstring, std::queue<PlayerAttackObject*>>::iterator iter =
		//	m_mapAttackObjs.find(_pObj->GetName());
		//
		//if (iter == m_mapAttackObjs.end())
		//{
		//	std::queue<PlayerAttackObject*> queue = {};
		//	queue.push(_pObj);
		//	m_mapAttackObjs.insert(std::make_pair(_pObj->GetName(), queue));
		//}
		//else
		//	iter->second.push(_pObj);
	}

	PlayerAttackObject* PlayerScript::GetPlayerSkill(const std::wstring& _strName)
	{

		//std::map<std::wstring, std::queue<PlayerAttackObject*>>::iterator iter =
		//	m_mapAttackObjs.find(_strName);
		//
		//if (iter == m_mapAttackObjs.end())
		//	assert(nullptr);
		//
		//PlayerAttackObject* pObj = iter->second.front();
		//iter->second.pop();
		//pObj->GetComponent<Collider2D>()->SetActive(true);
		GameObject* pGameObj = ObjectPoolManager::FrontObject(_strName);
		pGameObj->GetComponent<Collider2D>()->SetActive(true);

		return dynamic_cast<PlayerAttackObject*>(pGameObj);
	}

	void PlayerScript::add_skill()
	{
		for (int i = 0; i < 5; ++i)
		{
			Shuriken* pShuriken = CreateShuriken();
			pShuriken->SetName(L"shuriken");
			AddPlayerSkill(pShuriken);
		}
	}

	void PlayerScript::check_time()
	{
		//무적시간
		if (m_fHitTime < 2.f)
			m_fHitTime += Time::DeltaTime();

		//추가 공격
		if (m_fAccAttackTime > m_fCurAccTime)
			m_fCurAccTime += Time::DeltaTime();

		if (m_fknockbackTime > 0.f)
		{
			m_fknockbackTime -= Time::DeltaTime();
			if (m_fknockbackTime <= 0.f)
			{
				m_bSuperKnockback = false;
				m_pPlayer->GetComponent<Rigidbody>()->SetAccumulation(false);
				m_fknockbackTime = 0.f;
			}
		}
	}

	void PlayerScript::super_knockback(float _fTime)
	{
		m_pPlayer->GetComponent<Rigidbody>()->SetAccumulation(true);
		m_bSuperKnockback = true;
		m_fknockbackTime = _fTime;
	}

	void PlayerScript::knockback()
	{
		Rigidbody* pRigidbody = m_pPlayer->GetComponent<Rigidbody>();
		int iDir = m_pPlayer->GetDir() * -1;
		if (m_tHitInfo.eAttType == eAttackType::SuperKnockback)
		{
			super_knockback(m_tHitInfo.fHitRigidityTime);
			pRigidbody->SetVelocity(Vector2(iDir * m_tHitInfo.fHitRcnt * 2.5f, 0.f));
			EventManager::ChangePlayerFSMState(m_pFSM, Player::ePlayerState::alert);
		}
		else
		{
			m_pPlayer->GetComponent<Rigidbody>()->SetAccumulation(false);
			if(m_tHitInfo.fHitUpperRcnt > 0.f)
				pRigidbody->SetGround(false);

			if (m_pPlayer->GetCurPlayerState() == Player::ePlayerState::walk)
			{
				pRigidbody->SetVelocity(Vector2(iDir * m_tHitInfo.fHitRcnt * 2.5f, m_tHitInfo.fHitUpperRcnt));
			}
			else
				pRigidbody->SetVelocity(Vector2(iDir * m_tHitInfo.fHitRcnt, m_tHitInfo.fHitUpperRcnt));
		}
	}

	void PlayerScript::Hit(const tAttackInfo& _tAttackInfo ,std::wstring _strAttackName)
	{
		//m_tObjectInfo.fHP -= _tAttackInfo.fAttackDamage;
		//m_bAttack = false;

		Vector3 vPosition = m_pPlayer->GetComponent<Transform>()->GetPosition();
		BattleManager::CheckDamage(m_tObjectInfo, _tAttackInfo, _strAttackName, vPosition);

		m_pPlayer->SetAlert(true);

		m_tHitInfo.eAttType = _tAttackInfo.eAttType;
		m_tHitInfo.fHitRcnt = _tAttackInfo.fAttRcnt;
		m_tHitInfo.fHitRigidityTime = _tAttackInfo.fAttRigidityTime;
		m_tHitInfo.fHitUpperRcnt = _tAttackInfo.fAttUpperRcnt;
		
		if (m_tHitInfo.fHitRcnt <= 0.f &&
			m_tHitInfo.fHitUpperRcnt <= 0.f)
			return;

		m_fHitTime = 0.f;

		Player::ePlayerState eState = m_pPlayer->GetCurPlayerState();
		if (eState == Player::ePlayerState::ladder)
			return;

		knockback();
	}
	
}