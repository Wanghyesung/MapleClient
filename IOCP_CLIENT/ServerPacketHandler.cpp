#include "pch.h"
#include "ServerPacketHandler.h"

#include "WEventManager.h"
#include "NetFunc.h"
#include "WGameObjectManager.h"
#include "..\Engine_Source\WGameObject.h"
#include "..\Engine_Source\WTransform.h"
#include "..\Engine_Source\WSceneManger.h"
#include "..\Engine\WObjectPoolManager.h"
//#include "..\Engine\WPlayer.h"
shared_ptr< ClientService> GClientService;
PacketHandlerFunc GPacketHandler[UINT16_MAX];
unordered_map<string, wstring> GHashStringToWstring = {};
unordered_map<wstring, string> GHashWstringToString = {};

extern UINT PLAYER_ID;


using namespace W;
bool Handle_S_ENTER(shared_ptr<Session> _pSession, Protocol::S_ENTER& _pkt)
{
	if (_pkt.success() == false)
	{
		return false;
	}

	GClientService->Connected();
	GClientService->SetPlayerID(_pkt.player_id());
	PLAYER_ID = _pkt.player_id();

	UINT64 iPlayerEquips = _pkt.player_equip_ids();
	W::EventManager::AddPlayer(PLAYER_ID, iPlayerEquips);

	return true;
}

bool Handle_S_NEW_ENTER(shared_ptr<Session> _pSession, Protocol::S_NEW_ENTER& _pkt)
{
	//GClientService->SetPlayerID(_pkt.playerid());
	//W::EventManager::AddOtherPlayer(_pkt.playerid());

	return true;
}

bool Handle_S_EQUIP(shared_ptr<Session> _pSession, Protocol::S_EQUIP& _pkt)
{
	UINT iPlayerInfo = _pkt.scene_layer_playerid_equipid();
	UINT iItemID = _pkt.item_id();

	EventManager::ChanagePlayerEquip(iPlayerInfo, iItemID);

	return true;
}

bool Handle_S_ITEM(shared_ptr<Session> _pSession, Protocol::S_ITEM& _pkt)
{
	UINT iFuncInfo = _pkt.scene_playerid_funcid();
	UINT iItemValue = _pkt.item_value();

	EventManager::UsingItem(iFuncInfo, iItemValue);
	return true;
}

bool Handle_S_MAP(shared_ptr<Session> _pSession, Protocol::S_MAP& _pkt)
{
	int iObjSize = _pkt.objinfo_size();
	for (int i = 0; i < iObjSize; ++i)
	{
		const Protocol::ObjectInfo& objInfo = _pkt.objinfo(i);
		const Protocol::TransformInfo& trInfo = _pkt.objinfo(i).transform();

		UINT iSceneLayerCreateIdId = objInfo.scene_layer_createid_id();
		
		tTransformInfo tTrInfo = {};
		tTrInfo.vPosition = Vector3(trInfo.p_x(), trInfo.p_y(), trInfo.p_z());
		tTrInfo.vRotation = Vector3(trInfo.r_x(), trInfo.r_y(), trInfo.r_z());

		W::EventManager::CreateObjectID(iSceneLayerCreateIdId, tTrInfo,
			StringToWString(objInfo.object_name()));
	}

	//맵 데이터 수신 완료
	SceneManger::CompletedMapData();

	return true;
}

bool Handle_S_CREATE(shared_ptr<Session> _pSession, Protocol::S_CREATE& _pkt)
{
	const Protocol::ObjectInfo& tInfo = _pkt.object_info();

	const Protocol::TransformInfo& trInfo = _pkt.object_info().transform();

	//애님에션 상태 추가
	int iState = tInfo.state_value();
	UINT iSceneLayerCreateIdId = tInfo.scene_layer_createid_id();

	UCHAR cLayer = (iSceneLayerCreateIdId >> 16) & 0xFF;

	tTransformInfo tTrInfo = {};
	tTrInfo.vPosition = Vector3(trInfo.p_x(), trInfo.p_y(), trInfo.p_z());
	tTrInfo.vRotation = Vector3(trInfo.r_x(), trInfo.r_y(), trInfo.r_z());

	W::EventManager::CreateObjectID(iSceneLayerCreateIdId, tTrInfo,
		StringToWString(tInfo.object_name()));

	return true;
}

bool Handle_S_PLAYER_CREATE(shared_ptr<Session> _pSession, Protocol::S_PLAYER_CREATE& _pkt)
{
	int iPlayerSize = _pkt.player_info_size();
	for (int i = 0; i < iPlayerSize; ++i)
	{
		const Protocol::PlayerInfo& plyerInfo = _pkt.player_info(i);
		const Protocol::TransformInfo& trInfo = _pkt.player_info(i).transform();

		UINT iSceneLayerCreateIdId = plyerInfo.scene_layer_createid_id();
		UINT iPlayerState = plyerInfo.state_value();
		
		const wstring& strStateName = StringToWString(plyerInfo.state());
		tTransformInfo tTrInfo = {};
		tTrInfo.vPosition = Vector3(trInfo.p_x(), trInfo.p_y(), trInfo.p_z());
		tTrInfo.vRotation = Vector3(trInfo.r_x(), trInfo.r_y(), trInfo.r_z());

		W::EventManager::AddOtherPlayer(iSceneLayerCreateIdId, iPlayerState, plyerInfo.player_equip_ids(),
			tTrInfo, strStateName);
	}
	return true;
}

bool Handle_S_DELETE(shared_ptr<Session> _pSession, Protocol::S_DELETE& _pkt)
{
	UINT iSceneLayerDeleteId = _pkt.scene_layer_deleteid();
	UCHAR CSceneID = (iSceneLayerDeleteId >> 24) & 0xFF;;
	UCHAR cLayer = (iSceneLayerDeleteId >> 16) & 0xFF;
	USHORT CID = iSceneLayerDeleteId & 0xFFFF;;

	eLayerType eLayerType = (W::eLayerType)cLayer;
	
	EventManager::DeleteObjectID(CID, eLayerType, CSceneID);
	
	return true;
}

bool Handle_S_STATE(shared_ptr<Session> _pSession, Protocol::S_STATE& _pkt)
{
	int iState = _pkt.state_value();
	
	std::wstring strAnimaState = StringToWString(_pkt.state());

	EventManager::UpdateState(_pkt.layer_id(), iState, strAnimaState);

	return true;
}

bool Handle_S_TRANSFORM(shared_ptr<Session> _pSession, Protocol::S_TRANSFORM& _pkt)
{
	const Protocol::TransformInfo& trInfo = _pkt.transform();
	
	UINT iLayerID = _pkt.scene_layer_id();
	W::eLayerType eLayer = (W::eLayerType)((iLayerID >> 24) & 0xFF);
	UINT ID = (iLayerID) & 0xFF;

	tTransformInfo tTrInfo = {};
	tTrInfo.vPosition = Vector3(trInfo.p_x(), trInfo.p_y(), trInfo.p_z());
	tTrInfo.vRotation = Vector3(trInfo.r_x(), trInfo.r_y(), trInfo.r_z());

	EventManager::UpdateTransform(ID, eLayer, tTrInfo);
	return true;
}

bool Handle_S_SKILL(shared_ptr<Session> _pSession, Protocol::S_Skill& _pkt)
{

	return false;
}

bool Handle_S_START_MAP(shared_ptr<Session> _pSession, Protocol::S_START_MAP& _pkt)
{

	return true;
}
bool Handle_S_EXIT(shared_ptr<Session> _pSession, Protocol::S_EXIT& _pkt)
{

	return false;
}

//여기까지 왔다는건 현제 같은 씬 (만약 간발의 차이로 다른맵으로 갔다면 무시)
bool Handle_S_NEW_EXIT(shared_ptr<Session> _pSession, Protocol::S_NEW_EXIT& _pkt)
{
	UINT iPlayerID = _pkt.playerid();
	EventManager::DeletePlayer(iPlayerID);
	return true;
}
