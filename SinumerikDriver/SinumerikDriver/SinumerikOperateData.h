// SinumerikOperateData.h: interface for the SinumerikOperateData class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_SINUMERIKOPERATEDATA_H__E38DCFEF_276A_44DC_8633_B75E7545BAB0__INCLUDED_)
#define AFX_SINUMERIKOPERATEDATA_H__E38DCFEF_276A_44DC_8633_B75E7545BAB0__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include <afxtempl.h>



class SinumerikOperateData  
{
public:
	SinumerikOperateData();
	virtual ~SinumerikOperateData();
//	BOOL GetAllVarValue(const CTypedPtrList<CPtrList,SimVarPara*> &SimVarParaList,const char* buff);
public:

	DWORD dwnckType;            //1��������
	double dbnckVersion;        //2����汾
	int nmaxnumGlobMachAxes;    //3��Ч��
	int nnumSpindles;           //4ת��
	int nnumGeoAxes;            //5������
	int nnumAuxAxes;            //6������
	char cprogName[32];         //7������
	char cworkPNameLong[128];   //8������� 
	int nprogStatus;            //9����״̬
	int nspeedOvr;              //10���ᱶ��
	int nnumAlarms;             //11������
	long ltextIndex1;           //12��һ����
	long ltextIndex2;           //13�ڶ�����
	long ltextIndex11;          //14��߱���
	double dbactToolLength1;    //15��ǰ���ߵĳ���
	int nopMode;                //16�豸״̬jog mda auto
	char csingleBlock[198];     //17ִ�д�����к�
	double dbactSpeed;          //18����ת��
	double dbactFeedRate1;      //19�����ٶ�X
	double 	dbactFeedRate2;     //20�����ٶ�Y
	double 	dbactFeedRate3;     //21�����ٶ�Z
	double dbfeedRateOvr1;      //22��������X
	double dbfeedRateOvr2;      //23��������Y
	double dbfeedRateOvr3;      //24��������Z
	double dbdriveLoad;         //25����
	double dbmaactToolBasePos1; //26machinepos1
	double	dbmaactToolBasePos2;//27
	double	dbmaactToolBasePos3;//28
	double	dbmaactToolBasePos4;//29
	double	dbmaactToolBasePos5;//30
	double	dbgeactToolBasePos1; //31/Geo-pos1
	double	dbgeactToolBasePos2;//32
	double	dbgeactToolBasePos3;//33
	double	dbgeactToolBasePos4;//34
	double	dbgeactToolBasePos5;//35
	int nmotorTemperature;        //36���¶�
	long ltoolno;                 //37��������
	double dbAxisFollowErr[5];    //38-42:�涯���
	int nAxisTemperature[5];  //43-47 �����¶�
	int nAxisCurrent[5];      //48-52 �������
	char cProductinfor[128];      //38�ӹ���Ϣ�������ţ�����  wl-201540608-Add
    char cWorkOrder[128];   //�����ţ��Ӽӹ���Ϣ����ȡ�Ĺ�����

	char cStopInforData[128];          //wl-201440806-Add //����

	DWORD dWorkCount1;//�������ӹ�����/20151205-wxf
	DWORD dWorkCount2;
};

#endif // !defined(AFX_SINUMERIKOPERATEDATA_H__E38DCFEF_276A_44DC_8633_B75E7545BAB0__INCLUDED_)
