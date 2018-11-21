/*
	gps网络操作
*/

#pragma once
#include <winsock2.h>

class CarGpsSocket
{
public:
	// 创建SOCKET
	CarGpsSocket();	

	// 释放SOCKET
	~CarGpsSocket();

	// 绑定目标地址
	bool SocketBind(int nAF, const char* sIP, int nPort);

	// 连接目标地址
	bool SocketConnect(int nAF, const char* sIP, int nPort);

	// 监听连接地址
	bool SocketListen(int nMaxValue);

	//  接受连接
	bool SocketAccept(SOCKET& newSocket, sockaddr& sockAddr, int& sockAdLen);

	// 发送连接数据
	bool SocketSend(SOCKET& newSocket, char* buf, int nSize, int nFlag);

	// 接受连接数据
	bool SocketRecv(SOCKET& newSocket, char* buf, int nSize, int nFlag);

	// 断开连接
	bool SocketShutDown(SOCKET& newSocket, int nType);

	// 断开连接
	bool SockeClose(SOCKET& newSocket);
private:
	// Socket
	SOCKET m_soSocket;
};