// SinumerikDriverSer.cpp : 实现文件
//

#include "stdafx.h"
#include "SinumerikDriver.h"
#include "SinumerikDriverSer.h"
#include "DebugInfor.h"


// CSinumerikDriverSer
IMPLEMENT_DYNCREATE(CSinumerikDriverSer, CCmdTarget)

CSinumerikDriverSer::CSinumerikDriverSer()
{
	EnableAutomation();
	
	// 为了使应用程序在 OLE 自动化对象处于活动状态时保持
	//	运行，构造函数调用 AfxOleLockApp。
	m_pThread = NULL;
	AfxOleLockApp();
}

CSinumerikDriverSer::~CSinumerikDriverSer()
{
	// 为了在用 OLE 自动化创建所有对象后终止应用程序，
	//	析构函数调用 AfxOleUnlockApp。
	delete m_pThread;
	m_pThread = NULL;
	AfxOleUnlockApp();
}


void CSinumerikDriverSer::OnFinalRelease()
{
	// 释放了对自动化对象的最后一个引用后，将调用
	// OnFinalRelease。  基类将自动
	// 删除该对象。  在调用该基类之前，请添加您的
	// 对象所需的附加清理代码。

	CCmdTarget::OnFinalRelease();
}

BEGIN_MESSAGE_MAP(CSinumerikDriverSer, CCmdTarget)
END_MESSAGE_MAP()


BEGIN_DISPATCH_MAP(CSinumerikDriverSer, CCmdTarget)
END_DISPATCH_MAP()

// 注意: 我们添加 IID_ISinumerikDriverSer 支持
//  以支持来自 VBA 的类型安全绑定。  此 IID 必须同附加到 .IDL 文件中的
//  调度接口的 GUID 匹配。

// {8E729AA6-9E85-45E2-BC41-76FAE56EC135}
static const IID IID_ISinumerikDriverSer =
{ 0x8E729AA6, 0x9E85, 0x45E2, { 0xBC, 0x41, 0x76, 0xFA, 0xE5, 0x6E, 0xC1, 0x35 } };

BEGIN_INTERFACE_MAP(CSinumerikDriverSer, CCmdTarget)
	INTERFACE_PART(CSinumerikDriverSer, IID_ISinumerikDriverSer, Dispatch)
	INTERFACE_PART(CSinumerikDriverSer, IID_NetMach1, NetMach1) // Add-wl-2016818
END_INTERFACE_MAP()

// {4CB51EDE-4B17-4ED2-9CD7-D62F02FB9E32}
IMPLEMENT_OLECREATE_FLAGS(CSinumerikDriverSer, "SinumerikDriver.SinumerikDriverSer", afxRegApartmentThreading, 0x4cb51ede, 0x4b17, 0x4ed2, 0x9c, 0xd7, 0xd6, 0x2f, 0x2, 0xfb, 0x9e, 0x32)


// CSinumerikDriverSer 消息处理程序
STDMETHODIMP_(ULONG) CSinumerikDriverSer::XNetMach1::AddRef(void)
{
	METHOD_PROLOGUE(CSinumerikDriverSer, NetMach1);
	return pThis->ExternalAddRef();
}
//
STDMETHODIMP_(ULONG) CSinumerikDriverSer::XNetMach1::Release(void)
{
	METHOD_PROLOGUE(CSinumerikDriverSer, NetMach1);
	return pThis->ExternalRelease();
}
//Query the com interface, not to deal 
STDMETHODIMP CSinumerikDriverSer::XNetMach1::QueryInterface(REFIID iid, void FAR* FAR* ppvObj)
{
	METHOD_PROLOGUE(CSinumerikDriverSer, NetMach1);
	return pThis->ExternalQueryInterface(&iid, ppvObj);
}

BOOL CSinumerikDriverSer::StartMonitor(const CHAR* szMachIP, int nPort)
{
	if (!m_pThread)
	{
		m_pThread = (CSinumerikThread*)AfxBeginThread(RUNTIME_CLASS(CSinumerikThread),
			THREAD_PRIORITY_NORMAL, 0, CREATE_SUSPENDED);
		CDebugInfor::ShowDebugInfor(Driver, _T("启动采集线程"));
		if (m_pThread)
		{
			m_pThread->ResumeThread();
			m_pThread->m_IP = szMachIP;
			m_pThread->m_nPort = nPort;
			m_pThread->ConnectServer();
			return TRUE;
		}
		else
		{
		}
		return FALSE;
	}
	return TRUE;
}

BOOL CSinumerikDriverSer::StopMonitor()
{
	CDebugInfor::ShowDebugInfor(Driver, _T("关闭采集线程"));
	if (m_pThread)
	{
		//m_pThread->SetStopFlag(TRUE);
		m_pThread->DisConnect();
		Sleep(100);
		{
			m_pThread->SetThreadPriority(THREAD_PRIORITY_HIGHEST);
			m_pThread->PostThreadMessage(WM_QUIT, NULL, NULL);
			CDebugInfor::ShowDebugInfor(Driver, _T("关闭采集线程成功"));
		}
		try
		{
			//WaitWithMessageLoop(m_pThread->m_hThread, 5000);
			WaitForSingleObject(m_pThread->m_hThread, 5000);
		}
		catch (...)
		{
		}
		m_pThread = NULL;
	}
	return FALSE;
}

STDMETHODIMP_(BOOL) CSinumerikDriverSer::XNetMach1::Start(const CHAR* szMachIP, int nPort)
{
	METHOD_PROLOGUE(CSinumerikDriverSer, NetMach1);
	CDebugInfor::ShowDebugInfor(Driver, _T("驱动开始运行"));
	pThis->StartMonitor(szMachIP, nPort);
	return TRUE;
}

STDMETHODIMP_(BOOL) CSinumerikDriverSer::XNetMach1::Stop()
{
	METHOD_PROLOGUE(CSinumerikDriverSer, NetMach1);
	CDebugInfor::ShowDebugInfor(Driver, _T("驱动运行结束"));
	pThis->StopMonitor();
	return FALSE;
}

