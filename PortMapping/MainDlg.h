#pragma once
using namespace DuiLib;
class CMainDlg : public WindowImplBase
{
public:
	CMainDlg();
	virtual ~CMainDlg();
protected:
	//ʵ�ֻ��ി��ӿ�
	virtual CDuiString GetSkinFolder();//������Դ�ļ���
	virtual CDuiString GetSkinFile();//������Դ�ļ�
	virtual LPCTSTR GetWindowClassName(void) const;//ע���õĴ�������
public:
	//��д�����麯��
};

