/*
	gps�������ඨ��
*/
/*
	gps�������ඨ��
*/

#pragma once
#include "../CarGpsSql/CarGpsSql.h"
#include "../CarGpsSocket/CarGpsSocket.h"

class CarGpsServer
{
public:
	CarGpsServer();
	~CarGpsServer();

	// ��ʼ��������
	bool InitServer();

	// ���з������߼�
	bool StartServer();


private:
	CarGpsSql* m_pCarGpsSql; 
	CarGpsSocket* m_pCarGpsSocket;
};
