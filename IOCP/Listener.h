#pragma once
#include "Session.h"
class IOCPAcceptEvent;

class ServerService;
class Listener : public Session 
{
public:
	Listener();
	virtual ~Listener();

	virtual void Clear()override;
public:
	void Start();

	virtual void DisPatch(IOCPEvent* _pEvent, int _iNumOfBytes) override;
public:
	void RegisterAccept(IOCPAcceptEvent* _pAcceptEvent) ;
	void ProcessAccept(IOCPAcceptEvent* _pAcceptEvent)  ;

private:
	vector<IOCPAcceptEvent*> m_vecEvent;
};

