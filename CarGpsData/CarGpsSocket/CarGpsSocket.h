/*
	gps网络操作
*/

#pragma once
#include "../CarGpsServer/CarGpsServer.h"
#include <winsock2.h>

class CarGpsSocket
{
public:
	// 创建SOCKET
	CarGpsSocket(const CarGpsServer* server);	

	// 释放SOCKET
	~CarGpsSocket();

	// 初始化socket
	bool InitSocket(int nAF, const char* sIP, int nPort);

	// 开始socket
	bool StartSocket(int nType, int nMaxCount = 0);

	// 结束socket
	bool EndSocket();

	// 接收消息处理函数
	static int RecHandle(void* lParam);

	// 发送消息处理函数
	static int SendHandle(void* lParam);

private:
	// 连接目标地址
	bool SocketConnect(int nAF, const char* sIP, int nPort);

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

	// ip地址
	std::string m_sIP;

	// 端口
	int m_nPort;

	// 协议族
	int m_nAFamily;

	// 能够连接的最大客户端数量
	int m_nMaxClientCount;

	// 服务器
	const CarGpsServer* m_Server;

	// 接收消息线程
	void* m_sRecHandle;
	unsigned long m_nRecThreadID;

	// 发送消息线程
	void* m_sSendHandle;
	unsigned long m_nSendThreadID;
};