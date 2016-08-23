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
				ShutDown();//释放Socket资源占用问题
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
//* 函数名称：SendReadCmd
//* 函数功能：发送读取指令
//* 返回值：BOOL :TRUE:成功；FALSE：失败
//* 参数说明：strCmd：读取指令
//* 创建者：  wl
//* 创建日期：2014年05月30日
//* 修改日期：
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
// * 函数名称：GetServVersion
// * 函数功能：获得服务端版本号
// * 返回值：BOOL :TRUE:成功；FALSE：失败
// * 参数说明：无
// * 创建者：  wl
// * 创建日期：2014年05月30日
// * 修改日期：
// ********************************************************************
BOOL CSinumerikOperateSocket::GetServVersion()
{
	if (SendReadCmd(SINUMERIK_VSERSION))   //发送读取版本指令
	{
	//	TRACE("Socket-GetServVersion成功\n");
		return TRUE;
	}
	else
	{
	//	TRACE("Socket-GetServVersion失败\n");
		return FALSE;
	}
	return FALSE;
}

// ********************************************************************
// * 函数名称：GetCNCVarinfor
// * 函数功能：获得变量标签号，每个变量对应一个标签号，一一对应关系
// * 返回值：BOOL :TRUE:成功；FALSE：失败
// * 参数说明：无
// * 创建者：  wl
// * 创建日期：2014年05月30日
// * 修改日期：
// ********************************************************************

BOOL CSinumerikOperateSocket::GetCNCVarinfor()
{
	if (SendReadCmd(SINUMERIK_VARFLAG))
	{
	//	TRACE("Socket-GetCNCVarinfor成功\n");
		Sleep(8);
		return TRUE;
	}
	else
	{
	//	TRACE("Socket-GetCNCVarinfor失败\n");
		return FALSE;
	}
	return FALSE;
}
// ********************************************************************
// * 函数名称：GetVarTypeDefine
// * 函数功能：获得变量类型定义
// * 返回值：BOOL :TRUE:成功；FALSE：失败
// * 参数说明：无
// * 创建者：  wl
// * 创建日期：2014年05月30日
// * 修改日期：
// ********************************************************************
BOOL CSinumerikOperateSocket::GetVarOffSet()
{
	if(SendReadCmd(SINUMERIK_VAROFFSET))
	{
		//TRACE("Socket-GetVarOffSet成功\n");
		Sleep(8);
		return TRUE;
	}
	else
	{
		//TRACE("Socket-GetVarOffSet失败\n");
		return FALSE;
	}
	return FALSE;
}
// ********************************************************************
// * 函数名称：GetVarTypeDefine
// * 函数功能：获得变量类型定义
// * 返回值：BOOL :TRUE:成功；FALSE：失败
// * 参数说明：无
// * 创建者：  wl
// * 创建日期：2014年05月30日
// * 修改日期：
// ********************************************************************

BOOL CSinumerikOperateSocket::GetVarTypeDefine()
{
	if(SendReadCmd(SINUMERIK_VARDEFINE))
	{
		//TRACE("Socket-GetVarTypeDefine成功\n");
		Sleep(8);
		return TRUE;
	}
	else
	{
		//TRACE("Socket-GetVarTypeDefine失败\n");
		return FALSE;
	}
	return FALSE;
}
// ********************************************************************
// * 函数名称：GetNCData
// * 函数功能：获得变量数据
// * 返回值：BOOL :TRUE:成功；FALSE：失败
// * 参数说明：无
// * 创建者：  wl
// * 创建日期：2014年06月04日
// * 修改日期：
// ********************************************************************
BOOL CSinumerikOperateSocket::GetNCData()
{
	if(SendReadCmd(SINUMERIK_VARDATA))
	{
		//TRACE("Socket-GetNCData成功\n");
		Sleep(8);
		return TRUE;
	}
	else
	{
		//TRACE("Socket-GetNCData失败\n");
		return FALSE;
	}
	return FALSE;
}
// ********************************************************************
// * 函数名称：ProcessMsg
// * 函数功能：OnReceive接收到的消息处理
// * 返回值：
// * 参数说明：无
// * 创建者：  wl
// * 创建日期：2014年06月03日
// * 修改日期：
// ********************************************************************
void CSinumerikOperateSocket::ProcessMsg( const int nByte )
{
	if (nByte == SIM_HEADER_SIZE)//接收到的消息小于数据消息头，接收的为服务端版本信息，格式为version:1.0  CString+double格式
	{
	//	char* tempbuff = new char[SIM_HEADER_SIZE];
		memcpy(tempHeadbuff,m_pcBuffer,SIM_HEADER_SIZE);
		AnalyseMsgVersion(tempHeadbuff);
	}
	else if (nByte>SIM_HEADER_SIZE) //接收到的消息大于数据消息头，说明消息头后面带有数据,格式:版本号(double) + 消息类型(int) + 数据个数(int) + 数据
	{
		memcpy(tempDatabuff,m_pcBuffer,nByte);
		AnalyseMsgData(tempDatabuff);
	}
}
// ********************************************************************
// * 函数名称：AnalyseMsgVersion
// * 函数功能：解析OnReceive接收到的消息处理，得到版本号
// * 返回值：  无
// * 参数说明：buff：收到的字符串;dbver:解析得到的版本号
// * 创建者：  wl
// * 创建日期：2014年06月03日
// * 修改日期：
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
// * 函数名称：AnalyseMsgData
// * 函数功能：解析OnReceive接收到的消息处理，得到数据
// * 返回值：  无
// * 参数说明：buff：收到的字符串;
// * 创建者：  wl
// * 创建日期：2014年06月03日
// * 修改日期：
// ********************************************************************
//格式:版本号(double) + 消息类型(int) + 数据个数(int) + 数据

void CSinumerikOperateSocket::AnalyseMsgData( const char* buff)
{
	//解析得到消息类型
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
// * 函数名称：SaveVarFlag
// * 函数功能：解析并保存变量标签
// * 返回值：  无
// * 参数说明：buff：收到的字符串;
// * 创建者：  wl
// * 创建日期：2014年06月03日
// * 修改日期：
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
// * 函数名称：SaveVarOffSet
// * 函数功能：解析并保存变量偏移
// * 返回值：  无
// * 参数说明：buff：收到的字符串;
// * 创建者：  wl
// * 创建日期：2014年06月04日
// * 修改日期：
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
// * 函数名称：SaveVarDefine
// * 函数功能：解析并保存变量定义
// * 返回值：  无
// * 参数说明：buff：收到的字符串;
// * 创建者：  wl
// * 创建日期：2014年06月04日
// * 修改日期：
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
// * 函数名称：SaveVarValue
// * 函数功能：解析并保存变量值
// * 返回值：  无
// * 参数说明：buff：收到的字符串;
// * 创建者：  wl
// * 创建日期：2014年06月04日
// * 修改日期：
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
	int nAllOffSet = 0;   //总的偏移量
	int nOffSet = 0;
	CString strVarType;   //类型
	CString strVarFlag;

	CString strbuff;  //测试用
	int nFlag;

	SimVarPara *pvarpara1 = NULL;

//	psimvardata->pchar = new char[198];
//	psimvardata->pchar = new char[nOffSet];
//	memcpy(psimvardata->pchar,0x00,198);
	while(pos)
	{
		pvarpara1 = SimVarParaList.GetAt(pos);
		nOffSet =  pvarpara1->nVarOffSet; //偏移量
		if (nOffSet>SIM_MAXVAR_SIZE || nOffSet<0)   //如果解析的内存偏移量大于
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
		case 1038:   //随动误差
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
		case 1043:   //轴温度
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
		case 1048:   //轴电流
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
		case 9998:  //工单号
			memcpy(psimOperdata->cProductinfor,tempvarbuff,nOffSet);
#ifdef _DEBUG
			strbuff = "DNC01Test0907";
			strncpy(psimOperdata->cProductinfor, strbuff, strbuff.GetLength());
#endif
			if (AnalyseProductinfor(psimOperdata->cProductinfor))  //解析自定义的信息
			{
				strncpy(psimOperdata->cProductinfor, psimOperdata->cWorkOrder, 128);  //解析得到工单号
			}	
			break;
		case 9999:  //待机原因
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
	if (strTemp=="DNC")  //判断是否是DNC信息
	{
		memset(cTemp,0,128);
		strTemp.Empty();
		strTemp.Format("%s",buff+3);
		int nLength = strTemp.GetLength();
		if (nLength<=2)  //标识符长度为2
		{
			return FALSE;
		}
		else
		{
			strTemp1 = strTemp.Mid(0,2);
			if (strTemp1 == "01")  //标识位正确
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
