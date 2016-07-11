#pragma once
#define  DUI_CTR_EDITEX                            (_T("EditEx"))
struct CheckInfo
{
	DuiLib::CDuiString	m_content;			//����������
	DuiLib::CDuiString	m_waring_info;		//������ʾ����
};
class CEditUIEx : public DuiLib::CEditUI
{
	friend class CEditWndEx;
public:
	CEditUIEx();
	virtual ~CEditUIEx();
public:
	virtual LPCTSTR GetClass() const override;
	virtual LPVOID GetInterface(LPCTSTR pstrName) override;
	virtual void PaintBorder(HDC hDC) override;
	virtual void DoEvent(DuiLib::TEventUI& event) override;
	virtual void SetText(LPCTSTR pstrText) override;
	virtual HWND GetNativeEditHWND() const override;
	virtual void SetPos(RECT rc, bool bNeedInvalidate = true) override;
	virtual void Move(SIZE szOffset, bool bNeedInvalidate = true) override;
	virtual void SetAttribute(LPCTSTR pstrName, LPCTSTR pstrValue) override;
	virtual void SetInternVisible(bool bVisible = true) override;
public:
	void SetShowWaring(bool bWaring = true) { m_bShowWaring = bWaring; };
	static void SetWaringColor(DWORD nCol) { CEditUIEx::m_nWaringCol = nCol; };
	bool GetState() { return m_bOK; };
private:
	bool CheckContent();
public:
	static DWORD 	m_nWaringCol;	//������߿���ɫ
	DuiLib::CEventSource OnCheck;	//����ί��
	
private:
	CEditWndEx*		m_pWindowEx;
	bool			m_bShowWaring;	//�Ƿ���ʾ�����
	bool			m_bOK;			//���ݼ���Ƿ�ͨ��
	CheckInfo		m_check_info;
};

