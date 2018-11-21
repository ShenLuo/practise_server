/*
	gps�������
*/

#pragma once
#include <winsock2.h>

class CarGpsSocket
{
public:
	// ����SOCKET
	CarGpsSocket();	

	// �ͷ�SOCKET
	~CarGpsSocket();

	// ��Ŀ���ַ
	bool SocketBind(int nAF, const char* sIP, int nPort);

	// ����Ŀ���ַ
	bool SocketConnect(int nAF, const char* sIP, int nPort);

	// �������ӵ�ַ
	bool SocketListen(int nMaxValue);

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
};