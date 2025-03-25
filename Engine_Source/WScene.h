#pragma once

#include "WEntity.h"
#include "WLayer.h"
#include "WGraphicDevice_Dx11.h"
#include "WAudioSource.h"
namespace W
{
	class Scene : public Entity
	{
	public:
		struct tMapSize
		{
			float LX;
			float LY;
			float RX;
			float RY;
		};

		//이동가능한 맵 사이즈
		struct tMapPossibleSize
		{
			float LX;
			float RX;
		};

		Scene();
		virtual ~Scene();

		virtual void Initialize();
		virtual void Update();
		virtual void LateUpdate();
		virtual void Render();
		virtual void Destroy();

		virtual void OnEnter();
		virtual void OnExit();

		virtual void CreateBackground() {};

		virtual void StartSound() {};
		virtual void EndSound() {};

		void AddGameObject(eLayerType _eType, GameObject* _pGameObj);
		void DeleteMonsterObject();

		template <typename T>
		std::vector<T*> FindObjectsOfType()
		{
			std::vector<T*> vecObjects = {};
			for (Layer& layer : m_vecLayer)
			{
				const std::vector<GameObject*> vecGameObjects =
					layer.GetGameObjects();
				
				for (GameObject* obj : vecGameObjects)
				{
					T* buff = dynamic_cast<T*>(obj);
					if (buff != nullptr)
						vecObjects.push_back(buff);
				}
			}
			return vecObjects;
		}
		
		Layer& GetLayer(eLayerType _eType) { return m_vecLayer[(UINT)_eType];}

		void SetMapSize(float _lx, float _ly, float _rx, float _ry) 
		{
			m_tMapSize.LX = _lx; m_tMapSize.LY = _ly;
			m_tMapSize.RX = _rx; m_tMapSize.RY = _ry;
		}
		void SetMapPossibleSize(float _lx, float _rx)
		{
			m_tPossibleSize.LX = _lx;	m_tPossibleSize.RX = _rx; 
		}

		tMapSize GetMapSize() { return m_tMapSize; }
		tMapPossibleSize GetMapPossibleSize() { return m_tPossibleSize; }

		void EraseObject(eLayerType _eType, GameObject* _pGameObj){ m_vecLayer[(UINT)_eType].EraseOnVector(_pGameObj); }

		
	protected:
		//맵 나갈 때, 맵 들어올 때 리소스 삭제, 할당
		std::vector<std::pair<std::wstring, std::wstring>> m_vecResource;

	private:
		std::vector<Layer> m_vecLayer;

		tMapSize m_tMapSize;
		tMapPossibleSize m_tPossibleSize;

		class InterfaceUI* m_pInterface;
		class Inventory* m_pInventory;
		class SKillStorage* m_pSKillStorage;
		class Stat* pStat;
		class EquipState* pEquipState;
	};
}


