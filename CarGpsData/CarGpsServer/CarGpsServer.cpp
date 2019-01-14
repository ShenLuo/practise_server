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
	//m_thread = thread(std::bind(&CarGpsServer::ThreadServer, this));
	m_thread = std::thread(&CarGpsServer::ThreadServer, this, nullptr);
	//std::thread temp = std::move(m_thread);
	m_thread.join();
	return true;
}

// 服务器线程入口
void CarGpsServer::ThreadServer(void* pParam)
{
	RegisterServer();
	InitServer();
	StartServer();
	UpdataServer();
}

// 注册服务器模块
bool CarGpsServer::RegisterServer()
{
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
	while (true)
	{
		// 运行逻辑模块
		std::map<std::string, CarGpsLogic*>::iterator it = m_mapLogicModules.begin();
		for(; it != m_mapLogicModules.end(); it++)
		{
			it->second->OnUpdata();
		}
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
