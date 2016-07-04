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
	virtual void InitWindow() override;//��OnCreate������
	virtual LRESULT MessageHandler(UINT uMsg, WPARAM wParam, LPARAM /*lParam*/, bool& bHandled) override;
private:
	CButtonUI*	m_pLeft_hide;		//������� ��ʾ��ť
	CButtonUI*  m_pBottom_hide;		//���б�����  ��ʾ��ť
	CButtonUI*  m_pMenu_hide;		//���ð�ť
	CControlUI* m_pLeft_layout;		//��������Ϣ������

	CListUI* m_pMapping_List;		//ӳ���ϵ�б�
	CListUI* m_pConnect_List;		//������Ϣ�б�
private:
	bool ButtonNotify(void* pNotify);//��ť��Ӧ��Ϣ
	void Test();
};

