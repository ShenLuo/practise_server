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
