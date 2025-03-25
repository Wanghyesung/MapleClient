#pragma once
#include "WLayer.h"
#include "WGameObject.h"
#include "WScene.h"
#include "WSceneManger.h"
#include "WTransform.h"

namespace W::object
{
	template <typename T>
	static __forceinline T* Intantiate(enums::eLayerType _eLayer)
	{
		T* gameObj = new T();
		Scene* pScene = SceneManger::GetActiveScene();
		pScene->AddGameObject(_eLayer, gameObj);

		return gameObj;
	}


	template <typename T>
	static __forceinline T* Instantiate(Vector3 vPos, enums::eLayerType _eLayer)
	{
		T* gameObj = new T();
		Transform* pTransform = gameObj->GetComponent<Transform>();
		pTransform->SetPosition(vPos);

		Scene* scene = SceneManger::GetActiveScene();
		scene->AddGameObject(_eLayer, gameObj);

		return gameObj;
	}

	template <typename T>
	static __forceinline T* Instantiate(Vector3 vPos, Vector3 vRotate, enums::eLayerType _eLayer)
	{
		T* gameObj = new T();
		Transform* tr = gameObj->GetComponent<Transform>();
		tr->SetPosition(vPos);
		tr->SetRotation(vRotate);

		Scene* scene = SceneManger::GetActiveScene();
		scene->AddGameObject(_eLayer, gameObj);

		return gameObj;
	}

	template <typename T>
	static __forceinline T* Instantiate(Vector3 vPos, Vector3 vRotate, Vector3 vScale, enums::eLayerType _eLayer)
	{
		T* gameObj = new T();
		Transform* tr = gameObj->GetComponent<Transform>();
		tr->SetPosition(vPos);
		tr->SetRotation(vRotate);
		tr->SetScale(vScale);

		Scene* scene = SceneManger::GetActiveScene();
		scene->AddGameObject(_eLayer, gameObj);

		return gameObj;
	}

	static __forceinline void Destroy(GameObject* pGameObj)
	{
		pGameObj->SetState(W::GameObject::eState::Dead);
	}

}