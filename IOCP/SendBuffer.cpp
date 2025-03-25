#include "pch.h"
#include "SendBuffer.h"
#include "SendBufferChunk.h"

SendBuffer::SendBuffer(shared_ptr< SendBufferChunk> _pOwner, BYTE* _buffer,size_t _BufferSize):
	m_iBufferSize(_BufferSize),
	m_iWritePos(0),
	m_sendBuffer(_buffer),
	m_pOwner(_pOwner)
{

}

SendBuffer::~SendBuffer()
{

}

void SendBuffer::Close(int _iLen)
{
	assert(_iLen <= m_iBufferSize);
	m_iWritePos = _iLen;
	m_pOwner->Close(_iLen);
}
