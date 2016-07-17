#pragma once
#include <uv.h>
#include <map>
#include <set>

using namespace std;
//for  nState
#define MAPPING_STOP	0x00000000
#define MAPPING_START	0x00000001
#define MAPPING_FAIL	0x00000002
//
#define INIT_FAIL		0x00000010
#define BIND_FAIL		0x00000020
#define LISTEN_FAIL		0x00000040

#define TCP_CONNECT_FAIL	0x00000080
#define TCP_CONNECT_SUCC	0x00000100


#define TCP_CLIENT_BREAK	0x00010000
#define TCP_SERVER_BREAK	0x00020000


/////////////////////////////////////////////////////////////////////////
//client��������>agent��������>server
//client<��������agent<��������server
struct MappingInfo
{
	uv_loop_t*		pLoop;
	int				nState;		
	sockaddr_in		Addr_agent;
	sockaddr_in		Addr_server;
	bool			bTCP;
	int				nConnect;

	UINT32			nTotalFromClientB;
	UINT32			nTotalFromClientM;

	UINT32			nTotalFromServerB;
	UINT32			nTotalFromServerM;
	union socket_listen
	{
		uv_tcp_t	listen_tcp;
		uv_udp_t	listen_udp;
	} u;
	void*			pUserData;
};
struct ConnectInfo
{
	MappingInfo*	pMapping;		//�����������Ķ�Ӧӳ��
	sockaddr_in		Addr_Client;	//�ͻ��˵�ַ

	UINT32			nCurFromClientB;
	UINT32			nCurFromClientM;

	UINT32			nCurFromServerB;
	UINT32			nCurFromServerM;
	union socket_connect
	{
		struct socket_tcp
		{
			uv_tcp_t	client_tcp;//��ͻ������ӵ�socket����socket�յ�����Ϣͨ��server_tcp���ͳ�ȥ
			uv_tcp_t	server_tcp;//���������ӵ�socket����socket�յ�����Ϣͨ��client_tcp���ͳ�ȥ
		} tcp;
		uv_udp_t		server_udp;//udp������ͨ�ŵ�socket����socket�յ�����Ϣͨ��listen_tcp���͸��ͻ���
								   //listen_tcp�յ�����Ϣͨ��server_udp���͸������
	} u;
	bool			bInMap;			//�Ƿ��Ѿ����뵽��¼��
	void*			pUserData;
};
struct Connectkey
{
	UINT	nClientIP;
	USHORT	nClientPort;
	bool operator<(const Connectkey& other)
	{
		if (nClientIP < other.nClientIP)
			return true;
		if (nClientIP == other.nClientIP && nClientPort < other.nClientPort)
			return true;
		return false;
	}
};
inline bool operator<(const Connectkey& A, const Connectkey& B)
{
	if (A.nClientIP < B.nClientIP)
		return true;
	if (A.nClientIP == B.nClientIP && A.nClientPort < B.nClientPort)
		return true;
	return false;
}
wstring a2w(const char* str);
string w2a(LPCWSTR* str);

#define ADD_CONNECT		0x0000001
#define DELETE_CONNECT	0x0000002
class INotifyLoop
{
public:
	virtual void NotifyConnectMessage(UINT nType, ConnectInfo* pInfo) const = 0; //connect��Ϣ�����仯ʱ��֪ͨ
};
class IOCallBack;
class CLibuvAdapter
{
	friend IOCallBack;
public:
	CLibuvAdapter();
	virtual ~CLibuvAdapter();
public:
	const MappingInfo* AddMapping(LPCWSTR strAgentIP, LPCWSTR strAgentPort, LPCWSTR strServerIP, LPCWSTR strServerPort, bool bTcp, int& err);
	//��ʼһ��ӳ��
	bool StartMapping(MappingInfo* pMapping);
	//ֹͣһ��ӳ��
	bool StopMapping(MappingInfo* pMapping);
	//�Ͽ�һ������
	bool RemoveConnect(ConnectInfo* connect_info, bool bAsync = true);//bAsync:�Ƿ���Ҫ�첽
	//��ȡ���б���ip  ipv4
	bool GetLocalIP(vector<wstring>& vecIP);
	//
	bool AddNotify(INotifyLoop* p);
	//
	bool RemoveNotify(INotifyLoop* p);
	
private:
	typedef void(*AsyncWork)(struct uv__work*, int);
	bool InitLoop();	//��ʼ��loop

	void RegisterAnsycWork(uv__work* pwork, AsyncWork);//��loopע���첽����
	
	void AsyncOperate(void* p, AsyncWork workfun);//�첽�����û��Ĳ���
												  
	void AddConnect(ConnectInfo* connect_info);//���һ����¼
	
	void RemoveAllConnect(MappingInfo* pMappingInfo);//�Ƴ�ĳһӳ��˿���ص�ȫ������

	ConnectInfo* GetUDPConnect(MappingInfo* mapping_info, const sockaddr_in* addr);//
public:
	uv_loop_t*		m_pLoop;
private:
	
	set<INotifyLoop*>	m_setNotify;

	uv_thread_t		m_Loop_thread;
	uv_check_t		m_check_keeprun;
	//data:
	map<USHORT, MappingInfo>	m_mapMapping;
	map<USHORT, map<Connectkey, ConnectInfo*>> m_mapConnect;
};

