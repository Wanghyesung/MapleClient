#pragma once

#include "WEntity.h"
#include "ComponentHeader.h"
#include "WMaterial.h"



namespace W
{
	class GameObject : public Entity
	{
	public:
		enum eState
		{
			Active,
			Paused,
			Dead,
		};

		GameObject();
		GameObject(const GameObject& _pOrigin);
		virtual ~GameObject();

		virtual void Initialize();
		virtual void Update();
		virtual void LateUpdate();
		virtual void Render();

		//네트워크
		virtual void UpdateState(const wstring& _strStateName, int _iState);


		template <typename T>
		T* GetComponent()
		{
			UINT iComponentID = T::GetComponentID();

			if (m_vecComponent[iComponentID] == nullptr)
				return nullptr;

			return static_cast<T*>(m_vecComponent[iComponentID]);
		}

		template<typename T>
		T* AddComponent()
		{
			UINT iComponentID = T::GetComponentID();

			if (m_vecComponent[iComponentID] != nullptr)
				assert(nullptr);
			
			T* comp = new T();
			if (iComponentID == (UINT)eComponentType::Script)
				m_vecScript.push_back(comp);
			else
				m_vecComponent[iComponentID] = comp;
			
			comp->SetOwner(this);
			return comp;
		}

		template<typename T>
		T* GetScript()
		{
			for (Component* pScript : m_vecScript)
			{
				T* pTarget = dynamic_cast<T*>(pScript);
				if (pTarget != nullptr)
					return pTarget;
			}
		}

		void SetState(eState _eState) { m_eState = _eState; }
		eState GetState() { return m_eState; }

		void SetLayerType(eLayerType _eLayerType) { m_eLayerType = _eLayerType; }
		eLayerType GetLayerType() { return m_eLayerType; }

		void SetDir(int _iDir) { m_iDir = _iDir; }
		int GetDir() { return m_iDir; }

		void SetAnimIdx(int _iIdx) { m_iAnimIdx = _iIdx; }
		int GetAnimIdx() { return m_iAnimIdx; }

		void SetPoolObject(bool _bPoolObject) { m_bObjectPool = _bPoolObject; }
		bool IsPoolObject() { return m_bObjectPool; }

		void SetObjectID(UINT _ID) { m_iObjectID = _ID; }
		UINT GetObjectID() { return m_iObjectID; }

		void SetClientObject(bool _bClientObject) { m_bClientObject = _bClientObject; }
		bool IsClientObject() { return m_bClientObject; }

		void SetRender(bool _bRender) { m_bRender = _bRender; }
		bool IsRender() { return m_bRender; }

	private:
		static void SetCreateID(UINT _ID) { CREATE_ID = _ID; }

	protected:
		//packet
		int m_iDir;
		int m_iAnimIdx;
		std::wstring m_strCurStateName;

	private:
		eState m_eState;
		std::vector<Component*> m_vecComponent;
		std::vector<Component*> m_vecScript;

		eLayerType m_eLayerType;

		bool m_bRender;

		bool m_bObjectPool;
		bool m_bClientObject;

		UINT m_iObjectID;
		static UINT CREATE_ID;

		friend class GameObjectManager;
	};
}


