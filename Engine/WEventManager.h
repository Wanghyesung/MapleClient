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

		CHANGE_PLAYER_EQUIP,
		SCENE_CHANGE,

		ADD_PLAYER_POOL,
		ADD_MONSTER_POOL,
		
		END,
	};

	struct tTransformInfo
	{
		Vector3 vPosition;
		Vector3 vRotation;
	};

	struct OBJECT_DATA
	{
		wstring stringData;
		tTransformInfo tTransformData;
	};

	struct tEvent
	{
		EVENT_TYPE eEventType;

		DWORD_PTR wParm;
		DWORD_PTR lParm;
		LONG_PTR accParm;//추가 인자

		OBJECT_DATA tObjectData; 
	};
	
	class EventManager
	{
	public:
		static void Update();
		static void Initialize();
		static void AddEvent(const tEvent& _tEve);
		
		static void CreateObject(GameObject* _pObj, eLayerType _eLayer);
		static void CreateObjectID(UINT _iSceneLayerCreateIdId, const tTransformInfo& _tTransformInfo, const wstring& _strObjectName);
		static void DeleteObject(GameObject* _pObj,  Scene* _pScene);
		static void DeleteObjectID(UINT _ID, eLayerType _eType, UINT _iSceneID);

		static void ChangeScene(const std::wstring& _strNextScene);
		static void ChanagePlayerEquip(UINT _iPlayerInfo, const wstring& _strEquipName);
	
		static void AddPlayer(UINT _iPlayerID, vector<UINT> _vecPlayerID);
		static void AddOtherPlayer(UINT _iPlayerID);

		static void UpdateTransform(UINT _ID, eLayerType _eType, const tTransformInfo& _tTransformInfo);
		static void UpdateState(UINT _iLayerID, int _iState, const wstring& _strState);
		
	private:
		static void create_object(DWORD_PTR _lParm, DWORD_PTR _wParm, LONG_PTR _accParm, const OBJECT_DATA& _tObjData);
		static void delete_object(DWORD_PTR _lParm, DWORD_PTR _wParm, LONG_PTR _accParm, const OBJECT_DATA& _tObjData);

		static void create_object_id(DWORD_PTR _lParm, DWORD_PTR _wParm, LONG_PTR _accParm, const OBJECT_DATA& _tObjData);
		static void delete_object_id(DWORD_PTR _lParm, DWORD_PTR _wParm, LONG_PTR _accParm, const OBJECT_DATA& _tObjData);

		static void change_scene(DWORD_PTR _lParm, DWORD_PTR _wParm, LONG_PTR _accParm, const OBJECT_DATA& _tObjData);
		static void change_player_equip(DWORD_PTR _lParm, DWORD_PTR _wParm, LONG_PTR _accParm, const OBJECT_DATA& _tObjData);

		static void add_player(DWORD_PTR _lParm, DWORD_PTR _wParm, LONG_PTR _accParm, const OBJECT_DATA& _tObjData);
		static void add_other_player(DWORD_PTR _lParm, DWORD_PTR _wParm, LONG_PTR _accParm, const OBJECT_DATA& _tObjData);

		static void delete_player(DWORD_PTR _lParm, DWORD_PTR _wParm, LONG_PTR _accParm, const OBJECT_DATA& _tObjData);
		static void delete_otehr_player(DWORD_PTR _lParm, DWORD_PTR _wParm, LONG_PTR _accParm, const OBJECT_DATA& _tObjData);

		static void update_state(DWORD_PTR _lParm, DWORD_PTR _wParm, LONG_PTR _accParm, const OBJECT_DATA& _tObjData);
		static void update_trasnform(DWORD_PTR _lParm, DWORD_PTR _wParm, LONG_PTR _accParm, const OBJECT_DATA& _tObjData);

	private:
		static void excute(const tEvent& _tEve);

	private:
		static std::function<void(DWORD_PTR, DWORD_PTR, LONG_PTR, OBJECT_DATA)> m_arrFunction[(UINT)EVENT_TYPE::END];
		static std::vector<tEvent> m_vecEvent[2];
		
		static atomic<int> m_iActiveIdx;

		
		static RWLock m_lock;
		static UINT m_iNextScene;

	};
}


