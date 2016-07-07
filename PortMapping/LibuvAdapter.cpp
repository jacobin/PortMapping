#include "LibuvAdapter.h"

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
CLibuvAdapter::CLibuvAdapter()
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