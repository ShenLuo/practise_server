/*
	gps�������ඨ��
*/

#include "CarGpsServer.h"

CarGpsServer::CarGpsServer()
{
	m_pCarGpsSql = nullptr;
	m_pCarGpsSocket = nullptr;
}

CarGpsServer::~CarGpsServer()
{

}

// ��ʼ��������
bool CarGpsServer::InitServer()
{
	m_pCarGpsSql = new CarGpsSql;
	m_pCarGpsSocket = new CarGpsSocket;

}

// ���з������߼�
bool CarGpsServer::StartServer()
{
	
}
