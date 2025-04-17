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
		auto iter = m_hashGameObject.begin();
		for (iter; iter != m_hashGameObject.end(); ++iter)
		{
			delete iter->second;
			iter->second = nullptr;
		} 

	}
	void Layer::Initialize()
	{
	}
	void Layer::Update()
	{
		// 임시 객체 참조 const auto iter& = m_hashGameObject.begin();

		auto iter = m_hashGameObject.begin();
		for (iter; iter != m_hashGameObject.end(); ++iter)
		{
			GameObject* gameObj = iter->second;

			if (gameObj->GetState() != GameObject::eState::Active)
				continue;

			gameObj->Update();
		}
	}
	void Layer::LateUpdate()
	{
		auto iter = m_hashGameObject.begin();
		for (iter; iter != m_hashGameObject.end(); ++iter)
		{
			GameObject* gameObj = iter->second;

			if (gameObj->GetState() != GameObject::eState::Active)
				continue;

			gameObj->LateUpdate();
		}
	}
	void Layer::Render()
	{
		auto iter = m_hashGameObject.begin();
		for (iter; iter != m_hashGameObject.end(); ++iter)
		{
			GameObject* gameObj = iter->second;

			if (gameObj->GetState() != GameObject::eState::Active)
				continue;

			gameObj->Render();
		}
	}


	void Layer::DestroyAll(Scene* _pScene)
	{
		auto iter = m_hashGameObject.begin();
		for (iter; iter != m_hashGameObject.end(); ++iter)
		{
			GameObject* gameObj = iter->second;

			EventManager::DeleteObject(gameObj, _pScene);
		}

	}

	void Layer::AddGameObject(GameObject* _pGameObj)
	{
		UINT iObjectID = _pGameObj->GetObjectID();

		if (m_hashGameObject.find(iObjectID) != m_hashGameObject.end())
			assert(nullptr);

		m_hashGameObject.insert(std::make_pair(iObjectID,_pGameObj));
	}

	void Layer::EraseOnVector(GameObject* _pGameObject)
	{
		UINT iGameObjectID = _pGameObject->GetObjectID();
		auto iter = m_hashGameObject.find(iGameObjectID);
		GameObject* pGameObject = iter->second;

		if (pGameObject != nullptr)
			m_hashGameObject.erase(iGameObjectID);
	}

	GameObject* Layer::FindObject(UINT _ID)
	{
		if (m_hashGameObject.find(_ID) == m_hashGameObject.end())
			return nullptr;

		return m_hashGameObject[_ID];
	}

	GameObject* Layer::FindObjectByName(const std::wstring& _strName)
	{
		auto iter = m_hashGameObject.begin();

		for (iter; iter != m_hashGameObject.end(); ++iter)
		{
			GameObject* gameObj = iter->second;

			if (gameObj->GetName() == _strName)
				return gameObj;
		}
		return nullptr;
	}

}