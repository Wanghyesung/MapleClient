#pragma once
#include <array>
//처음에 버퍼를 할당하고 삭제하는 개념이 아니라 
//사용 후 다시 재사용할 목적으로

/*//////////////////////////////
		SendBufferChunk
*//////////////////////////////
class SendBuffer;

enum
{
	MAX_SENDBUFFER_SIZE = 6000
};

class SendBufferChunk : public enable_shared_from_this<SendBufferChunk>
{
public:
	SendBufferChunk();
	~SendBufferChunk();


	shared_ptr<SendBuffer> Open(size_t _size);
	void Close(int _iUsedSize);
	void Reset();
	bool IsOpen() { return m_bOpen; }

	BYTE* GetBuffer() { return &m_vecSendBuffer[m_iUsedPos]; }
	int FreeSize() { return  static_cast<int>(m_vecSendBuffer.size()) - m_iUsedPos; }

private:
	vector<BYTE> m_vecSendBuffer;
	//array<BYTE, MAX_SENDBUFFER_SIZE> m_buffer = {};
	
	bool m_bOpen;
	int m_iUsedPos;
};


/*//////////////////////////////
		SendBufferManager
*//////////////////////////////

class SendBufferManager
{
public:
	SendBufferManager();
	~SendBufferManager();

	shared_ptr<SendBuffer> Open(size_t _size);

private:
	shared_ptr<SendBufferChunk> Pop();
	void Push(shared_ptr<SendBufferChunk> _pSendBufferChunk);

	static void PushGlobal(SendBufferChunk* _pSendBufferChunk);
	
private:
	vector<shared_ptr<SendBufferChunk>> m_vecSendBufferChunk;

	RWLock m_Lock;

	static atomic<bool> m_bShutDown;
};

