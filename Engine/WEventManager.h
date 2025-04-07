#pragma once
#include "Engine.h"

namespace W
{
	class GameObject;

	enum class EVENT_TYPE
	{
		CREATE_OBJECT,
		DELET_OBJECT,
		SCENE_CHANGE,

		ADD_PLAYER_POOL,
		ADD_MONSTER_POOL,
		
		END,
	};

	struct tEvent
	{
		DWORD_PTR wParm;
		DWORD_PTR lParm;
		LONG_PTR accParm;//추가 인자
		EVENT_TYPE eEventType;
	};
	class EventManager
	{
	public:
		static void Update();
		static void AddEvent(const tEvent& _tEve) { m_vecEvent.push_back(_tEve); }
		
		static void CreateObject(GameObject* _pObj, eLayerType _eLayer);
		static void DeleteObject(GameObject* _pObj, class Scene* _pScene);
	
		static void ChangeScene(const std::wstring& _strNextScene);
	
	private:
		static void excute(const tEvent& _tEve);

	private:
		static std::vector<tEvent> m_vecEvent;

	
		static std::wstring m_strNextScene;
	};
}


