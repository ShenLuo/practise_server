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

bool CarGpsServer::RunServer()
{
	m_thread = new thread(&ThreadServer, NULL);
	return true;
}

// ��ʼ��������
bool CarGpsServer::InitServer()
{
	m_pCarGpsSql = new CarGpsSql;
	m_pCarGpsSocket = new CarGpsSocket(this);

	// ��ʼ���߼�ģ��
	std::map<std::string, CarGpsLogic*>::iterator it = m_mapLogicModules.begin();
	for(; it != m_mapLogicModules.end(); it++)
	{
		it->second->OnInit();
	}

	return true;
}

// ���з������߼�
bool CarGpsServer::StartServer()
{
	// �����߼�ģ��
	std::map<std::string, CarGpsLogic*>::iterator it = m_mapLogicModules.begin();
	for(; it != m_mapLogicModules.end(); it++)
	{
		it->second->OnStart();
	}

	return true;
}

// ������������
bool CarGpsServer::UpdataServer()
{
	// �����߼�ģ��
	std::map<std::string, CarGpsLogic*>::iterator it = m_mapLogicModules.begin();
	for(; it != m_mapLogicModules.end(); it++)
	{
		it->second->OnUpdata();
	}

	return true;
}

// �رշ�����
bool CarGpsServer::EndServer()
{
	// �ر��߼�ģ��
	std::map<std::string, CarGpsLogic*>::iterator it = m_mapLogicModules.begin();
	for(; it != m_mapLogicModules.end(); it++)
	{
		it->second->OnEnd();
	}

	return true;
}
