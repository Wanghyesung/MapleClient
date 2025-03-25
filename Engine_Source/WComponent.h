#pragma once
#include "WEntity.h"

namespace W
{
	using namespace W::enums;
	using namespace W::math;

	class GameObject;

	class Component
	{
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
	private:
		const eComponentType m_eType;
		GameObject* m_pOwner;

	};
}


