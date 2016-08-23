
#pragma once
#include "INetMach.h"
#include "SinumerikThread.h"


// CSinumerikDriverSer ÃüÁîÄ¿±ê

class CSinumerikDriverSer : public CCmdTarget
{
	DECLARE_DYNCREATE(CSinumerikDriverSer)

public:
	CSinumerikDriverSer();
	virtual ~CSinumerikDriverSer();

	virtual void OnFinalRelease();
	CSinumerikThread* m_pThread;
protected:
	DECLARE_MESSAGE_MAP()
	DECLARE_OLECREATE(CSinumerikDriverSer)
	DECLARE_DISPATCH_MAP()
	DECLARE_INTERFACE_MAP()

	BEGIN_INTERFACE_PART(NetMach1, INetMach)
	STDMETHOD_(BOOL, Start)(const CHAR* szMachIP, int nPort);
	STDMETHOD_(BOOL, Stop)();
	END_INTERFACE_PART(NetMach1)

public:
	
	BOOL StartMonitor(const CHAR* szMachIP, int nPort);
	BOOL StopMonitor();
};


