#pragma once
class BufferWriter
{
public:
	BufferWriter(BYTE* _buffer, int _iBufferSize);
	~BufferWriter();

	int FreeSize() { return m_iBufferSize - m_iWritePos; }
	int GetWritePos() { return m_iWritePos; }
	BYTE* GetBuffer() { return m_writeBuffer; }

	template<typename T>
	bool Write(T* _src) {Write(_src, sizeof(T));}
	bool Write(void* _src, int _iLen);

	template <typename T>
	BufferWriter& operator<<(T&& _src);

	template <typename T>
	T* Reserve(int _iCount);
private:
	BYTE* m_writeBuffer;

	int m_iBufferSize;
	int m_iWritePos;
};

template<typename T>
inline BufferWriter& BufferWriter::operator<<(T&& _src)
{
	using DataType = std::remove_reference_t<T>;

	*reinterpret_cast<DataType*>(&m_writeBuffer[m_iWritePos]) = std::forward<DataType>(_src);
	m_iWritePos += sizeof(T);

	return *this;
}

template<typename T>
inline T* BufferWriter::Reserve(int _iCount)
{
	if (FreeSize() < sizeof(T) * _iCount)
		return nullptr;

	T* Data = reinterpret_cast<T*>(&m_writeBuffer[m_iWritePos]);
	m_iWritePos += sizeof(T) * _iCount;

	return Data;
}
