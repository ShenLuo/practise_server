/*
	gps服务器类定义
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

// 初始化服务器
bool CarGpsServer::InitServer()
{
	m_pCarGpsSql = new CarGpsSql;
	m_pCarGpsSocket = new CarGpsSocket(this);

	// 初始化逻辑模块
	std::map<std::string, CarGpsLogic*>::iterator it = m_mapLogicModules.begin();
	for(; it != m_mapLogicModules.end(); it++)
	{
		it->second->OnInit();
	}

	return true;
}

// 运行服务器逻辑
bool CarGpsServer::StartServer()
{
	// 运行逻辑模块
	std::map<std::string, CarGpsLogic*>::iterator it = m_mapLogicModules.begin();
	for(; it != m_mapLogicModules.end(); it++)
	{
		it->second->OnStart();
	}

	return true;
}

// 服务器运行中
bool CarGpsServer::UpdataServer()
{
	// 运行逻辑模块
	std::map<std::string, CarGpsLogic*>::iterator it = m_mapLogicModules.begin();
	for(; it != m_mapLogicModules.end(); it++)
	{
		it->second->OnUpdata();
	}

	return true;
}

// 关闭服务器
bool CarGpsServer::EndServer()
{
	// 关闭逻辑模块
	std::map<std::string, CarGpsLogic*>::iterator it = m_mapLogicModules.begin();
	for(; it != m_mapLogicModules.end(); it++)
	{
		it->second->OnEnd();
	}

	return true;
}
