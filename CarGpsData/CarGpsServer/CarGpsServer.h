/*
	gps�������ඨ��
*/
/*
	gps�������ඨ��
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

	// ��ʼ��������
	bool InitServer();

	// ���з������߼�
	bool StartServer();


private:
	CarGpsSql* m_pCarGpsSql; 
	CarGpsSocket* m_pCarGpsSocket;
};

#endif // _CARGPSSERVER_
