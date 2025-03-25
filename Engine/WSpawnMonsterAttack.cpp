#include "WSpawnMonsterAttack.h"
#include "WMonster.h"
#include "WTime.h"
#include "WSceneManger.h"
#include "WEventManager.h"
#include "WRigidbody.h"
#include "WAnimator.h"
namespace W
{
	SpawnMonsterAttack::SpawnMonsterAttack():
		m_fCreateTime(0.f),
		m_fCurCreateTime(0.f),
		m_iCurIndex(0),
		m_iEndFrame(0),
		m_vecOffset{},
		m_bEndEvent(false)
	{

	}
	SpawnMonsterAttack::~SpawnMonsterAttack()
	{

	}
	void SpawnMonsterAttack::Initialize()
	{
		m_bEndEvent = false;
		m_iCurIndex = 0;
		m_iEndFrame = 0;
		m_fCurCreateTime = 0.f;
		m_fCreateTime = 0.f;
		m_vecVelocity.clear();
		m_vecOffset.clear();
	}
	void SpawnMonsterAttack::Update()
	{
		Monster* pMon = GetOwner();
		int iFrame = pMon->GetComponent<Animator>()->GetActiveAnimation()->GetCurIndex();


		if (m_iEndFrame <= iFrame ||
			pMon->GetState() == GameObject::eState::Paused)
		{
			off();
		}

		GameObject::Update();
	}
	void SpawnMonsterAttack::LateUpdate()
	{
		m_fCurCreateTime += Time::DeltaTime();

		if (m_fCurCreateTime >= m_fCreateTime)
		{
			m_fCurCreateTime = 0.f;
			Vector3 vPosition = GetComponent<Transform>()->GetPosition();

			for (int i = 0; i < m_iCreateCount; ++i)
			{
				MonsterAttackObject* pObj = GetOwner()->GetMonsterSkill(m_strAttackName);
				if (pObj == nullptr)
					return;

				//위치 속도값 정하기
				pObj->GetComponent<Rigidbody>()->SetVelocity(m_vecVelocity[m_iCurIndex]);

				if (++m_iCurIndex >= m_vecVelocity.size())
					m_iCurIndex = 0;

				Vector3 vCreatePos = vPosition;
				vCreatePos.x += m_vecOffset[i].x;
				vCreatePos.y += m_vecOffset[i].y;

				pObj->GetComponent<Transform>()->SetPosition(vCreatePos);
				//속도 전달
				pObj->Initialize();

				EventManager::CreateObject(pObj, eLayerType::MonsterAttack);
			}
		}

		GameObject::LateUpdate();
	}
	void SpawnMonsterAttack::Render()
	{
		GameObject::Render();
	}
	void SpawnMonsterAttack::SetVelocity(const Vector2& _vVelocity, const Vector3& _vOffset)
	{
		m_vecVelocity.push_back(_vVelocity);
		m_vecOffset.push_back(_vOffset);
	}
	void SpawnMonsterAttack::off()
	{
		if (!m_bEndEvent)
		{
			EventManager::AddMonsterPool(this);
			m_bEndEvent = true;
		}
	}
}
