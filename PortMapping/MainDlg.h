#pragma once
#include "UIMenu.h"
#include "LibuvAdapter.h"
#include "EditUIEx.h"
#include <regex>
#include "MyListItem.h"

using namespace DuiLib;
class CMainDlg : public WindowImplBase,
	public INotifyLoop
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
	//INotifyLoop
	virtual void NotifyConnectMessage(UINT nType, ConnectInfo* pInfo);
	virtual void NotifyMappingMessage(UINT nType, MappingInfo* pInfo);
	virtual void NotifyGetAllConnectByMapping(ConnectInfo** pInfo, size_t size);//��ȡĳһӳ�������������Ϣ
private:
	void UpDataList();
	bool RootNotify(void* p);	//��������˵���Ϣ
	
	bool ButtonNotify(void* pNotify);//��ťNotify��Ϣ
	bool ListNotify(void* pNotify);
	void UpDataConnectList(CControlUI* p_sender);	//ˢ�������б�
	//�б�Notify��Ϣ
	bool ListItemNotify(void* p);	//�����б������Ϣ
	bool CheckPort(void* p);		//���˿�
	bool CheckIP(void* p);			//���IP

	void GetLocalIP();				//��ȡ����IP
	void OnMenuItemInit(CMenuElementUI* pMenuItem, LPARAM l_param);	//�˵���ʼ�����ڵ���֮ǰ����
	void OnMenuItemClick(LPCWSTR pName, LPARAM l_param);			//�˵����
	
	void OnAddClick();												//��Ӱ�ť����
	bool CheckAllInfo();											//��������������Ϣ�Ƿ���Ч

	void DealWithConnectMsg(WPARAM w_param, ConnectInfo* connect_info);
	void DealWithMappingMsg(WPARAM w_param, MappingInfo* mapping_info);
private:
	CButtonUI*	m_pLeft_hide;		//������� ��ʾ��ť
	CButtonUI*  m_pBottom_hide;		//���б�����  ��ʾ��ť
	CButtonUI*  m_pMenu_hide;		//���ð�ť
	CControlUI* m_pLeft_layout;		//��������Ϣ������

	CListUI* m_pMapping_List;		//ӳ���ϵ�б�
	CListUI* m_pConnect_List;		//������Ϣ�б�

	CEditUIEx*	m_pEdit_agent_port;	//���ض˿�
	CEditUIEx*	m_pEdit_server_port;//ӳ��˿�

	CEditUIEx* m_pEdit_server_ip;	//ӳ��IP

	CComboUI*	m_pCmb_protocol;	//Э������
	CComboUI*  m_pCmb_agent_ip;		//����ip

	CButtonUI*	m_pBtn_ADD;			//ADD��ť

	vector<wstring>		m_vecLocalIP;//����IP
	CLibuvAdapter*		m_pLibuv;	//����libuv��ع���

	wregex*				m_pregex_IP;//ip�жϵ�������ʽ

	CMappingListItem*			m_pCur_mapping;
};

