#include "stdafx.h"
#include "LibuvAdapter.h"
#include "../libuv-dll/src/queue.h"

//common fun
LPCWSTR a2w(const char* str)//�ڴ���Ҫ�Լ��ͷ�
{
	if (!str)
		return L"";
	int wlength = MultiByteToWideChar(CP_ACP, 0, str, -1, nullptr, 0);
	if (wlength < 1)
		return L"";
	wchar_t* pw = new wchar_t[wlength + 1];
	memset(pw, 0, sizeof(wchar_t) * (wlength + 1));
	MultiByteToWideChar(CP_ACP, 0, str, -1, pw, wlength);
	return pw;
}
string w2a(const wchar_t* str)
{
	if (!str)
		return "";
	int alength = WideCharToMultiByte(CP_ACP, 0, str, -1, nullptr, 0, nullptr, nullptr);
	if (alength < 1)
		return "";
	char* pa = new char[alength + 1];
	memset(pa, 0, sizeof(char) * (alength + 1));
	WideCharToMultiByte(CP_ACP, 0, str, -1, pa, alength, nullptr, nullptr);
	string astr(pa);
	delete[] pa;
	return astr;
}
CLibuvAdapter::CLibuvAdapter() : m_pLoop(nullptr)
{
}


CLibuvAdapter::~CLibuvAdapter()
{
}

MappingInfo* CLibuvAdapter::AddMapping(LPCWSTR strAgentIP, LPCWSTR strAgentPort, LPCWSTR strServerIP, LPCWSTR strServerPort, bool bTcp, int& err)
{
	err = 0;
	USHORT nAgentPort = _wtoi(strAgentPort);
	if (m_mapMapping.find(nAgentPort) != m_mapMapping.end())
	{
		err = 1;//ӳ���Ѵ���
		return nullptr;
	}
	MappingInfo& curInfp = m_mapMapping[nAgentPort];//���ӳ��
	memset(&curInfp, 0, sizeof MappingInfo);//��ʼ��ӳ��
	curInfp.bTCP = bTcp;
	string strIP = w2a(strAgentIP);
	uv_ip4_addr(strIP.c_str(), nAgentPort, &curInfp.Addr_agent);

	strIP = w2a(strServerIP);
	USHORT nServerPort = _wtoi(strServerPort);
	uv_ip4_addr(strIP.c_str(), nAgentPort, &curInfp.Addr_server);

	return &curInfp;
}

bool CLibuvAdapter::StartMapping(MappingInfo* pMapping)
{
	if (!m_pLoop && !InitLoop())
		return false;
	//�����߳��Ѿ��������������Ĳ��������첽��
	return true;
}

//�ջص�  
void null_cb(uv_check_t* handle)
{}
 void LoopThread(void *arg)
{
	CLibuvAdapter* pThis = (CLibuvAdapter*)arg;
	if (!pThis)
		return;
	uv_run(pThis->m_pLoop, UV_RUN_DEFAULT);//����ѭ��
}
//��ʼ��loop
bool CLibuvAdapter::InitLoop()
{
	m_pLoop = uv_default_loop();
	if (!m_pLoop)
		return false;
	//�����ı����¼�ѭ����һ���յĻص�
	uv_check_init(m_pLoop, &m_check_keeprun);
	uv_check_start(&m_check_keeprun, null_cb);
	int ret = uv_thread_create(&m_Loop_thread, LoopThread, this);//���������߳�
	return ret == 0;
}
//ע��һ������loop�������񽫻���loop���ڵ��߳���ִ��
void CLibuvAdapter::RegisterAnsycWork(uv__work* pwork, void(* done)(uv__work* w, int status))
{
	if (!pwork || !m_pLoop)
		return;
	pwork->done = done;
	pwork->loop = m_pLoop;
	uv_mutex_lock(&m_pLoop->wq_mutex);
	pwork->work = nullptr;
	QUEUE_INSERT_TAIL(&m_pLoop->wq, &pwork->wq);
	uv_async_send(&m_pLoop->wq_async);
	uv_mutex_unlock(&m_pLoop->wq_mutex);
}