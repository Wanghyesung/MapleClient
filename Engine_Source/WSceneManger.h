#pragma once

#include "WScene.h"
#include "WUI.h"

namespace W
{
	class SceneManger
	{
	public:
		static void Initialize();
		static void Update();
		static void LateUpdate();
		static void Render();
		static void Release();
		static void Erase(GameObject* _pGameObject);

		template <typename T>
		static bool CreateScene(std::wstring name)
		{
			T* scene = new T();

			std::map<std::wstring, Scene*>::iterator iter
				= m_mapScene.find(name);

			if (iter != m_mapScene.end())
				return false;

			m_mapScene.insert(std::make_pair(name, scene));
			m_pActiveScene = scene;
			scene->Initialize();
			return true;
		}
		static Scene* GetActiveScene() { return m_pActiveScene; }
		static Scene* LoadScene(std::wstring _strName);

		static void AddGameObject(eLayerType _eType, GameObject* _pGameObj){ m_pActiveScene->AddGameObject(_eType, _pGameObj);}
		static GameObject* FindPlayer();
		static GameObject* FindObject(UINT _ID, eLayerType _eLayerType);
		template <typename T>
		static T* GetUI()
		{
			std::unordered_map<UINT, GameObject*> hashUI =
				m_pActiveScene->GetLayer(eLayerType::UI).GetGameObjects();
			
			auto iter = hashUI.begin();
			for (iter; iter != hashUI.end(); ++iter )
			{
				UI* pUI = (UI*)iter->second;

				std::queue<UI*> queue;

				queue.push(pUI);

				while (!queue.empty())
				{
					UI* pTarget = queue.front();
					queue.pop();

					T* pTargetUI = dynamic_cast<T*>(pTarget);
					if (pTargetUI != nullptr)
						return pTargetUI;
					else
					{
						std::vector<UI*> vecChildUI = pTarget->GetChildUI();
						for (UI* pChildUI : vecChildUI)
						{
							queue.push(pChildUI);
						}
					}
				}
			}
			return nullptr;
		}

		static void SwapObject(Scene* _pPrevScene, Scene* _pNextScene, GameObject* _pGameObject);
		static void SwapObject(Scene* _pPrevScene, Scene* _pNextScene, const std::wstring& _strGameName, eLayerType _eLayerType);
		static void SwapUI(Scene* _pPrevScene, Scene* _pNextScene);
		static void SwapPlayer(Scene* _pPrevScene, Scene* _pNextScene);
		static void SwapCamera();
	
	private:
		static Scene* m_pActiveScene;
		static std::map<std::wstring, Scene*> m_mapScene;
	};
}


