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
	GClientService->SetPlayerID(_pkt.playerid());
	PLAYER_ID = _pkt.playerid();
	
	vector<UINT> vecPlayerID;
	vector<UINT> vecObjectID;	
	int iUserSize = _pkt.player_ids_size();
	for (int i = 0; i < iUserSize; ++i)
	{
		vecPlayerID.push_back(_pkt.player_ids(i));
		vecObjectID.push_back(_pkt.object_ids(i));
	}
	
	W::EventManager::AddPlayer(_pkt.playerid(), _pkt.create_id(), vecPlayerID, vecObjectID);

	return true;
}

bool Handle_S_NEW_ENTER(shared_ptr<Session> _pSession, Protocol::S_NEW_ENTER& _pkt)
{
	GClientService->SetPlayerID(_pkt.playerid());
	W::EventManager::AddOtherPlayer(_pkt.playerid(),_pkt.create_id());

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
		
		GameObject* pObj =  GameObjectManager::GetMonsterOfID(objInfo.create_id());
	
		eLayerType eLayerType = (W::eLayerType)objInfo.layer();
		pObj->SetObjectID(objInfo.id());
		W::EventManager::CreateObject(pObj, eLayerType);	
	}

	return true;
}

bool Handle_S_CREATE(shared_ptr<Session> _pSession, Protocol::S_CREATE& _pkt)
{
	GameObject* pObj = GameObjectManager::GetMonsterOfID(_pkt.create_id());

	eLayerType eLayerType = (W::eLayerType)_pkt.layer();
	pObj->SetObjectID(_pkt.id());

	EventManager::CreateObject(pObj, eLayerType);

	return true;
}

bool Handle_S_DELETE(shared_ptr<Session> _pSession, Protocol::S_DELETE& _pkt)
{
	eLayerType eLayerType = (W::eLayerType)_pkt.layer();
	
	EventManager::DeleteObject(_pkt.delete_id(), eLayerType);
	
	return true;
}

bool Handle_S_STATE(shared_ptr<Session> _pSession, Protocol::S_STATE& _pkt)
{
	//애니메이션 인덱스가 -1이면
	if (_pkt.anim_idx() < 0)
		return false;

	std::wstring strAnimaState = StringToWString(_pkt.state());
	
	eLayerType eLayerType = (W::eLayerType)_pkt.layer();
	UINT ID = _pkt.id();

	EventManager::UpdateState(ID, eLayerType, strAnimaState);

	return true;
}

bool Handle_S_TRANSFORM(shared_ptr<Session> _pSession, Protocol::S_TRANSFORM& _pkt)
{
	Vector3 vPosition = Vector3{ _pkt.x(),_pkt.y(),_pkt.z() };
	eLayerType eLayerType = (W::eLayerType)_pkt.layer();
	UINT ID = _pkt.id();

	EventManager::UpdateTransform(ID, eLayerType, vPosition);
	return true;
}

bool Handle_S_EXIT(shared_ptr<Session> _pSession, Protocol::S_EXIT& _pkt)
{

	return false;
}
