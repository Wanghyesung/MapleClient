#include "WMonsterScript.h"
#include "WMonsterFSM.h"
#include "WRigidbody.h"
#include "WAttackScript.h"
#include "WTime.h"
#include "WSceneManger.h"
#include "WMonsterAttackObject.h"
#include "WObject.h"
#include "WBattleManager.h"
#include "WEventManager.h"
#include "WMonsterHP.h"
#include "WPlayerAttackObject.h"
#include "WPlayerScript.h"
#include "WMonsterAttackScript.h"
namespace W
{
	MonsterScript::MonsterScript() :
		m_pFSM(nullptr),
		m_pAttackObject(nullptr),
		m_pHitEffect(nullptr),
		m_pHP(nullptr),
		m_tHitInfo{},
		m_tMonsterInfo{},
		m_tObjectInfo{},
		m_vecAttacks{},
		m_iCurAttackCount(0),
		m_bBoss(false),
		m_bReflex(false)
	{
		m_tMonsterInfo.tAttackInfo.fAttackDamage = 5.f;
		m_tObjectInfo.fSpeed = 1.f;
	}

	MonsterScript::~MonsterScript()
	{
		if (m_pFSM)
		{
			delete m_pFSM;
			m_pFSM = nullptr;
		}
	}

	void MonsterScript::Initialize()
	{
		m_pMonster = dynamic_cast<Monster*>(GetOwner());
	}

	void MonsterScript::Update()
	{
		if (!m_pFSM)
			return;

		m_pFSM->Update();

		if (m_pFSM->GetActiveState()->GetType() == Monster::eMonsterState::stand ||
			m_pFSM->GetActiveState()->GetType() == Monster::eMonsterState::move)
		{
			update_cooltime();
		}
	}
	void MonsterScript::LateUpdate()
	{
	}
	void MonsterScript::Render()
	{
	}
	void MonsterScript::OnCollisionEnter(Collider2D* other)
	{
		GameObject* pOther = other->GetOwner();
		if (pOther->GetLayerType() == eLayerType::AttackObject)
		{
			float fDir = other->GetPosition().x - GetOwner()->GetComponent<Collider2D>()->GetPosition().x;
			int iDir = fDir > 0 ? 1 : -1;
			m_tHitInfo.fHitDir = -iDir;

			AttackScript* pAttackScript = pOther->GetScript<AttackScript>();
			UINT ID = m_pMonster->GetComponent<Collider2D>()->GetColliderID();

			if (pAttackScript->IsAttackOn(ID))
			{
				tAttackInfo attackInfo = pAttackScript->GetAttackInfo();
				hit(attackInfo, pOther);
			}
		}
	}

	void MonsterScript::OnCollisionStay(Collider2D* other)
	{
		GameObject* pOther = other->GetOwner();
		if (pOther->GetLayerType() == eLayerType::AttackObject)
		{
			AttackScript* pAttackScript = pOther->GetScript<AttackScript>();
			UINT ID = m_pMonster->GetComponent<Collider2D>()->GetColliderID();

			if (pAttackScript->IsAttackOn(ID))
			{
				tAttackInfo attackInfo = pAttackScript->GetAttackInfo();
				hit(attackInfo, pOther);
			}
		}
	}
	void MonsterScript::OnCollisionExit(Collider2D* other)
	{

	}

	//void MonsterScript::AddAttackDamage(float _fDamage)
	//{
	//	for (UINT i = 0; i < m_vecAttacks.size(); ++i)
	//	{
	//		m_vecAttacks[i].tAttackInfo.fAttackDamage += _fDamage;
	//	}
	//}
	//
	//void MonsterScript::DecAttackDamage(float _fDamage)
	//{
	//	for (UINT i = 0; i < m_vecAttacks.size(); ++i)
	//	{
	//		m_vecAttacks[i].tAttackInfo.fAttackDamage += _fDamage;
	//	}
	//}

	void MonsterScript::SetActiveAttack()
	{
		//현재 실행중인 공격 정보 가져오기
		tMonsterAttack& tAttack = m_vecAttacks[m_iCurAttackCount];
		
		//공격(현재 공격 설정)
		if (tAttack.pFunction != nullptr)
			tAttack.pFunction();

		//(소환, 마법) 공격이 아니면 공격 정보 전달
		if (!tAttack.bSkill)
			m_pAttackObject->SetMonsterAttack(tAttack);
	}

	void MonsterScript::DeleteActiveAttack()
	{
		if (!m_pAttackObject)
			return;

		tMonsterAttack& tAttack = m_vecAttacks[m_iCurAttackCount];
		if (!tAttack.bSkill)
		{
			//m_pMonster->AddMonsterSkill(m_pAttackObject);
			//SceneManger::Erase(m_pAttackObject);

			m_pAttackObject->GetScript<MonsterAttackScript>()->InitStack();
			EventManager::AddMonsterPool(m_pAttackObject);

			m_pAttackObject = nullptr;
		}
	}

	void MonsterScript::AciveAttack(UINT _iINdex)
	{
		m_vecAttacks[_iINdex].tTime.fCurTime = m_vecAttacks[_iINdex].tTime.fCoolTime;
	}

	void MonsterScript::AddAttack(const tMonsterAttack& _tMonsterAttack)
	{
		m_vecAttacks.push_back(_tMonsterAttack);
	}

	void MonsterScript::CreateHP()
	{
		m_pHP = new MonsterHP(m_bBoss);
		m_pHP->SetOwner(m_pMonster);
		m_pHP->Initialize();

		if (!m_bBoss)
			SceneManger::AddGameObject(eLayerType::Object, m_pHP);
		else
			SceneManger::AddGameObject(eLayerType::UI, m_pHP);
	}

	void MonsterScript::hit(const tAttackInfo& _tAttackInfo, GameObject* _pAttackObj)
	{
		if(m_pHP)
			m_pHP->ActiveOn();

		//m_tObjectInfo.fHP -= _tAttackInfo.fAttackDamage;
		m_tHitInfo.fHitRcnt = _tAttackInfo.fAttRcnt;
		m_tHitInfo.fHitRigidityTime = _tAttackInfo.fAttRigidityTime;
		m_tHitInfo.fHitUpperRcnt = _tAttackInfo.fAttUpperRcnt;

		std::wstring strAttackName = _pAttackObj->GetName();
		Collider2D* pCollider = GetOwner()->GetComponent<Collider2D>();
		Vector3 vPos = pCollider->GetPosition();
		BattleManager::CheckDamage(m_tObjectInfo, _tAttackInfo, strAttackName, vPos);
		
		if (m_tObjectInfo.fHP <= 0.f)
		{
			m_tObjectInfo.fHP = 0.f;

			EventManager::ChangeMonsterFSMState(m_pFSM, Monster::eMonsterState::dead);

			//캐릭터 공격 오브젝트에서 내 객체 삭제
			_pAttackObj->GetScript<AttackScript>()->Erase(pCollider->GetColliderID());
		}
		else if (!m_bBoss)
		{
			EventManager::ChangeMonsterFSMState(m_pFSM, Monster::eMonsterState::hit);
			m_pMonster->SetDir(m_tHitInfo.fHitDir);
		}

		//공반
		if (m_bReflex)
			reflex(_tAttackInfo,_pAttackObj);
	}

	void MonsterScript::update_cooltime()
	{
		for (UINT i = 0; i < m_vecAttacks.size(); ++i)
		{
			tMonsterAttack& tAttck = m_vecAttacks[i];
			if (tAttck.tTime.fCurTime < tAttck.tTime.fCoolTime)
				m_vecAttacks[i].tTime.fCurTime += Time::DeltaTime();

			else
			{
				m_iCurAttackCount = i;
				m_vecAttacks[i].tTime.fCurTime = 0.f;
				EventManager::ChangeMonsterFSMState(m_pFSM, Monster::eMonsterState::attack);
				break;
			}
		}
	}
	void MonsterScript::reflex(const tAttackInfo& _tAttackInfo, GameObject* _pAttackObj)
	{
		PlayerAttackObject* pAttackObj = dynamic_cast<PlayerAttackObject*>(_pAttackObj);
		
		tAttackInfo tAtt = {};
		tAtt.fAttackDamage = _tAttackInfo.fAttackDamage/2.f;
		tAtt.fAttUpperRcnt = 0.f;
		tAtt.fAttRcnt = 0.f;

		pAttackObj->GetPlayer()->GetScript<PlayerScript>()->Hit(tAtt,L"");
	}
}