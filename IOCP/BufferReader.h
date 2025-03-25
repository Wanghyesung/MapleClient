#pragma once
class BufferReader
{
public:
	BufferReader(BYTE* _buffer, int _iBufferSize);
	~BufferReader();


	int GetBufferSize() { return m_iBufferSize; }
	int GetReadPos() { return m_iBufferSize; }
	int FreeSize() { return m_iBufferSize - m_iReadPos; }
	BYTE* GetBuffer() { return &m_readBuffer[m_iReadPos]; }

	template<typename T>
	bool Read(T* _dst){Read(_dst, sizeof(T));}
	bool Read(void* _dst, int _iLen);

	template <typename T>
	BufferReader& operator>>(T& _dst);

private:
	int m_iReadPos;
	int m_iBufferSize;

	BYTE* m_readBuffer;
};


template <typename T>
inline BufferReader& BufferReader::operator>>(T& _dst)
{
	_dst = *reinterpret_cast<T*>(&m_readBuffer[m_iReadPos]);
	m_iReadPos += sizeof(T);
	return *this;
}