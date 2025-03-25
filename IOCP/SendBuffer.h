#pragma once

class SendBufferChunk;

class SendBuffer : public enable_shared_from_this<SendBuffer>
{
public:
	SendBuffer(shared_ptr<SendBufferChunk> _pOwner, BYTE* _buffer, size_t _BufferSize);
	~SendBuffer();

	int GetBufferSize() { return m_iBufferSize; }
	int GetWritePos() { return m_iWritePos; }
	BYTE* GetData() { return m_sendBuffer; }
	void Close(int _iLen);

private:
	int m_iBufferSize;
	int m_iWritePos;
	BYTE* m_sendBuffer;

	//내 버퍼는 sendbufferchunk에서 뜯어서 가져왔기 때무에 sendbufferchunk가 갑자기 사라지면 안됨 때문에 shared로 사라지지 못하게 참조
	shared_ptr<SendBufferChunk> m_pOwner;
};




