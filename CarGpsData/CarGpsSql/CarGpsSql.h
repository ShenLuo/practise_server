/*
	gps���ݿ����
*/

#pragma once

#include "../CarGpsDef/CarGpsRecordDef.h"
#include <string>
#include <vector>
#include <map>
#include "mysql.h"

class CarGpsSql
{
public:
	// ����mysql����
	CarGpsSql();

	// �ͷ�mysql����
	~CarGpsSql();

	// �������ݿ�����
	bool LoadDataFromDataBase();

	// ��ȡ����˺���Ϣ
	bool GetPlayerByPid(int pid, CarGpsRecPlayer& player);

	// ��ȡ����˺���Ϣ
	bool GetPlayerByName(const char* sName, CarGpsRecPlayer& player);

	// ��ȡ��ҼӰ���Ϣ
	bool  GetPlayerInfo(int pid, std::vector<CarGpsRecPlayerInfo>& playerinfo);

	// �������
	bool SavePlayer(const CarGpsRecPlayer& player);

	// ������ҼӰ���Ϣ
	bool SavePlayerWorkInfo(const CarGpsRecPlayerInfo& playerinfo);

	// �������ݵ����ݿ�
	bool SaveDataToDatabase();

private:
	// ��ȡ�˺ű�
	bool GetPlayerRecordFromDataBase();

	// �����˺ű�
	bool SavePlayerRecordToDataBase();

	// ��ȡ��Ϣ��
	bool GetPlayerInfoRecordFromDataBase();

	// ������Ϣ��
	bool SavePlayerInfoRecordToDataBase();

private:
	// ���ݿ����ݽṹ
	MYSQL m_MySql;

	// ����˺���Ϣ::��������
	std::map<std::string, CarGpsRecPlayer> m_mapPlayerRecName;

	// ����˺���Ϣ::pid����
	std::map<int, CarGpsRecPlayer> m_mapPlayerRecPid;

	// ��ҼӰ���Ϣ
	std::map<int, std::vector<CarGpsRecPlayerInfo>> m_mapPlayerInfoRec;
};