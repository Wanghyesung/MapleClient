#pragma once

namespace W
{
	class GameObjectManager
	{
	public:
		static void Initialize();
		
	private:
		static std::unordered_map < UINT, std::function<GameObject* ()>> m_hashObject;
	};
}
