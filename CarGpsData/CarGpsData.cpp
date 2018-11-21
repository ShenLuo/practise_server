/*
	���ܣ��Ӱ����ϵͳ
	���ߣ�MrDuck(LuoShen)
	ʱ�䣺2017/08/17
*/

#include "stdafx.h"
#include "CarGpsFile/CarGpsFile.h"
#include "CarGpsSocket/CarGpsSocket.h"
#include "CarGpsUtilFunc/CarGpsUtil.h"
#include "CarGpsDef/CarGpsMsgDef.h"
#include "CarGpsSql/CarGpsSql.h"
#include <time.h>

// ���ע��
bool PlayerSignIn(TypeVector& tyv)
{

	return true;
}

// ��ҵ�½
bool PlayerLoginIn(TypeVector& tyv)
{
	return true;
}

// ����°�
bool PlayerLoginOut(TypeVector& tyv)
{
	return true;

}

// �̺߳���
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
				// ���ע��
				if (PlayerSignIn(temp))
				{
					send(*pSocket, MSG_SERVER_TO_CLIENT_SUCCESS_SIGNIN, 128, 0);
				}
			}
			else if (strcmp(sMsgTitle.c_str(), MSG_CLIENT_TO_SERVER_LOGININ) == 0)
			{
				// ��ҵ�½
				if (PlayerLoginIn(temp))
				{
					// �ɹ���½
					send(*pSocket, MSG_SERVER_TO_CLIENT_SUCCESS_LOGININ, 128, 0);

					// ������Ϣ
					send(*pSocket, MSG_SERVER_TO_CLIENT_WORKDATA, 128, 0);
				}
			}
			else if (strcmp(sMsgTitle.c_str(), MSG_CLIENT_TO_SERVER_LOGINOUT) == 0)
			{
				// ����°�
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

// ���������ݿ�����߳�
int HandleDatabase(void* lpParmate)
{
	// �������ݿ�
	mysql.LoadDataFromDataBase();

	// ��ʱ�������ݿ�
	time_t pre_time = 0;
	time(&pre_time);

	while (true)
	{
		time_t cur_time = 0;
		time(&cur_time);

		if (cur_time - pre_time >= 5)
		{
			// ÿ��ִ��һ��
			mysql.SaveDataToDatabase();
			pre_time = cur_time;
		}
	}
}

int g_nSockIndex = 0;
SOCKET g_sock[100] = {0};
int g_nInstanceIndex = 0;
unsigned long g_instance[100] = {0};

// ������
int _tmain(int argc, _TCHAR* argv[])
{
	// �������������ݿ�����߳�
	unsigned long nThreadIDDatabase;
	CreateThread(NULL, 0, 
		(LPTHREAD_START_ROUTINE)HandleDatabase, 0, 0, &nThreadIDDatabase);

	// ������������������߳�
	{
		CarGpsSocket carSockTep;
		carSockTep.SocketBind(AF_INET, "192.168.1.40", 6677);
		carSockTep.SocketListen(100);

		// ���ܿͻ��˵�����
		while (true)
		{
			sockaddr soAddr;
			int nSoAddr = sizeof(soAddr);

			// ����Ա������
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

