#include "pch.h"
#include "ServerPacketHandler.h"

#include "WEventManager.h"
#include "NetFunc.h"
#include "WGameObjectManager.h"
#include "..\Engine_Source\WGameObject.h"
#include "..\Engine_Source\WTransform.h"
#include "..\Engine_Source\WSceneManger.h"
shared_ptr< ClientService> GClientService;
PacketHandlerFunc GPacketHandler[UINT16_MAX];
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
	
	vector<UINT> vecPlayerID;
	vector<UINT> vecObjectID;	
	int iUserSize = _pkt.player_ids_size();
	for (int i = 0; i < iUserSize; ++i)
	{
		vecPlayerID.push_back(_pkt.player_ids(i));
	}
	
	W::EventManager::AddPlayer(PLAYER_ID, vecPlayerID);

	return true;
}

bool Handle_S_NEW_ENTER(shared_ptr<Session> _pSession, Protocol::S_NEW_ENTER& _pkt)
{
	GClientService->SetPlayerID(_pkt.playerid());
	W::EventManager::AddOtherPlayer(_pkt.playerid());

	return true;
}

bool Handle_S_EQUIP(shared_ptr<Session> _pSession, Protocol::S_EQUIP& _pkt)
{
	return false;
}

bool Handle_S_MAP(shared_ptr<Session> _pSession, Protocol::S_MAP& _pkt)
{
	int iObjSize = _pkt.objinfo_size();
	for (int i = 0; i < iObjSize; ++i)
	{
		const Protocol::ObjectInfo& objInfo = _pkt.objinfo(i);
		
		UINT iLayerCreateIdId = objInfo.layer_createid_id();
		UCHAR cLayer = (iLayerCreateIdId >> 24) & 0xFF;
		UCHAR cCreateid = (iLayerCreateIdId >> 16) & 0xFF;
		USHORT CID = iLayerCreateIdId & 0xFFFF;

		GameObject* pObj =  GameObjectManager::GetMonsterOfID(cCreateid);
	
		eLayerType eLayerType = (W::eLayerType)cLayer;
		pObj->SetObjectID(CID);
		W::EventManager::CreateObject(pObj, eLayerType);	
	}

	return true;
}

bool Handle_S_CREATE(shared_ptr<Session> _pSession, Protocol::S_CREATE& _pkt)
{
	UINT iLayerCreateIdId = _pkt.layer_createid_id();
	UCHAR cLayer = (iLayerCreateIdId >> 24) & 0xFF;
	UCHAR cCreateid = (iLayerCreateIdId >> 16) & 0xFF;
	USHORT CID = iLayerCreateIdId & 0xFFFF;

	GameObject* pObj = GameObjectManager::GetMonsterOfID(cCreateid);

	eLayerType eLayerType = (W::eLayerType)cLayer;
	pObj->SetObjectID(CID);

	EventManager::CreateObject(pObj, eLayerType);

	return true;
}

bool Handle_S_DELETE(shared_ptr<Session> _pSession, Protocol::S_DELETE& _pkt)
{
	UINT iLayerDeleteId = _pkt.layer_deleteid();
	UCHAR cLayer = (iLayerDeleteId >> 24) & 0xFF;
	USHORT CID = iLayerDeleteId & 0xFFFF;

	eLayerType eLayerType = (W::eLayerType)cLayer;
	
	EventManager::DeleteObject(CID, eLayerType);
	
	return true;
}

bool Handle_S_STATE(shared_ptr<Session> _pSession, Protocol::S_STATE& _pkt)
{
	int iAnim = _pkt.anim();
	UCHAR cAnimIdx = iAnim & 0xFF;      

	//애니메이션 인덱스가 -1이면
	if (cAnimIdx < 0)
		return false;

	std::wstring strAnimaState = StringToWString(_pkt.state());

	if (iAnim >= 257)
		int a = 10;
	EventManager::UpdateState(_pkt.layer_id(), iAnim, strAnimaState);

	return true;
}

bool Handle_S_TRANSFORM(shared_ptr<Session> _pSession, Protocol::S_TRANSFORM& _pkt)
{
	Vector3 vPosition = Vector3{ _pkt.x(),_pkt.y(),_pkt.z() };

	UINT iLayerID = _pkt.layer_id();
	W::eLayerType eLayer = (W::eLayerType)((iLayerID >> 24) & 0xFF);
	UINT ID = (iLayerID) & 0xFF;

	EventManager::UpdateTransform(ID, eLayer, vPosition);
	return true;
}

bool Handle_S_EXIT(shared_ptr<Session> _pSession, Protocol::S_EXIT& _pkt)
{

	return false;
}
