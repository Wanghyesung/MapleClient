#pragma once
#include "Engine.h"

namespace W
{
	class Entity
	{
	public:
		Entity();
		Entity(const Entity& _pOrigin);
		~Entity();

		void SetName(const std::wstring& name) { m_strName = name; }
		std::wstring& GetName() { return m_strName; }

	private:
		std::wstring m_strName;
	};
}


