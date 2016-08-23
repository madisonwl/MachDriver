// SinumerikThread.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "SinumerikThread.h"
#include "DebugInfor.h"


// CSinumerikThread

IMPLEMENT_DYNCREATE(CSinumerikThread, CWinThread)

CSinumerikThread::CSinumerikThread()
{
	m_nPort = 8888;
	m_StopFlag = FALSE;
}

CSinumerikThread::~CSinumerikThread()
{
	m_StopFlag = FALSE;
}

BOOL CSinumerikThread::InitInstance()
{
	// TODO:    �ڴ�ִ���������̳߳�ʼ��
	//ConnectServer();
	return TRUE;
}

int CSinumerikThread::ExitInstance()
{
	// TODO:    �ڴ�ִ���������߳�����
	return CWinThread::ExitInstance();
}

BEGIN_MESSAGE_MAP(CSinumerikThread, CWinThread)
END_MESSAGE_MAP()


// CSinumerikThread ��Ϣ�������
BOOL CSinumerikThread::ConnectServer()
{
	BOOL ret = FALSE;
	CString sInfor = _T("����");
	sInfor = /*m_IP +*/ _T("����");
	CDebugInfor::ShowDebugInfor(Driver, sInfor.GetBuffer(0));
	ret = m_SinumerikSocket.ConnectServer(m_IP, m_nPort);
	if (ret == TRUE)
	{
		sInfor.Empty();
		sInfor = /*m_IP +*/ "���ӳɹ�";
		CDebugInfor::ShowDebugInfor(Driver, sInfor.GetBuffer(0));
		return TRUE;
	}
	sInfor.Empty();
	sInfor = /*m_IP + */"����ʧ��";
	CDebugInfor::ShowDebugInfor(Driver, sInfor.GetBuffer(0));
	return FALSE;
}

BOOL CSinumerikThread::DisConnect()
{
	CDebugInfor::ShowDebugInfor(Driver, _T("�ر�SOCKET"));
	m_SinumerikSocket.Disconnect();
	return FALSE;
}

void CSinumerikThread::SetStopFlag(BOOL bStopFlag)
{
	m_StopFlag = bStopFlag;
}

BOOL CSinumerikThread::PreTranslateMessage(MSG* pMsg)
{
	// TODO:  �ڴ����ר�ô����/����û���
	if ((pMsg->message == WM_SINUMTHREADMSG1) && (!m_StopFlag))
	{
		switch (pMsg->wParam)
		{
		case 0:
			PostThreadMessage(WM_QUIT, 0, 0);
			break;
		default:
			break;
		}
	}
	return CWinThread::PreTranslateMessage(pMsg);
}
