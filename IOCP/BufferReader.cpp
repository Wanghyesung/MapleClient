#include "pch.h"
#include "BufferReader.h"

BufferReader::BufferReader(BYTE* _buffer, int _iBufferSize):
	m_iBufferSize(_iBufferSize),
	m_readBuffer(_buffer),
	m_iReadPos(0)
{

}

BufferReader::~BufferReader()
{

}

bool BufferReader::Read(void* _dst, int _iLen)
{
	if (FreeSize() < _iLen)
		return false;

	memcpy( _dst,&m_readBuffer[m_iReadPos], _iLen);
	m_iReadPos += _iLen;

	return true;
}
