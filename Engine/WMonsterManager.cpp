#include "WMonsterManager.h"
#include "WMonster.h"
#include "WTime.h"
#include "WEventManager.h"
#include "WMonsterScript.h"
#include "WMonsterHP.h"
#include "WItemObject.h"
#include "WIconUI.h"
#include "WSceneManger.h"

namespace W
{
	std::vector<Monster*> MonsterManager::m_vecDeadObjs = {};
	std::vector<float> MonsterManager::m_vecReSpwanTime = {};
	std::vector<GameObject*> MonsterManager::m_vecExpectedDeleteObjs = {};

	void MonsterManager::Update()
	{
		std::vector<float>::iterator timeiter = m_vecReSpwanTime.begin();
		std::vector<Monster*>::iterator objiter = m_vecDeadObjs.begin();

		for (timeiter; timeiter != m_vecReSpwanTime.end(); )
		{
			*timeiter -= Time::DeltaTime();
			if (*timeiter <= 0.f)
			{
				respawn(*objiter);
				objiter = m_vecDeadObjs.erase(objiter);
				timeiter = m_vecReSpwanTime.erase(timeiter);
			}
			else
			{
				++timeiter;
				++objiter;
			}
		}
	}

	void MonsterManager::AddDeadObject(Monster* _pGameObj)
	{
		m_vecDeadObjs.push_back(_pGameObj);
		m_vecReSpwanTime.push_back(7.f);

		create_item(_pGameObj);
	}

	void MonsterManager::AddDeleteObject(GameObject* _pGameObj)
	{
		_pGameObj->SetState(GameObject::eState::Paused);
		SceneManger::Erase(_pGameObj);
		m_vecExpectedDeleteObjs.push_back(_pGameObj);
	}

	void MonsterManager::DeleteMonster()
	{
		for (int i = 0; i < m_vecExpectedDeleteObjs.size(); ++i)
		{
			delete m_vecExpectedDeleteObjs[i];
			m_vecExpectedDeleteObjs[i] = nullptr;
		}
		m_vecExpectedDeleteObjs.clear();
	}

	void MonsterManager::respawn(Monster* _pGameObj)
	{
		_pGameObj->SetState(GameObject::Active);
		_pGameObj->GetComponent<Collider2D>()->SetActive(true);
		_pGameObj->SetDead(false);

		MonsterScript* pScript =_pGameObj->GetScript<MonsterScript>();
		tObjectInfo& tInfo = pScript->m_tObjectInfo;
		pScript->m_pHP->m_fHP = tInfo.fMaxMP;
		tInfo.fHP = tInfo.fMaxMP;
		pScript->CreateHP();
	}

	void MonsterManager::create_item(Monster* _pGameObj)
	{
		const std::vector<std::wstring>& vecItems = _pGameObj->GetItemVec();
		int iCnt = _pGameObj->GetCreateCount();
		float xForce = 1;
		for (int i = 0; i < iCnt; ++i)
		{
			srand(time(NULL));
			int iIndx = (rand() % vecItems.size());

			std::wstring strItemName = vecItems[iIndx];
			ItemObject* pItem = new ItemObject(strItemName);

			Vector3 vPos = _pGameObj->GetComponent<Collider2D>()->GetPosition();
			pItem->GetComponent<Transform>()->SetPosition(vPos);
			pItem->SetVelociy(Vector2(xForce* i, 3.f));
			EventManager::CreateObject(pItem, eLayerType::ItemObject);

			xForce *= -1.f;
		}
	}
}