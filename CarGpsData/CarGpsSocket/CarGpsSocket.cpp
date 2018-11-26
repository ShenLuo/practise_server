/*
	gps�������
*/

#include "CarGpsSocket.h"
#include "CarGpsSocketDef.h"
#include <winsock2.h>

//#pragma comment(lib, "Ws2_32.lib")

// ����Socket
CarGpsSocket::CarGpsSocket(const CarGpsServer* server)
{
	if (NULL == server)
	{
		return;
	}

	m_soSocket = INVALID_SOCKET;
	m_Server = server;
	m_sIP = "";
	m_nPort = -1;
	m_nAFamily = AF_UNSPEC;
	m_nMaxClientCount = 0;
	m_nRecThreadID = 0;
	m_nSendThreadID = 0;
	m_sRecHandle = NULL;
	m_sSendHandle = NULL;
	return;
}

// �ͷ�Socket
CarGpsSocket::~CarGpsSocket()
{
	m_soSocket = INVALID_SOCKET;
	m_Server = NULL;
	m_sIP = "";
	m_nPort = -1;
	m_nAFamily = AF_UNSPEC;
	m_nMaxClientCount = 0;
	return;
}

// ��ʼ��socket
bool CarGpsSocket::InitSocket(int nAF, const char* sIP, int nPort)
{
	// ��ȡWSADATA��Ϣ
	WSADATA wsData;
	int nResult = WSAStartup(MAKEWORD(2,2), &wsData);
	if (NO_ERROR != nResult)
	{
		return false;
	}

	// ����Socket����
	SOCKET soListen = INVALID_SOCKET;
	soListen = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (soListen == INVALID_SOCKET)
	{
		return false;
	}

	sockaddr_in stAddress;
	stAddress.sin_family = nAF;
	stAddress.sin_addr.S_un.S_addr = inet_addr(sIP);
	stAddress.sin_port = htons(nPort);

	// ��Socket
	int nResultB = bind(soListen, (SOCKADDR *)&stAddress, sizeof(stAddress));
	if (nResultB == SOCKET_ERROR)
	{
		int nError = WSAGetLastError();
		return false;
	}

	m_soSocket = soListen;
	m_sIP = sIP;
	m_nPort = nPort;
	m_nAFamily = nAF;
	return true;
}

// ��ʼsocket
bool CarGpsSocket::StartSocket(int nType, int nMaxCount)
{
	switch (nType)
	{
	case SocketType::SocketTypeServer:
		{
			// socket�������ȴ��ͻ�������
			
			m_nMaxClientCount = nMaxCount;
		}

		break;
	case SocketType::SocketTypeClient:
		{
			// socket�ͻ������ӷ�����
			if (SocketConnect(m_nAFamily, m_sIP.c_str(), m_nPort))
			{
				m_sRecHandle = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)CarGpsSocket::RecHandle ,
					this, 0, &m_nRecThreadID);
				m_sSendHandle = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)CarGpsSocket::SendHandle ,
					this, 0, &m_nSendThreadID);
			}
		}

		break;
	default:
		break;
	}
}

// ����socket
bool CarGpsSocket::EndSocket()
{
	if (m_soSocket == INVALID_SOCKET)
	{
		return;
	}

	closesocket(m_soSocket);
	WSACleanup();
}

// ������Ϣ������
int CarGpsSocket::RecHandle(void* lParam)
{
	if (NULL == lParam)
	{
		return 0;
	}

	CarGpsSocket* pSocket = (CarGpsSocket*)lParam;
	pSocket->SocketRecv();
}

// ������Ϣ������
int CarGpsSocket::SendHandle(void* lParam)
{
	if (NULL == lParam)
	{
		return 0;
	}
}


// ����Ŀ���ַ
bool CarGpsSocket::SocketConnect(int nAF, const char* sIP, int nPort)
{
	if (m_soSocket == INVALID_SOCKET || strcmp(sIP, "") == 0)
	{
		return  false;
	}

	sockaddr_in stAddress;
	stAddress.sin_family = nAF;
	stAddress.sin_addr.S_un.S_addr = inet_addr(sIP);
	stAddress.sin_port = htons(nPort);

	// ����Socket��Ŀ��
	int nResultB = connect(m_soSocket, (SOCKADDR *)&stAddress, sizeof(stAddress));
	if (nResultB == SOCKET_ERROR)
	{
		return false;
	}

	return true;
}

//  ��������
bool CarGpsSocket::SocketAccept(SOCKET& newSocket, sockaddr& sockAddr, int& sockAdLen)
{
	if (m_soSocket == INVALID_SOCKET)
	{
		return false;
	}

	if (SOCKET_ERROR == listen(m_soSocket, m_nMaxClientCount))
	{
		return false;
	}

	newSocket = accept(m_soSocket, &sockAddr, &sockAdLen);

	if (SOCKET_ERROR == newSocket)
	{
		return false;
	}
	
	return true;
}

// ������������
bool CarGpsSocket::SocketSend(SOCKET& newSocket, char* buf, int nSize, int nFlag)
{
	if (m_soSocket == INVALID_SOCKET)
	{
		return false;	
	}

	int nResult = send(newSocket, buf, nSize, nFlag);
	if (nResult == SOCKET_ERROR)
	{
		return false;
	}
	else
	{

	}

	return true;
}

// ������������
bool CarGpsSocket::SocketRecv(SOCKET& newSocket, char* buf, int nSize, int nFlag)
{
	if (newSocket == INVALID_SOCKET || NULL == buf)
	{
		return false;
	}

	int nResult = recv(newSocket, buf, nSize, nFlag);
	if (nResult == SOCKET_ERROR)
	{

	}
	else if (nResult == 0)
	{

	}
	else
	{
		
	}

	return true;
}

// �Ͽ�����
bool CarGpsSocket::SocketShutDown(SOCKET& newSocket, int nType)
{
	int nResult = shutdown(newSocket, nType);
	if (SOCKET_ERROR == nResult)
	{
		return false;
	}

	return true;
}

// �Ͽ�����
bool CarGpsSocket::SockeClose(SOCKET& newSocket)
{
	int nResult = closesocket(newSocket);
	if (nResult == SOCKET_ERROR)
	{
		return false;
	}

	return true;
}