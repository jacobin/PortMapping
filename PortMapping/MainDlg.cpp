#include "stdafx.h"
#include "MainDlg.h"
#include "resource.h"

CMainDlg::CMainDlg()
{
}


CMainDlg::~CMainDlg()
{
}

CDuiString CMainDlg::GetSkinFolder()
{
	return L"";
}
//����xml�ļ���Դ����ԴID
CDuiString CMainDlg::GetSkinFile()
{
	return L"skin.xml";
}

LPCTSTR CMainDlg::GetWindowClassName(void) const
{
	return L"CMainDlg_Duilib";
}

