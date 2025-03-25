#include "WScene.h"
#include "WUI.h"
#include "WThreadPool.h"
#include "..\Engine\WMonsterHP.h"
#include "..\Engine\WMonsterManager.h"
namespace W
{
	Scene::Scene()
	{
		m_vecLayer.resize((UINT)W::enums::eLayerType::End);
	}
	Scene::~Scene()
	{
	}
	void Scene::Initialize()
	{
	}
	void Scene::Update()
	{
		for (Layer& layer : m_vecLayer)
		{
			layer.Update();
		}
	}
	void Scene::LateUpdate()
	{
		for (Layer& layer : m_vecLayer)
		{
			layer.LateUpdate();
		}
	}
	void Scene::Render()
	{
		for (Layer& layer : m_vecLayer)
		{
			layer.Render();
		}
	}

	void Scene::Destroy()
	{
		for (UINT i = 0; i < m_vecLayer.size(); ++i)
		{
			if (i == (UINT)eLayerType::UI)
				continue;

			m_vecLayer[i].Destory();
		}
	}

	void Scene::OnEnter()
	{
		for (int i = 0; i < m_vecResource.size(); ++i)
		{
			ThreadPool::LoadingResource<Texture>(m_vecResource[i].first, m_vecResource[i].second);
		}
	}
	void Scene::OnExit()
	{
		for (int i = 0; i < m_vecResource.size(); ++i)
		{
			ThreadPool::DeleteResource<Texture>(m_vecResource[i].first);
		}
	}
	void Scene::AddGameObject(eLayerType _eType, GameObject* _pGameObj)
	{
		m_vecLayer[(UINT)_eType].AddGameObject(_pGameObj);
		_pGameObj->SetLayerType(_eType);
	}

	void Scene::DeleteMonsterObject()
	{
		Layer& monsterLayer = GetLayer(eLayerType::Monster);
		const std::vector<GameObject*> vecMonster = monsterLayer.GetGameObjects();
		for (int i = 0; i < vecMonster.size(); ++i)
			MonsterManager::AddDeleteObject(vecMonster[i]);
		
		Layer& monAttackLayer = GetLayer(eLayerType::MonsterAttack);
		const std::vector<GameObject*> vecAttack = monAttackLayer.GetGameObjects();
		for (int i = 0; i < vecAttack.size(); ++i)
			MonsterManager::AddDeleteObject(vecAttack[i]);

		Layer& monStatLayer = GetLayer(eLayerType::Object);
		const std::vector<GameObject*> vecStat = monStatLayer.GetGameObjects();
		for (int i = 0; i < vecStat.size(); ++i)
			MonsterManager::AddDeleteObject(vecStat[i]);

		Layer& monsterUI = GetLayer(eLayerType::UI);
		MonsterHP* pHp = monsterUI.FindObject<MonsterHP>();
		if (pHp)
			pHp->DeleteHP();
		
	}
}