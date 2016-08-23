#pragma once

#include "SinumerikOperateSocket.h"

// CSinumerikThread
class CSinumerikThread : public CWinThread
{
	DECLARE_DYNCREATE(CSinumerikThread)

protected:
	CSinumerikThread();           // ��̬������ʹ�õ��ܱ����Ĺ��캯��
	

public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();
	virtual ~CSinumerikThread();
public:
	CString m_IP;
	int m_nPort;
	CSinumerikOperateSocket m_SinumerikSocket;
	BOOL ConnectServer();
	BOOL DisConnect();
	void SetStopFlag(BOOL bStopFlag);

private:
	BOOL m_StopFlag;

protected:
	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
};


