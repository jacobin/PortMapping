#pragma once
#include "UIMenu.h"
#include "LibuvAdapter.h"
#include "EditUIEx.h"

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
	virtual CControlUI* CreateControl(LPCTSTR pstrClass)  override;
public:
	
	//��д�����麯��
	virtual void InitWindow() override;//��OnCreate������
	
	virtual LRESULT MessageHandler(UINT uMsg, WPARAM wParam, LPARAM /*lParam*/, bool& bHandled) override;
	virtual LRESULT HandleCustomMessage(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled) override;
private:
	bool RootNotify(void* p);
	
	bool ButtonNotify(void* pNotify);//��ťNotify��Ϣ
	bool ListNotify(void* pNotify);//�б�Notify��Ϣ
	bool ListItemNotify(void* p);
	bool CheckPort(void* p);
	bool CheckIP(void* p);

	void GetLocalIP();
	void OnMenuItemInit(CMenuElementUI* pMenuItem, LPARAM l_param);
	void OnMenuItemClick(LPCWSTR pName, LPARAM l_param);
	void OnAddClick();
	bool CheckAllInfo();
	void Test();
	
private:
	CButtonUI*	m_pLeft_hide;		//������� ��ʾ��ť
	CButtonUI*  m_pBottom_hide;		//���б�����  ��ʾ��ť
	CButtonUI*  m_pMenu_hide;		//���ð�ť
	CControlUI* m_pLeft_layout;		//��������Ϣ������

	CListUI* m_pMapping_List;		//ӳ���ϵ�б�
	CListUI* m_pConnect_List;		//������Ϣ�б�

	CEditUIEx*	m_pEdit_agent_port;
	CEditUIEx*	m_pEdit_server_port;

	CEditUIEx* m_pEdit_server_ip;

	CComboUI*	m_pCmb_protocol;
	CComboUI*  m_pCmb_agent_ip;

	CButtonUI*	m_pBtn_ADD;

	vector<wstring>		m_vecLocalIP;
	CLibuvAdapter*		m_pLibuv;
};

