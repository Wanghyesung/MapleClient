#pragma once
class RecvBuffer
{
public:
	RecvBuffer(int _iBufferSize);
	~RecvBuffer();

	BYTE* GetReadPos() { return &m_vecRecvBuffer[m_iReadPos]; }
	BYTE* GetWritePos() { return &m_vecRecvBuffer[m_iWritePos]; }
	int DataSize() { return m_iWritePos - m_iReadPos; }
	int FreeSize() { return m_iCapacity - m_iWritePos; }


	bool Read(int _iNumOfBytes);
	bool Write(int _iNumOfBytes);

	bool Clear();

private:
	vector<BYTE> m_vecRecvBuffer;


	int m_iCapacity;//용량
	int m_iBufferSize;//전체 사이즈
	int m_iReadPos;//현제 읽어야할 위치
	int m_iWritePos;//지금까지 쓴 위치

};

