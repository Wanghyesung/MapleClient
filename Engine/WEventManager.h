#pragma once
#include "..\Engine_Source\Engine.h"

namespace W
{
	class GameObject;
	class Scene;

	enum class EVENT_TYPE
	{
		UPDATE_STATE,
		UPDATE_TRANSFORM,

		CREATE_PLAYER,
		CREATE_OTHER_PLAYER,
		DELETE_PLAYER,

		CREATE_OBJECT,
		DELET_OBJECT,
		CREATE_OBJECT_ID,
		DELET_OBJECT_ID,

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
		static void CreateObject(UINT _ID, eLayerType _eLayer);
		static void DeleteObject(GameObject* _pObj,  Scene* _pScene);
		static void DeleteObject(UINT _ID, eLayerType _eType);
		static void ChangeScene(const std::wstring& _strNextScene);
	
		static void AddPlayer(UINT _iPlayerID, UINT _iObjectID, vector<UINT> _vecPlayerID, vector<UINT> _vecObjectID);
		static void AddOtherPlayer(UINT _iPlayerID, UINT _iObjectID);

		static void UpdateTransform(UINT _ID, eLayerType _eType, Vector3 _vPosition);
		static void UpdateState(UINT _ID, eLayerType _eType, const wstring& _strAnimState);
	private:
		static void excute(const tEvent& _tEve);

	private:
		static std::vector<tEvent> m_vecEvent;

	
		static std::wstring m_strNextScene;
	};
}


