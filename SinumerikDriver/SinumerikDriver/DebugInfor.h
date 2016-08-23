#pragma once
enum DebugInforType
{
	Driver
};
class CDebugInfor
{
public:
	CDebugInfor();
	~CDebugInfor();


public:
	static void ShowDebugInfor(int nDebugType, TCHAR* szDebugInfor);
};

