// SinumerikThread.cpp : 实现文件
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
	// TODO:    在此执行任意逐线程初始化
	//ConnectServer();
	return TRUE;
}

int CSinumerikThread::ExitInstance()
{
	// TODO:    在此执行任意逐线程清理
	return CWinThread::ExitInstance();
}

BEGIN_MESSAGE_MAP(CSinumerikThread, CWinThread)
END_MESSAGE_MAP()


// CSinumerikThread 消息处理程序
BOOL CSinumerikThread::ConnectServer()
{
	BOOL ret = FALSE;
	CString sInfor = _T("连接");
	sInfor = /*m_IP +*/ _T("连接");
	CDebugInfor::ShowDebugInfor(Driver, sInfor.GetBuffer(0));
	ret = m_SinumerikSocket.ConnectServer(m_IP, m_nPort);
	if (ret == TRUE)
	{
		sInfor.Empty();
		sInfor = /*m_IP +*/ "连接成功";
		CDebugInfor::ShowDebugInfor(Driver, sInfor.GetBuffer(0));
		return TRUE;
	}
	sInfor.Empty();
	sInfor = /*m_IP + */"连接失败";
	CDebugInfor::ShowDebugInfor(Driver, sInfor.GetBuffer(0));
	return FALSE;
}

BOOL CSinumerikThread::DisConnect()
{
	CDebugInfor::ShowDebugInfor(Driver, _T("关闭SOCKET"));
	m_SinumerikSocket.Disconnect();
	return FALSE;
}

void CSinumerikThread::SetStopFlag(BOOL bStopFlag)
{
	m_StopFlag = bStopFlag;
}

BOOL CSinumerikThread::PreTranslateMessage(MSG* pMsg)
{
	// TODO:  在此添加专用代码和/或调用基类
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
