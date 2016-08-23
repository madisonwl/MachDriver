// SinumerikDriverSer.cpp : ʵ���ļ�
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
	
	// Ϊ��ʹӦ�ó����� OLE �Զ��������ڻ״̬ʱ����
	//	���У����캯������ AfxOleLockApp��
	m_pThread = NULL;
	AfxOleLockApp();
}

CSinumerikDriverSer::~CSinumerikDriverSer()
{
	// Ϊ������ OLE �Զ����������ж������ֹӦ�ó���
	//	������������ AfxOleUnlockApp��
	delete m_pThread;
	m_pThread = NULL;
	AfxOleUnlockApp();
}


void CSinumerikDriverSer::OnFinalRelease()
{
	// �ͷ��˶��Զ�����������һ�����ú󣬽�����
	// OnFinalRelease��  ���ཫ�Զ�
	// ɾ���ö���  �ڵ��øû���֮ǰ�����������
	// ��������ĸ���������롣

	CCmdTarget::OnFinalRelease();
}

BEGIN_MESSAGE_MAP(CSinumerikDriverSer, CCmdTarget)
END_MESSAGE_MAP()


BEGIN_DISPATCH_MAP(CSinumerikDriverSer, CCmdTarget)
END_DISPATCH_MAP()

// ע��: ������� IID_ISinumerikDriverSer ֧��
//  ��֧������ VBA �����Ͱ�ȫ�󶨡�  �� IID ����ͬ���ӵ� .IDL �ļ��е�
//  ���Ƚӿڵ� GUID ƥ�䡣

// {8E729AA6-9E85-45E2-BC41-76FAE56EC135}
static const IID IID_ISinumerikDriverSer =
{ 0x8E729AA6, 0x9E85, 0x45E2, { 0xBC, 0x41, 0x76, 0xFA, 0xE5, 0x6E, 0xC1, 0x35 } };

BEGIN_INTERFACE_MAP(CSinumerikDriverSer, CCmdTarget)
	INTERFACE_PART(CSinumerikDriverSer, IID_ISinumerikDriverSer, Dispatch)
	INTERFACE_PART(CSinumerikDriverSer, IID_NetMach1, NetMach1) // Add-wl-2016818
END_INTERFACE_MAP()

// {4CB51EDE-4B17-4ED2-9CD7-D62F02FB9E32}
IMPLEMENT_OLECREATE_FLAGS(CSinumerikDriverSer, "SinumerikDriver.SinumerikDriverSer", afxRegApartmentThreading, 0x4cb51ede, 0x4b17, 0x4ed2, 0x9c, 0xd7, 0xd6, 0x2f, 0x2, 0xfb, 0x9e, 0x32)


// CSinumerikDriverSer ��Ϣ�������
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
		CDebugInfor::ShowDebugInfor(Driver, _T("�����ɼ��߳�"));
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
	CDebugInfor::ShowDebugInfor(Driver, _T("�رղɼ��߳�"));
	if (m_pThread)
	{
		//m_pThread->SetStopFlag(TRUE);
		m_pThread->DisConnect();
		Sleep(100);
		{
			m_pThread->SetThreadPriority(THREAD_PRIORITY_HIGHEST);
			m_pThread->PostThreadMessage(WM_QUIT, NULL, NULL);
			CDebugInfor::ShowDebugInfor(Driver, _T("�رղɼ��̳߳ɹ�"));
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
	CDebugInfor::ShowDebugInfor(Driver, _T("������ʼ����"));
	pThis->StartMonitor(szMachIP, nPort);
	return TRUE;
}

STDMETHODIMP_(BOOL) CSinumerikDriverSer::XNetMach1::Stop()
{
	METHOD_PROLOGUE(CSinumerikDriverSer, NetMach1);
	CDebugInfor::ShowDebugInfor(Driver, _T("�������н���"));
	pThis->StopMonitor();
	return FALSE;
}

