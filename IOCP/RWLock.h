#pragma once
//[0~ 15 write, 16~31 read]

class RWLock
{
	enum : int
	{
		ACQUIRE_TIMEOUT_TICK = 10000,
		MAX_SPINE_COUNT = 5000,
		WRITE_THREAD_MASK = 0xFFFF'0000,
		READ_COUNT_MASK = 0x0000'FFFF,
		EMPTY_FLAG = 0x0000'0000
	};


public:
	RWLock();
	~RWLock();

	void WriteLock();
	void UnWriteLock();

	void ReadLock();
	void UnReadLock();


private:
	std::atomic<int> m_lockFlag;
	int m_iWriteCount; 

};

class WLock
{
public:
	WLock(RWLock& _pLock);
	~WLock();

private:
	RWLock& m_RWLock;
};

class RLock
{
public:
	RLock(RWLock& _pLock);
	~RLock();

private:
	RWLock& m_RWLock;
};

