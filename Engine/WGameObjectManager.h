#pragma once

namespace W
{
	class GameObjectManager
	{
	public:
		static void Initialize();
	
	public:
		static GameObject* GetMonsterOfID(UINT _ID);


	private:
		static std::unordered_map < UINT, std::function<GameObject* ()>> m_hashObject;
		
	
	};
}
