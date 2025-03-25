#include "WLayer.h"
#include "..\Engine\WEventManager.h"
#include "WScene.h"
namespace W
{
	Layer::Layer()
	{
		
	}
	Layer::~Layer()
	{
		for (GameObject* gameObj : m_vecGameObject)
		{
			if (gameObj == nullptr)
				continue;

			delete gameObj;
			gameObj = nullptr;
		}
	}
	void Layer::Initialize()
	{
	}
	void Layer::Update()
	{
		for (GameObject* gameObj : m_vecGameObject)
		{
			if (gameObj->GetState() != GameObject::eState::Active)
				continue;

			gameObj->Update();
		}
	}
	void Layer::LateUpdate()
	{
		for (GameObject* gameObj : m_vecGameObject)
		{
			if (gameObj->GetState() != GameObject::eState::Active)
				continue;
			gameObj->LateUpdate();
		}
	}
	void Layer::Render()
	{
		for (GameObject* gameObj : m_vecGameObject)
		{
			if (gameObj->GetState() != GameObject::eState::Active)
				continue;
			gameObj->Render();
		}
	}

	void Layer::Destory()
	{
		std::set<GameObject*> setDeleteGameObj = {};

		for (GameObject* pGameObj : m_vecGameObject)
		{
			if (pGameObj->GetState() ==
				GameObject::eState::Dead)
				setDeleteGameObj.insert(pGameObj);
		}

		typedef std::vector<GameObject*>::iterator GameObjectIter;
		for (GameObjectIter iter = m_vecGameObject.begin();
			iter != m_vecGameObject.end();)
		{
			std::set<GameObject*>::iterator deleteIter =
				setDeleteGameObj.find(*(iter));

			if (deleteIter != setDeleteGameObj.end())
			{
				iter = m_vecGameObject.erase(iter);
				continue;
			}

			++iter;
		}

		//메모리 해제
		for (GameObject* pObj : setDeleteGameObj)
		{
			delete pObj;
			pObj = nullptr;
		}

	}

	void Layer::DestroyAll(Scene* _pScene)
	{
		for (int i = 0; i < m_vecGameObject.size(); ++i)
		{
			EventManager::DeleteObject(m_vecGameObject[i], _pScene);
		}
	}

	void Layer::AddGameObject(GameObject* _pGameObj)
	{
		m_vecGameObject.push_back(_pGameObj);
	}

	void Layer::EraseOnVector(GameObject* _pGameObject)
	{
		std::vector<GameObject*>::iterator iter = m_vecGameObject.begin();
		for (iter; iter != m_vecGameObject.end(); ++iter)
		{
			if (*iter == _pGameObject)
			{
				m_vecGameObject.erase(iter);
				return;
			}
		}
	}

}