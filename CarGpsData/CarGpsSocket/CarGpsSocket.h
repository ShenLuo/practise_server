/*
	gps�������
*/

#pragma once
#include "../CarGpsServer/CarGpsServer.h"
#include <winsock2.h>

class CarGpsSocket
{
public:
	// ����SOCKET
	CarGpsSocket(const CarGpsServer* server);	

	// �ͷ�SOCKET
	~CarGpsSocket();

	// ��ʼ��socket
	bool InitSocket(int nAF, const char* sIP, int nPort);

	// ��ʼsocket
	bool StartSocket(int nType, int nMaxCount = 0);

	// ����socket
	bool EndSocket();

	// ������Ϣ������
	static int RecHandle(void* lParam);

	// ������Ϣ������
	static int SendHandle(void* lParam);

private:
	// ����Ŀ���ַ
	bool SocketConnect(int nAF, const char* sIP, int nPort);

	//  ��������
	bool SocketAccept(SOCKET& newSocket, sockaddr& sockAddr, int& sockAdLen);

	// ������������
	bool SocketSend(SOCKET& newSocket, char* buf, int nSize, int nFlag);

	// ������������
	bool SocketRecv(SOCKET& newSocket, char* buf, int nSize, int nFlag);

	// �Ͽ�����
	bool SocketShutDown(SOCKET& newSocket, int nType);

	// �Ͽ�����
	bool SockeClose(SOCKET& newSocket);
private:
	// Socket
	SOCKET m_soSocket;

	// ip��ַ
	std::string m_sIP;

	// �˿�
	int m_nPort;

	// Э����
	int m_nAFamily;

	// �ܹ����ӵ����ͻ�������
	int m_nMaxClientCount;

	// ������
	const CarGpsServer* m_Server;

	// ������Ϣ�߳�
	void* m_sRecHandle;
	unsigned long m_nRecThreadID;

	// ������Ϣ�߳�
	void* m_sSendHandle;
	unsigned long m_nSendThreadID;
};