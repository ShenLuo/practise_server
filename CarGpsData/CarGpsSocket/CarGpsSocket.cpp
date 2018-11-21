/*
	gps网络操作
*/

#include "CarGpsSocket.h"
#include <winsock2.h>

//#pragma comment(lib, "Ws2_32.lib")

// 构造Socket
CarGpsSocket::CarGpsSocket()
{
	// 获取WSADATA信息
	WSADATA wsData;
	int nResult = WSAStartup(MAKEWORD(2,2), &wsData);
	if (NO_ERROR != nResult)
	{
		return;
	}

	// 创建Socket对象
	SOCKET soListen = INVALID_SOCKET;
	soListen = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (soListen == INVALID_SOCKET)
	{
		return;
	}

	m_soSocket = soListen;
	return;
}

// 释放Socket
CarGpsSocket::~CarGpsSocket()
{
	if (m_soSocket == INVALID_SOCKET)
	{
		return;
	}

	closesocket(m_soSocket);
	WSACleanup();
	return;
}

// 绑定目标地址
bool CarGpsSocket::SocketBind(int nAF, const char* sIP, int nPort)
{
	if (m_soSocket == INVALID_SOCKET || strcmp(sIP, "") == 0)
	{
		return  false;
	}

	sockaddr_in stAddress;
	stAddress.sin_family = nAF;
	stAddress.sin_addr.S_un.S_addr = inet_addr(sIP);
	stAddress.sin_port = htons(nPort);

	// 绑定Socket
	int nResultB = bind(m_soSocket, (SOCKADDR *)&stAddress, sizeof(stAddress));
	if (nResultB == SOCKET_ERROR)
	{
		int nError = WSAGetLastError();
		return false;
	}

	return true;
}

// 连接目标地址
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

	// 连接Socket到目标
	int nResultB = connect(m_soSocket, (SOCKADDR *)&stAddress, sizeof(stAddress));
	if (nResultB == SOCKET_ERROR)
	{
		return false;
	}

	return true;
}

// 监听连接地址
bool CarGpsSocket::SocketListen(int nMaxValue)
{
	if (m_soSocket == INVALID_SOCKET)
	{
		return false;
	}

	if (SOCKET_ERROR == listen(m_soSocket, nMaxValue))
	{
		return false;
	}

	return true;
}

//  接受连接
bool CarGpsSocket::SocketAccept(SOCKET& newSocket, sockaddr& sockAddr, int& sockAdLen)
{
	if (m_soSocket == INVALID_SOCKET)
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

// 发送连接数据
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

// 接受连接数据
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

// 断开连接
bool CarGpsSocket::SocketShutDown(SOCKET& newSocket, int nType)
{
	int nResult = shutdown(newSocket, nType);
	if (SOCKET_ERROR == nResult)
	{
		return false;
	}

	return true;
}

// 断开连接
bool CarGpsSocket::SockeClose(SOCKET& newSocket)
{
	int nResult = closesocket(newSocket);
	if (nResult == SOCKET_ERROR)
	{
		return false;
	}

	return true;
}