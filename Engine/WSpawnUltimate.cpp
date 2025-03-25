#include "WSpawnUltimate.h"
#include "WTime.h"
#include "WPlayer.h"
#include "WPlayerScript.h"
#include "WEventManager.h"
#include "WUltimateShuriken.h"
#include "WAttackScript.h"
#include "WMonsterScript.h"
#include "WSceneManger.h"
namespace W
{
	SpawnUltimate::SpawnUltimate():
		m_fCreateTime(2.f),
		m_fActiveTime(20.f),
		m_iCurIndex(0)
	{
		std::shared_ptr<Material> pMater = std::make_shared<Material>();
		pMater->SetRenderinMode(eRenderingMode::Transparent);
		pMater->SetShader(Resources::Find<Shader>(L"ObjectShader"));
		Resources::Insert(L"pSpawnMater", pMater);

		MeshRenderer* pRenderer = AddComponent<MeshRenderer>();
		pRenderer->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
		pRenderer->SetMaterial(pMater);

		m_vecCreateCount.push_back(3);
		m_vecCreateCount.push_back(4);
		m_vecCreateCount.push_back(5);

		m_vecShurikenDir.resize(3);
		m_vecShurikenDir[0].push_back(Vector2(0.5f, 0.5f));
		m_vecShurikenDir[0].push_back(Vector2(-0.3f, 0.7f));
		m_vecShurikenDir[0].push_back(Vector2(0.f, 1.f));

		m_vecShurikenDir[1].push_back(Vector2(0.5f, 0.5f));
		m_vecShurikenDir[1].push_back(Vector2(-0.5f, 0.5f));
		m_vecShurikenDir[1].push_back(Vector2(0.f, 1.f));
		m_vecShurikenDir[1].push_back(Vector2(0.8f, 0.2f));

		m_vecShurikenDir[1].push_back(Vector2(0.5f, 0.5f));
		m_vecShurikenDir[1].push_back(Vector2(1.f, 0.f));
		m_vecShurikenDir[1].push_back(Vector2(0.f, 1.f));
		m_vecShurikenDir[1].push_back(Vector2(0.6f, -0.4f));
		m_vecShurikenDir[2].push_back(Vector2(-0.3f, 0.7f));

		AddComponent<Collider2D>()->SetSize(Vector2(0.f, 0.f));
		AddComponent<AttackScript>()->SetDeleteTime(1000.f);
		GetComponent<AttackScript>()->SetDeleteObject(false);
	}
	SpawnUltimate::~SpawnUltimate()
	{

	}
	void SpawnUltimate::Initialize()
	{
		m_pTarget = nullptr;

		PlayerAttackObject* pAttackObj1 = GetPlayer()->GetScript<PlayerScript>()->GetPlayerSkill(L"ultimate1");
		PlayerAttackObject* pAttackObj2 = GetPlayer()->GetScript<PlayerScript>()->GetPlayerSkill(L"ultimate2");
		
		pAttackObj1->Initialize();
		pAttackObj2->Initialize();

		EventManager::CreateObject(pAttackObj1, eLayerType::AttackObject);
		EventManager::CreateObject(pAttackObj2, eLayerType::AttackObject);

		
		const std::vector<GameObject*>& vecMonster =
			SceneManger::GetActiveScene()->GetLayer(eLayerType::Monster).GetGameObjects();

		//가장 체력이 높은 몬스터
		float fMax = 0.f;
		for (int i = 0; i < vecMonster.size(); ++i)
		{
			if (vecMonster[i]->GetState() == GameObject::eState::Paused)
				continue;

			float fHP = vecMonster[i]->GetScript<MonsterScript>()->GetObjectInfo().fHP;
			if (fMax < fHP)
			{
				fMax = fHP;
				m_pTarget = vecMonster[i];
			}
		}
	}
	void SpawnUltimate::Update()
	{
		m_fCurCreateTime += Time::DeltaTime();
		m_fCurActiveTime += Time::DeltaTime();

		if (m_fCurActiveTime >= m_fActiveTime)
		{
			m_fCurActiveTime = 0.f;
			EventManager::AddPlayerPool(this);
		}

		if (m_fCurCreateTime >= m_fCreateTime)
		{
			m_fCurCreateTime = 0.f;
			create();
		}

		GameObject::Update();
	}
	void SpawnUltimate::LateUpdate()
	{
		GameObject::LateUpdate();
	}
	void SpawnUltimate::Render()
	{
		//GameObject::Render();
	}

	void SpawnUltimate::off()
	{
		m_fCurActiveTime = 0.f;
		m_fCurCreateTime = 0.f;
		m_pTarget = nullptr;


		PlayerAttackObject::Off();
	}

	void SpawnUltimate::create()
	{
		if (!m_pTarget)
			return;

		for (int i = 0; i < m_vecCreateCount[m_iCurIndex]; ++i)
		{
			for (int j = 0; i < m_vecShurikenDir[m_iCurIndex].size(); ++i)
			{
				PlayerAttackObject* pAttackObj = GetPlayer()->GetScript<PlayerScript>()->GetPlayerSkill(L"ultimate_suriken");
				UltimateShuriken* pShuriken = dynamic_cast<UltimateShuriken*>(pAttackObj);
				Vector2 vDir = m_vecShurikenDir[m_iCurIndex][i];
				pShuriken->SetTarget(m_pTarget);
				pShuriken->SetStartPos(vDir);
				pShuriken->Initialize();
				EventManager::CreateObject(pAttackObj, eLayerType::AttackObject);
			}
			
		}
		++m_iCurIndex;
		if (m_iCurIndex > 2)
			m_iCurIndex = 0;
	}
	
}