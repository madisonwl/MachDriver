// SinumerikOperateSocket.cpp : implementation file
//

#include "stdafx.h"
//#include "	\ add additional includes here"
#include "SinumerikOperateSocket.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CSinumerikOperateSocket

CSinumerikOperateSocket::CSinumerikOperateSocket()
{
	m_bConnected = FALSE;
}

CSinumerikOperateSocket::~CSinumerikOperateSocket()
{
}

// Do not edit the following lines, which are needed by ClassWizard.
#if 0
BEGIN_MESSAGE_MAP(CSinumerikOperateSocket, CAsyncSocket)
	//{{AFX_MSG_MAP(CSinumerikOperateSocket)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()
#endif	// 0
BOOL CSinumerikOperateSocket::ConnectServer( const CString& sServerIP, const int nPort )
{
	if (("0.0.0.0" == sServerIP) || sServerIP.IsEmpty())
	{
		return FALSE;
	}
	ShutDown();
	Close();
	try
	{
		AfxSocketInit();
		if (Create())
		{	
			if (!AsyncSelect(FD_READ | FD_WRITE | FD_CLOSE | FD_CONNECT))
			{
				ShutDown();
				Close();
				//GetSocketErrorText();			
				return FALSE;
			}	
			Connect(sServerIP, nPort);
		    //FreeList();
			m_bConnected = TRUE;
			return TRUE;
		}
	}
	catch (...)
	{
		//		Close();
	}
	return FALSE;
}


/////////////////////////////////////////////////////////////////////////////
// CSinumerikOperateSocket member functions

void CSinumerikOperateSocket::OnReceive(int nErrorCode) 
{
	// TODO: Add your specialized code here and/or call the base class
	/*try
	{
		if (0 == nErrorCode)
		{
			memset(m_pcBuffer, 0x00, SIM_BUF_SIZE);
			int nBytes = Receive(m_pcBuffer, SIM_BUF_SIZE);
			switch (nBytes)
			{
			case 0:// connection has been closed
				ShutDown();//�ͷ�Socket��Դռ������
				Close();
				m_bConnected = FALSE;
				break;
			case SOCKET_ERROR:// read error
				if(GetLastError()!=WSAEWOULDBLOCK)
				{
					m_bConnected = FALSE;
				//	TRACE("OnReceive errror: %d\n", GetLastError());
				}
				break;
			default:
				ProcessMsg(nBytes);
				break;
			}
		}
		else if (WSAENETDOWN == nErrorCode)
		{
		}
	}
	catch (...)
	{
	}*/
	CAsyncSocket::OnReceive(nErrorCode);
}

void CSinumerikOperateSocket::OnClose(int nErrorCode) 
{
	// TODO: Add your specialized code here and/or call the base class
	try
	{
		ShutDown();
		Close();
	}
	catch (...)
	{
	}
	
	m_bConnected = FALSE;
	CAsyncSocket::OnClose(nErrorCode);
}

void CSinumerikOperateSocket::OnConnect(int nErrorCode) 
{
	// TODO: Add your specialized code here and/or call the base class
	if (0 == nErrorCode)
	{
	//	m_bConnected = TRUE;
	}
	CAsyncSocket::OnConnect(nErrorCode);
}

/*
BOOL CSinumerikOperateSocket::WriteReadMsg( const UINT nVers, const UINT nCmd )
{
	if (!m_pcCmd)
	{
		return FALSE;
	}
	try
	{
	//	*(UINT *)(m_pcCmd + 8) = nCmd;

	//	int nBytes = Send(m_pcCmd, SIM_CMD_SIZE);
		char* sendData = "SINUMERIK_VARFLAG";
		int nBytes = Send(sendData, strlen(sendData));
		switch (nBytes)
		{
		case SOCKET_ERROR:
			if (WSAEWOULDBLOCK == GetLastError())
			{
			//	GetSocketErrorText();
			}
			else
			{
				return FALSE;
			}
			break;
		default:
			return TRUE;
			break;
		}
	}
	catch (...)
	{
	}
	return FALSE;
} */

//********************************************************************
//* �������ƣ�SendReadCmd
//* �������ܣ����Ͷ�ȡָ��
//* ����ֵ��BOOL :TRUE:�ɹ���FALSE��ʧ��
//* ����˵����strCmd����ȡָ��
//* �����ߣ�  wl
//* �������ڣ�2014��05��30��
//* �޸����ڣ�
//********************************************************************
/*
BOOL CSinumerikOperateSocket::SendReadCmd( const CString strCmd )
{
	if(strCmd.IsEmpty())
	{
		return FALSE;
	}
	try
	{
		int nBytes = Send(strCmd, strlen(strCmd));
		switch (nBytes)
		{
		 case SOCKET_ERROR:
			if (WSAEWOULDBLOCK == GetLastError())
			{
				GetSocketErrorText();
				m_bConnected = FALSE;
			}
			else
			{
				return FALSE;
			}
			break;
		 default:
			return TRUE;
			break;
		}
	}
	catch (...)
	{
	}

	return FALSE;
}

// ********************************************************************
// * �������ƣ�GetServVersion
// * �������ܣ���÷���˰汾��
// * ����ֵ��BOOL :TRUE:�ɹ���FALSE��ʧ��
// * ����˵������
// * �����ߣ�  wl
// * �������ڣ�2014��05��30��
// * �޸����ڣ�
// ********************************************************************
BOOL CSinumerikOperateSocket::GetServVersion()
{
	if (SendReadCmd(SINUMERIK_VSERSION))   //���Ͷ�ȡ�汾ָ��
	{
	//	TRACE("Socket-GetServVersion�ɹ�\n");
		return TRUE;
	}
	else
	{
	//	TRACE("Socket-GetServVersionʧ��\n");
		return FALSE;
	}
	return FALSE;
}

// ********************************************************************
// * �������ƣ�GetCNCVarinfor
// * �������ܣ���ñ�����ǩ�ţ�ÿ��������Ӧһ����ǩ�ţ�һһ��Ӧ��ϵ
// * ����ֵ��BOOL :TRUE:�ɹ���FALSE��ʧ��
// * ����˵������
// * �����ߣ�  wl
// * �������ڣ�2014��05��30��
// * �޸����ڣ�
// ********************************************************************

BOOL CSinumerikOperateSocket::GetCNCVarinfor()
{
	if (SendReadCmd(SINUMERIK_VARFLAG))
	{
	//	TRACE("Socket-GetCNCVarinfor�ɹ�\n");
		Sleep(8);
		return TRUE;
	}
	else
	{
	//	TRACE("Socket-GetCNCVarinforʧ��\n");
		return FALSE;
	}
	return FALSE;
}
// ********************************************************************
// * �������ƣ�GetVarTypeDefine
// * �������ܣ���ñ������Ͷ���
// * ����ֵ��BOOL :TRUE:�ɹ���FALSE��ʧ��
// * ����˵������
// * �����ߣ�  wl
// * �������ڣ�2014��05��30��
// * �޸����ڣ�
// ********************************************************************
BOOL CSinumerikOperateSocket::GetVarOffSet()
{
	if(SendReadCmd(SINUMERIK_VAROFFSET))
	{
		//TRACE("Socket-GetVarOffSet�ɹ�\n");
		Sleep(8);
		return TRUE;
	}
	else
	{
		//TRACE("Socket-GetVarOffSetʧ��\n");
		return FALSE;
	}
	return FALSE;
}
// ********************************************************************
// * �������ƣ�GetVarTypeDefine
// * �������ܣ���ñ������Ͷ���
// * ����ֵ��BOOL :TRUE:�ɹ���FALSE��ʧ��
// * ����˵������
// * �����ߣ�  wl
// * �������ڣ�2014��05��30��
// * �޸����ڣ�
// ********************************************************************

BOOL CSinumerikOperateSocket::GetVarTypeDefine()
{
	if(SendReadCmd(SINUMERIK_VARDEFINE))
	{
		//TRACE("Socket-GetVarTypeDefine�ɹ�\n");
		Sleep(8);
		return TRUE;
	}
	else
	{
		//TRACE("Socket-GetVarTypeDefineʧ��\n");
		return FALSE;
	}
	return FALSE;
}
// ********************************************************************
// * �������ƣ�GetNCData
// * �������ܣ���ñ�������
// * ����ֵ��BOOL :TRUE:�ɹ���FALSE��ʧ��
// * ����˵������
// * �����ߣ�  wl
// * �������ڣ�2014��06��04��
// * �޸����ڣ�
// ********************************************************************
BOOL CSinumerikOperateSocket::GetNCData()
{
	if(SendReadCmd(SINUMERIK_VARDATA))
	{
		//TRACE("Socket-GetNCData�ɹ�\n");
		Sleep(8);
		return TRUE;
	}
	else
	{
		//TRACE("Socket-GetNCDataʧ��\n");
		return FALSE;
	}
	return FALSE;
}
// ********************************************************************
// * �������ƣ�ProcessMsg
// * �������ܣ�OnReceive���յ�����Ϣ����
// * ����ֵ��
// * ����˵������
// * �����ߣ�  wl
// * �������ڣ�2014��06��03��
// * �޸����ڣ�
// ********************************************************************
void CSinumerikOperateSocket::ProcessMsg( const int nByte )
{
	if (nByte == SIM_HEADER_SIZE)//���յ�����ϢС��������Ϣͷ�����յ�Ϊ����˰汾��Ϣ����ʽΪversion:1.0  CString+double��ʽ
	{
	//	char* tempbuff = new char[SIM_HEADER_SIZE];
		memcpy(tempHeadbuff,m_pcBuffer,SIM_HEADER_SIZE);
		AnalyseMsgVersion(tempHeadbuff);
	}
	else if (nByte>SIM_HEADER_SIZE) //���յ�����Ϣ����������Ϣͷ��˵����Ϣͷ�����������,��ʽ:�汾��(double) + ��Ϣ����(int) + ���ݸ���(int) + ����
	{
		memcpy(tempDatabuff,m_pcBuffer,nByte);
		AnalyseMsgData(tempDatabuff);
	}
}
// ********************************************************************
// * �������ƣ�AnalyseMsgVersion
// * �������ܣ�����OnReceive���յ�����Ϣ�����õ��汾��
// * ����ֵ��  ��
// * ����˵����buff���յ����ַ���;dbver:�����õ��İ汾��
// * �����ߣ�  wl
// * �������ڣ�2014��06��03��
// * �޸����ڣ�
// ********************************************************************
void CSinumerikOperateSocket::AnalyseMsgVersion( const char* buff)
{
	char cTemp[9];
	memset(cTemp,0,9);
	memcpy(cTemp,buff,8);
	CString strTemp;
	strTemp.Format("%s",buff);
	if (strTemp==SIM_HEADER_MSG)
	{
		dbSerVersion = *(double* )(buff+8);
		m_strSerVersion.Format("%.1f",dbSerVersion);
	}
}

// ********************************************************************
// * �������ƣ�AnalyseMsgData
// * �������ܣ�����OnReceive���յ�����Ϣ�����õ�����
// * ����ֵ��  ��
// * ����˵����buff���յ����ַ���;
// * �����ߣ�  wl
// * �������ڣ�2014��06��03��
// * �޸����ڣ�
// ********************************************************************
//��ʽ:�汾��(double) + ��Ϣ����(int) + ���ݸ���(int) + ����

void CSinumerikOperateSocket::AnalyseMsgData( const char* buff)
{
	//�����õ���Ϣ����
	int nMsgType = 0;
	nMsgType = *(UINT*)(buff+8);
	switch(nMsgType)
	{
	case SINUMERIKVARFLAG:
		SaveVarFlag(buff);
		break;
	case SINUMERIKVAROFFSET:
		SaveVarOffSet(buff);
		break;
	case SINUMERIKVARDEFINE:
		SaveVarDefine(buff);
		break;
	case SINUMERIKVARDATA:
		SaveVarValue(buff);
		break;
	default:
		break;
	}
}

// ********************************************************************
// * �������ƣ�SaveVarFlag
// * �������ܣ����������������ǩ
// * ����ֵ��  ��
// * ����˵����buff���յ����ַ���;
// * �����ߣ�  wl
// * �������ڣ�2014��06��03��
// * �޸����ڣ�
// ********************************************************************

void CSinumerikOperateSocket::SaveVarFlag(const char* buff)
{
	int nVarNum = 0;
	nVarNum = *(UINT*)(buff+sizeof(double)+sizeof(int));
	char cTemp[5];
	memset(cTemp,0,5);
	CString strVarTemp;	
	for (int i=0;i<nVarNum;i++)
	{
		SimVarPara *pvarpara = new SimVarPara;
		memcpy(cTemp,buff+sizeof(double)+sizeof(int)*2+i*4,4);
		strVarTemp.Format("%s",cTemp,4);
		pvarpara->VarFlag = strVarTemp;
		SimVarParaList.AddTail(pvarpara);
	}
}

// ********************************************************************
// * �������ƣ�SaveVarOffSet
// * �������ܣ��������������ƫ��
// * ����ֵ��  ��
// * ����˵����buff���յ����ַ���;
// * �����ߣ�  wl
// * �������ڣ�2014��06��04��
// * �޸����ڣ�
// ********************************************************************
void CSinumerikOperateSocket::SaveVarOffSet(const char* buff)
{
	int nVarNum = 0;
	char cTemp[5];
	memset(cTemp,0,5);
	CString strVarTemp;

	POSITION pos = NULL;
	pos = 	SimVarParaList.GetHeadPosition();
	SimVarPara *pvarpara1 = NULL;
	nAlloffSet = 0;
	while (pos)
	{		
		pvarpara1 = SimVarParaList.GetAt(pos);	
		pvarpara1->nVarOffSet= *(UINT*)(buff+sizeof(double)+sizeof(int)*2+nVarNum*4);
		nAlloffSet += pvarpara1->nVarOffSet;
		SimVarParaList.SetAt(pos,pvarpara1);	
		SimVarParaList.GetNext(pos);
		nVarNum++;
	}
	int a= 0;
}

// ********************************************************************
// * �������ƣ�SaveVarDefine
// * �������ܣ������������������
// * ����ֵ��  ��
// * ����˵����buff���յ����ַ���;
// * �����ߣ�  wl
// * �������ڣ�2014��06��04��
// * �޸����ڣ�
// ********************************************************************
void CSinumerikOperateSocket::SaveVarDefine(const char* buff)
{
	int nVarNum = 0;
	char cTemp[3];
	memset(cTemp,0,3);
	CString strVarTemp;

	POSITION pos = NULL;
	pos = 	SimVarParaList.GetHeadPosition();
	SimVarPara *pvarpara1 = NULL;
	while (pos)
	{		
		pvarpara1 = SimVarParaList.GetAt(pos);	
		memcpy(cTemp,buff+sizeof(double)+sizeof(int)*2+nVarNum,1);
		pvarpara1->VarType.Format("%s",cTemp);
		SimVarParaList.SetAt(pos,pvarpara1);	
		SimVarParaList.GetNext(pos);
		nVarNum++;
	}
}

// ********************************************************************
// * �������ƣ�SaveVarValue
// * �������ܣ��������������ֵ
// * ����ֵ��  ��
// * ����˵����buff���յ����ַ���;
// * �����ߣ�  wl
// * �������ڣ�2014��06��04��
// * �޸����ڣ�
// ********************************************************************
void CSinumerikOperateSocket::SaveVarValue( const char* buff )
{
/ *
	int nVarNum = 0;
	char cTemp[3];
	memset(cTemp,0,3);
	CString strVarTemp;* /
	m_bGetValue = GetAllVarValue(SimVarParaList,buff);
}
BOOL CSinumerikOperateSocket::GetAllVarValue(const CTypedPtrList<CPtrList,SimVarPara*> &SimVarParaList, const char* buff)
{
	int nVarNum = 0;
	POSITION pos = NULL;
	pos = 	SimVarParaList.GetHeadPosition();
	if (pos==NULL)
	{
		return FALSE;
	}
	int nAllOffSet = 0;   //�ܵ�ƫ����
	int nOffSet = 0;
	CString strVarType;   //����
	CString strVarFlag;

	CString strbuff;  //������
	int nFlag;

	SimVarPara *pvarpara1 = NULL;

//	psimvardata->pchar = new char[198];
//	psimvardata->pchar = new char[nOffSet];
//	memcpy(psimvardata->pchar,0x00,198);
	while(pos)
	{
		pvarpara1 = SimVarParaList.GetAt(pos);
		nOffSet =  pvarpara1->nVarOffSet; //ƫ����
		if (nOffSet>SIM_MAXVAR_SIZE || nOffSet<0)   //����������ڴ�ƫ��������
		{
			return FALSE;
		}
		strVarType = pvarpara1->VarType;  //1:DWORD;2:int;3:double 4:char; 5:long
		if (strVarType=="1")
		{
			psimvardata->dwVarVal = *(DWORD*)(buff+sizeof(double)+sizeof(int)*2 + nAllOffSet);
			nAllOffSet+=nOffSet;	
		}
		else if (strVarType=="2")
		{
			psimvardata->nVarVal = 	*(UINT*)(buff+sizeof(double)+sizeof(int)*2 + nAllOffSet);
			nAllOffSet+=nOffSet;	
		}
		else if (strVarType=="3")
		{
			psimvardata->dbVarVal = *(double*)(buff+sizeof(double)+sizeof(int)*2 + nAllOffSet);
			nAllOffSet+=nOffSet;	
		}
		else if (strVarType=="4")
		{
		//	psimvardata->pchar = new char[nOffSet];

		//	memcpy(psimvardata->pchar,buff+sizeof(double)+sizeof(int)*2 + nAllOffSet,nOffSet);
			if (nOffSet<0 )
			{
				return FALSE;
			}
		    memcpy(tempvarbuff,buff+sizeof(double)+sizeof(int)*2 + nAllOffSet,nOffSet);
			nAllOffSet+=nOffSet;
		}
		else if (strVarType=="5")
		{
			psimvardata->lVarVal = 	*(long*)(buff+sizeof(double)+sizeof(int)*2 + nAllOffSet);
			nAllOffSet+=nOffSet;	
		}
		else
		{
			return FALSE;
		}
		strVarFlag = pvarpara1->VarFlag;
		nFlag = atoi(strVarFlag);
	//	if (nFlag>9999 || nFlag<1001)
		if (nFlag>10000 || nFlag<1001 || nOffSet<0)
		{
			return FALSE;
		}
		switch(nFlag)
		{
		case 1001:
			psimOperdata->dwnckType = psimvardata->dwVarVal;
			break;
		case 1002:
			psimOperdata->dbnckVersion = psimvardata->dbVarVal;
			break;
		case 1003:
			psimOperdata->nmaxnumGlobMachAxes = psimvardata->nVarVal;
			break;
		case 1004:
			psimOperdata->nnumSpindles = psimvardata->nVarVal;
			break;
		case 1005:
			psimOperdata->nnumGeoAxes = psimvardata->nVarVal;
			break;
		case 1006:
			psimOperdata->nnumAuxAxes = psimvardata->nVarVal;
			break;
		case 1007:
			memcpy(psimOperdata->cprogName,tempvarbuff,nOffSet);
			break;
		case 1008:
			memcpy(psimOperdata->cworkPNameLong,tempvarbuff,nOffSet);
			break;
		case 1009:
			psimOperdata->nprogStatus = psimvardata->nVarVal;
			break;
		case 1010:
			psimOperdata->nspeedOvr = psimvardata->nVarVal;
			break;
		case 1011:
			psimOperdata->nnumAlarms = psimvardata->nVarVal;
			break;
		case 1012:
			psimOperdata->ltextIndex1 = psimvardata->lVarVal;
			break;
		case 1013:
			psimOperdata->ltextIndex2 = psimvardata->lVarVal;
			break;
		case 1014:
			psimOperdata->ltextIndex11 = psimvardata->lVarVal;
			break;
		case 1015:
			psimOperdata->dbactToolLength1 = psimvardata->dbVarVal;
			break;
		case 1016:
			psimOperdata->nopMode = psimvardata->nVarVal;
			break;
		case 1017:
		    memcpy(psimOperdata->csingleBlock,tempvarbuff,nOffSet);
			break;
		case 1018:
			psimOperdata->dbactSpeed = psimvardata->dbVarVal;
			break;
		case 1019:
			psimOperdata->dbactFeedRate1 = psimvardata->dbVarVal;
			break;
		case 1020:
			psimOperdata->dbactFeedRate2 = psimvardata->dbVarVal;
			break;
		case 1021:
			psimOperdata->dbactFeedRate3 = psimvardata->dbVarVal;
			break;
		case 1022:
			psimOperdata->dbfeedRateOvr1 = psimvardata->dbVarVal;
			break;
		case 1023:
			psimOperdata->dbfeedRateOvr2 = psimvardata->dbVarVal;
			break;
		case 1024:
			psimOperdata->dbfeedRateOvr3 = psimvardata->dbVarVal;
			break;
		case 1025:
			psimOperdata->dbdriveLoad = psimvardata->dbVarVal;
			break;
		case 1026:
			psimOperdata->dbmaactToolBasePos1 = psimvardata->dbVarVal;
			break;
		case 1027:
			psimOperdata->dbmaactToolBasePos2 = psimvardata->dbVarVal;
			break;
		case 1028:
			psimOperdata->dbmaactToolBasePos3 = psimvardata->dbVarVal;
			break;
		case 1029:
			psimOperdata->dbmaactToolBasePos4 = psimvardata->dbVarVal;
			break;
		case 1030:
			psimOperdata->dbmaactToolBasePos5 = psimvardata->dbVarVal;
			break;
		case 1031:
			psimOperdata->dbgeactToolBasePos1 = psimvardata->dbVarVal;
			break;
		case 1032:
			psimOperdata->dbgeactToolBasePos2 = psimvardata->dbVarVal;
			break;
		case 1033:
			psimOperdata->dbgeactToolBasePos3 = psimvardata->dbVarVal;
			break;
		case 1034:
			psimOperdata->dbgeactToolBasePos4 = psimvardata->dbVarVal;
			break;
		case 1035:
			psimOperdata->dbgeactToolBasePos5 = psimvardata->dbVarVal;
			break;
		case 1036:
			psimOperdata->nmotorTemperature = psimvardata->nVarVal;
			break;
		case 1037:
			psimOperdata->ltoolno = psimvardata->lVarVal;
			break;
		case 1038:   //�涯���
			psimOperdata->dbAxisFollowErr[0] = psimvardata->dbVarVal;
			break;
		case 1039:
			psimOperdata->dbAxisFollowErr[1]= psimvardata->dbVarVal;
			break;
		case 1040:
			psimOperdata->dbAxisFollowErr[2] = psimvardata->dbVarVal;
			break;
		case 1041:
			psimOperdata->dbAxisFollowErr[3] = psimvardata->dbVarVal;
			break;
		case 1042:
			psimOperdata->dbAxisFollowErr[4] = psimvardata->dbVarVal;
			break;
		case 1043:   //���¶�
			psimOperdata->nAxisTemperature[0] = psimvardata->nVarVal;
			break;
		case 1044:
			psimOperdata->nAxisTemperature[1]= psimvardata->nVarVal;
			break;
		case 1045:
			psimOperdata->nAxisTemperature[2] = psimvardata->nVarVal;
			break;
		case 1046:
			psimOperdata->nAxisTemperature[3] = psimvardata->nVarVal;
			break;
		case 1047:
			psimOperdata->nAxisTemperature[4] = psimvardata->nVarVal;
			break;
		case 1048:   //�����
			psimOperdata->nAxisCurrent[0] = psimvardata->nVarVal;
			break;
		case 1049:
			psimOperdata->nAxisCurrent[1]= psimvardata->nVarVal;
			break;
		case 1050:
			psimOperdata->nAxisCurrent[2] = psimvardata->nVarVal;
			break;
		case 1051:
			psimOperdata->nAxisCurrent[3] = psimvardata->nVarVal;
			break;
		case 1052:
			psimOperdata->nAxisCurrent[4] = psimvardata->nVarVal;
			break;
		case 9998:  //������
			memcpy(psimOperdata->cProductinfor,tempvarbuff,nOffSet);
#ifdef _DEBUG
			strbuff = "DNC01Test0907";
			strncpy(psimOperdata->cProductinfor, strbuff, strbuff.GetLength());
#endif
			if (AnalyseProductinfor(psimOperdata->cProductinfor))  //�����Զ������Ϣ
			{
				strncpy(psimOperdata->cProductinfor, psimOperdata->cWorkOrder, 128);  //�����õ�������
			}	
			break;
		case 9999:  //����ԭ��
			memcpy(psimOperdata->cStopInforData,tempvarbuff,nOffSet);
			break;
		default:
			break;
		}
		SimVarParaList.GetNext(pos);
	}
	return TRUE;
}
BOOL CSinumerikOperateSocket::AnalyseProductinfor(const char* buff)
{
	int nTempLength =0;
	UINT nTemp = 0;
	int nTemp1 = 0;
	int iii=0;
	char cTemp[128];
	memset(cTemp,0,128);
	CString strTemp;
	CString strTemp1;
	CString strFlag;
	int nFlag = -1;
	memcpy(cTemp,buff,3);
	strTemp.Format("%s",cTemp,3);
	if (strTemp=="DNC")  //�ж��Ƿ���DNC��Ϣ
	{
		memset(cTemp,0,128);
		strTemp.Empty();
		strTemp.Format("%s",buff+3);
		int nLength = strTemp.GetLength();
		if (nLength<=2)  //��ʶ������Ϊ2
		{
			return FALSE;
		}
		else
		{
			strTemp1 = strTemp.Mid(0,2);
			if (strTemp1 == "01")  //��ʶλ��ȷ
			{
				strTemp1 = strTemp.Mid(2,nLength-1);
				if (strTemp1.GetLength()>128)
				{
					return FALSE;
				}
				strncpy(psimOperdata->cWorkOrder, strTemp1,strTemp1.GetLength() );
				return TRUE;
			}
		}	
/ *
		while(1)
		{
			nTemp = strTemp.Find(";",nTemp1+1);
			strTemp1.Empty();
			if (iii==0)
			{
				strTemp1 = strTemp.Mid(nTemp1,nTemp);
			}
			else
			{
				strTemp1 = strTemp.Mid(nTemp1+1,nTemp-nTemp1-1);
			}
			iii = -1;
			nTemp1=nTemp;
			if (strTemp1=="")
			{
				return FALSE;
			}
			else
			{
				nTempLength =strTemp1.GetLength();
				if (nTempLength<=2)
				{
					return FALSE;
				}
				strFlag = strTemp1.Mid(0,2);
				
				nFlag = atoi(strFlag);
				switch (nFlag)
				{
				case 1:
					strTemp1= strTemp1.Mid(2,nTempLength-2);
					strncpy(psimOperdata->cWorkOrder, strTemp1,nTempLength-2);
					break;
				case 2:
					break;
				default:
					break;
				}
				return TRUE;
			}
			if (nTemp +1>nLength || nTemp +1 == nLength)
			{
				break;
			}
		}	* /
	}
/ *
	else
	{
		return FALSE;
	}* /
	return FALSE;
}
void CSinumerikOperateSocket::FreeList()
{
	POSITION pos=NULL;
	pos = SimVarParaList.GetHeadPosition();
	SimVarPara *pvarpara1 = NULL;
	if(pos)
	{
		while(pos)
		{
			pvarpara1=SimVarParaList.GetNext(pos);
			if(pvarpara1)
			{
				delete pvarpara1;
				pvarpara1=NULL;
			}
		}
		SimVarParaList.RemoveAll();
	}
}*/
void CSinumerikOperateSocket::Disconnect()
{
	if (m_bConnected)
	{
		try
		{
			ShutDown();
			Close();
		}
		catch (...)
		{
		}
		m_bConnected = FALSE;
	}	
}

/*
int CSinumerikOperateSocket::GetSocketErrorText()
{
	int nError = GetLastError();
	switch (nError)
	{
	case WSAENOTSOCK://10038
		TRACE("Socket error: Socket operation on non-socket\n");
		break;
	case WSAEADDRINUSE://10048
		TRACE("Socket error: Address already in ues\n");
		break;
	case WSAENETUNREACH://10051
		TRACE("Socket error: Network is unreachable\n");
		break;
	case WSAENETRESET://10052
		TRACE("Socket error: Network dropped connection on reset\n");
		break;
	case WSAECONNABORTED://10053
		TRACE("Socket error: Software caused connection abort\n");
		break;
	case WSAECONNRESET://10054
		TRACE("Socket error: Connection reset by peer\n");
		//Close();
		break;
	case WSAEISCONN://10056
		TRACE("Socket error: Socket is already connected\n");
		break;
	case WSAENOTCONN://10057
		TRACE("Socket error: Socket is not connected\n");
		break;
	case WSAESHUTDOWN://10058
		TRACE("Socket error: Cannot send after socket shutdown\n");
		break;
	case WSAETIMEDOUT://10060
		TRACE("Socket error: Connection timed out\n");
		break;
	case WSAECONNREFUSED://10061
		TRACE("Socket error: Connection refused\n");
		break;
	default:
		TRACE("Socket error: Other fault %d\n", nError);
		break;
	}
	return nError;
}*/
