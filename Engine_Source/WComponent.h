#pragma once
#include "WEntity.h"


namespace W
{
	
	class GameObject;

	class Component
	{
		DECLARE_COMPONENT_ID;
	public:
		Component(eComponentType _eType);
		Component(const Component& _pOrigin);
		virtual ~Component();

		virtual Component* CreateClone() { return nullptr; }

		virtual void Initialize();
		virtual void Update();
		virtual void LateUpdate();
		virtual void Render();

		GameObject* GetOwner() { return m_pOwner; }
		void SetOwner(GameObject* _pGameObj) { m_pOwner = _pGameObj; }

		const eComponentType GetComponentType() { return m_eType; }
	private:
		const eComponentType m_eType;
		GameObject* m_pOwner;

	};
}


