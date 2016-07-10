#pragma once
#include <uv.h>
#include <map>
using namespace std;
//for  nState
#define MAPPING_STOP	0x00000000
#define MAPPING_START	0x00000001
#define MAPPING_FAIL	0x00000002

#define TCP_CONNECT_FAIL	0x00000010
#define TCP_CONNECT_SUCC	0x00000020
#define TCP_CLIENT_BREAK	0x00000040
#define TCP_SERVER_BREAK	0x00000080

#define WORK_START			0x00000001
#define WORK_STOP			0x00000002
#define WORK_DELETE			0x00000004
/////////////////////////////////////////////////////////////////////////
//client��������>agent��������>server
//client<��������agent<��������server
struct MappingInfo
{
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
	};
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
		};
		uv_udp_t		server_udp;//udp������ͨ�ŵ�socket����socket�յ�����Ϣͨ��listen_tcp���͸��ͻ���
								   //listen_tcp�յ�����Ϣͨ��server_udp���͸������
	};
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
class CLibuvAdapter
{
public:
	CLibuvAdapter();
	virtual ~CLibuvAdapter();
public:
	MappingInfo* AddMapping(LPCWSTR strAgentIP, LPCWSTR strAgentPort, LPCWSTR strServerIP, LPCWSTR strServerPort, bool bTcp, int& err);
	
	bool StartMapping(MappingInfo* pMapping);//��ʼһ��ӳ��
	bool GetLocalIP(vector<wstring>& vecIP);
private:
	bool InitLoop();
	void RegisterAnsycWork(uv__work* pwork, void(*done)(struct uv__work *w, int status));
	
public:
	uv_loop_t*		m_pLoop;
private:
	
	uv_thread_t		m_Loop_thread;
	uv_check_t		m_check_keeprun;
	//data:
	map<USHORT, MappingInfo>	m_mapMapping;
	map<Connectkey, ConnectInfo> m_mapConnect;
};

