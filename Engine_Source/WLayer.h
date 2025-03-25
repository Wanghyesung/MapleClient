#pragma once

#include "WGameObject.h"


namespace W
{
	class Scene;
	class Layer
	{
	public:
		Layer();
		~Layer();

		virtual void Initialize();
		virtual void Update();
		virtual void LateUpdate();
		virtual void Render();

		template<typename T>
		T* FindObject();

		virtual void Destory();
		virtual void DestroyAll(Scene* _pScene);

		void AddGameObject(GameObject* _pGameObj);
		const std::vector<GameObject*>& GetGameObjects() { return m_vecGameObject; }

		void EraseOnVector(GameObject* _pGameObject);

	private:
		std::vector<GameObject*> m_vecGameObject;


		friend class UIManger;
	};

	template<typename T>
	inline T* Layer::FindObject()
	{
		for (int i = 0; i < m_vecGameObject.size(); ++i)
		{
			T* pTarget = dynamic_cast<T*>(m_vecGameObject[i]);
			if (pTarget == nullptr)
				continue;
			
			return pTarget;
		}
		return nullptr;
	}
}


