#pragma once
#include "Session.h"


class PacketSession : public Session
{
public:
	PacketSession();
	virtual ~PacketSession();

	shared_ptr<PacketSession> GetPacketSessionRef() { return static_pointer_cast<PacketSession>(shared_from_this()); }

protected:
	virtual int OnRecv(BYTE* _buffer, int _iLen) sealed;
	virtual int OnRecvPacket(BYTE* _buffer, int _iLen) = 0;


};


#pragma pack(1)
struct PacketHeader
{
	UINT16 size;
	UINT16 id;
};

//가변 인자 시작
struct VariableData
{
	UINT16 offsetPos;
	UINT16 charCount;
};

struct PacketTest
{
	PacketHeader header;

	//가변 데이터 시작 위치 
	VariableData variableData;

	//WCHAR strMessage;

	bool IsVaild()
	{
		int iSize = 0;
		iSize += sizeof(PacketTest);
		iSize += variableData.charCount * sizeof(WCHAR);
		if (iSize != header.size)
			return false;

		if (variableData.offsetPos + variableData.charCount * sizeof(WCHAR) != header.size)
			return false;

		return true;
	}
};
#pragma pack()