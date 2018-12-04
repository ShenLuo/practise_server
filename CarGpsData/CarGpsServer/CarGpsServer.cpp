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

// 初始化服务器
bool CarGpsServer::InitServer()
{
	m_pCarGpsSql = new CarGpsSql;
	m_pCarGpsSocket = new CarGpsSocket(this);
	return true;
}

// 运行服务器逻辑
bool CarGpsServer::StartServer()
{
	return true;
}
