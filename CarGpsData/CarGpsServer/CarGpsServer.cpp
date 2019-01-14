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
	//m_thread = thread(std::bind(&CarGpsServer::ThreadServer, this));
	m_thread = std::thread(&CarGpsServer::ThreadServer, this, nullptr);
	//std::thread temp = std::move(m_thread);
	m_thread.join();
	return true;
}

// �������߳����
void CarGpsServer::ThreadServer(void* pParam)
{
	RegisterServer();
	InitServer();
	StartServer();
	UpdataServer();
}

// ע�������ģ��
bool CarGpsServer::RegisterServer()
{
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
	while (true)
	{
		// �����߼�ģ��
		std::map<std::string, CarGpsLogic*>::iterator it = m_mapLogicModules.begin();
		for(; it != m_mapLogicModules.end(); it++)
		{
			it->second->OnUpdata();
		}
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
