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
		static bool CreateScene(const std::wstring& name)
		{
			T* scene = new T();

			m_hashSceneID.insert(std::make_pair(scene->GetSceneID(), scene));

			m_pActiveScene = scene;
			scene->SetName(name);
			scene->Initialize();

			return true;
		}
		static Scene* GetActiveScene() { return m_pActiveScene; }
		static Scene* LoadScene(UINT _iSceneID);

		static void AddGameObject(eLayerType _eType, GameObject* _pGameObj){ m_pActiveScene->AddGameObject(_eType, _pGameObj);}
		static GameObject* FindPlayer();
		static GameObject* FindObject(UINT _ID, eLayerType _eLayerType);
		static GameObject* FindObject(Scene* _pScene, UINT _ID, eLayerType _eLayerType);
		template <typename T>
		static T* GetUI()
		{
			std::unordered_map<UINT, GameObject*> hashUI =
				m_pActiveScene->GetLayer(eLayerType::UI)->GetGameObjects();
			
			auto iter = hashUI.begin();
			for (iter; iter != hashUI.end(); ++iter )
			{
				UI* pUI = dynamic_cast<UI*>(iter->second);
				if (pUI == nullptr)
					continue;

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
						const std::vector<UI*>& vecChildUI = pTarget->GetChildUI();
						for (UI* pChildUI : vecChildUI)
						{
							queue.push(pChildUI);
						}
					}
				}
			}
			return nullptr;
		}

		static Scene* FindScene(UINT _iSceneID);
		static Scene* FindScene(const wstring& _strSceneName);

		static void SwapObject(Scene* _pPrevScene, Scene* _pNextScene, GameObject* _pGameObject);
		static void SwapObject(Scene* _pPrevScene, Scene* _pNextScene, const std::wstring& _strGameName, eLayerType _eLayerType);
		static void SwapUI(Scene* _pPrevScene, Scene* _pNextScene);
		static void SwapPlayer(Scene* _pPrevScene, Scene* _pNextScene);
		static void SwapCamera();
	
		static void SendEnter();

		static void CompletedMapData() {m_bWaitForMapData.store(false); }
		static void StartWaitForMapData() {m_bWaitForMapData.store(true); }

		static bool IsWaitForMapData() { return m_bWaitForMapData.load(); }

	private:
		static Scene* m_pActiveScene;
		static std::unordered_map<UINT, Scene*> m_hashSceneID;

		static atomic<bool> m_bWaitForMapData;

	};
}


