#if !defined(AFX_SINUMERIKOPERATESOCKET_H__4A52E9C9_1D4F_46B1_AD49_61EDBA25A899__INCLUDED_)
#define AFX_SINUMERIKOPERATESOCKET_H__4A52E9C9_1D4F_46B1_AD49_61EDBA25A899__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include <afxsock.h>
/*#include<LIST.H>*/
#include <afxtempl.h>
#include "SinumerikOperateData.h"
// SinumerikOperateSocket.h : header file
//



/////////////////////////////////////////////////////////////////////////////
// CSinumerikOperateSocket command target


class CSinumerikOperateSocket : public CAsyncSocket
{

public:
	CSinumerikOperateSocket();
	virtual ~CSinumerikOperateSocket();


// Overrides
public:
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSinumerikOperateSocket)
	public:
	virtual void OnReceive(int nErrorCode);
	virtual void OnClose(int nErrorCode);
	virtual void OnConnect(int nErrorCode);
	//}}AFX_VIRTUAL

	// Generated message map functions
	//{{AFX_MSG(CSinumerikOperateSocket)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG

// Implementation
public:
	BOOL ConnectServer(const CString& sServerIP, const int nPort);	
	void Disconnect();
	BOOL m_bConnected;
protected:
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SINUMERIKOPERATESOCKET_H__4A52E9C9_1D4F_46B1_AD49_61EDBA25A899__INCLUDED_)
