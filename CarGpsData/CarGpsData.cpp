/*
	功能：加班管理系统
	作者：MrDuck(LuoShen)
	时间：2017/08/17
*/

#include "stdafx.h"
#include "CarGpsFile/CarGpsFile.h"
#include "CarGpsSocket/CarGpsSocket.h"
#include "CarGpsUtilFunc/CarGpsUtil.h"
#include "CarGpsDef/CarGpsMsgDef.h"
#include "CarGpsSql/CarGpsSql.h"
#include <time.h>

// 玩家注册
bool PlayerSignIn(TypeVector& tyv)
{

	return true;
}

// 玩家登陆
bool PlayerLoginIn(TypeVector& tyv)
{
	return true;
}

// 玩家下班
bool PlayerLoginOut(TypeVector& tyv)
{
	return true;

}

// 线程函数
int HandleStuffMsg(void* sParamter)
{
	SOCKET* pSocket = (SOCKET*)sParamter;
	if (NULL == pSocket || *pSocket == INVALID_SOCKET || *pSocket == SOCKET_ERROR)
	{
		return 0;
	}

	while (true)
	{
		char charTemp[128] = {0};
		if (recv(*pSocket, charTemp, sizeof(charTemp), 0) >= 0)
		{
			TypeVector temp(charTemp);
			std::string sMsgTitle = temp.GetString(0);
			if (strcmp(sMsgTitle.c_str(), MSG_CLIENT_TO_SERVER_SIGNIN) == 0)
			{
				// 玩家注册
				if (PlayerSignIn(temp))
				{
					send(*pSocket, MSG_SERVER_TO_CLIENT_SUCCESS_SIGNIN, 128, 0);
				}
			}
			else if (strcmp(sMsgTitle.c_str(), MSG_CLIENT_TO_SERVER_LOGININ) == 0)
			{
				// 玩家登陆
				if (PlayerLoginIn(temp))
				{
					// 成功登陆
					send(*pSocket, MSG_SERVER_TO_CLIENT_SUCCESS_LOGININ, 128, 0);

					// 往期信息
					send(*pSocket, MSG_SERVER_TO_CLIENT_WORKDATA, 128, 0);
				}
			}
			else if (strcmp(sMsgTitle.c_str(), MSG_CLIENT_TO_SERVER_LOGINOUT) == 0)
			{
				// 玩家下班
				if (PlayerLoginOut(temp))
				{
					send(*pSocket, MSG_SERVER_TO_CLIENT_SUCCESS_LOGINOUT, 128, 0);
				}
			}
		}
	}

	return 0;
}

CarGpsSql mysql;

// 服务器数据库操作线程
int HandleDatabase(void* lpParmate)
{
	// 加载数据库
	mysql.LoadDataFromDataBase();

	// 定时保存数据库
	time_t pre_time = 0;
	time(&pre_time);

	while (true)
	{
		time_t cur_time = 0;
		time(&cur_time);

		if (cur_time - pre_time >= 5)
		{
			// 每秒执行一次
			mysql.SaveDataToDatabase();
			pre_time = cur_time;
		}
	}
}

int g_nSockIndex = 0;
SOCKET g_sock[100] = {0};
int g_nInstanceIndex = 0;
unsigned long g_instance[100] = {0};

// 主函数
int _tmain(int argc, _TCHAR* argv[])
{
	// 创建服务器数据库操作线程
	unsigned long nThreadIDDatabase;
	CreateThread(NULL, 0, 
		(LPTHREAD_START_ROUTINE)HandleDatabase, 0, 0, &nThreadIDDatabase);

	// 创建服务器网络操作线程
	{
		CarGpsSocket carSockTep;
		carSockTep.SocketBind(AF_INET, "192.168.1.40", 6677);
		carSockTep.SocketListen(100);

		// 接受客户端的连接
		while (true)
		{
			sockaddr soAddr;
			int nSoAddr = sizeof(soAddr);

			// 处理员工操作
			if(carSockTep.SocketAccept(g_sock[g_nSockIndex], soAddr, nSoAddr))
			{
				CreateThread(NULL, 0, 
					(LPTHREAD_START_ROUTINE)HandleStuffMsg,
					&g_sock[g_nSockIndex], 0, &g_instance[g_nInstanceIndex]);

				g_nInstanceIndex++;
				g_nSockIndex++;
			}
		}
	}
	

	return 0;
}

