/*
	gps服务器类定义
*/
/*
	gps服务器类定义
*/

#ifndef _CARGPSSERVER_
#define _CARGPSSERVER_

#include "../CarGpsSql/CarGpsSql.h"
#include "../CarGpsSocket/CarGpsSocket.h"

class CarGpsSocket;

class CarGpsServer
{
public:
	CarGpsServer();
	~CarGpsServer();

	// 初始化服务器
	bool InitServer();

	// 运行服务器逻辑
	bool StartServer();


private:
	CarGpsSql* m_pCarGpsSql; 
	CarGpsSocket* m_pCarGpsSocket;
};

#endif // _CARGPSSERVER_
