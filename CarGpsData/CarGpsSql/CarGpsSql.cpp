/*
	gps���ݿ����
*/

#include "mysql.h"
#include "CarGpsSql.h"
#include <map>

#define SQLIP "192.168.1.40"
#define SQLWORKSPACE "work_database"
#define SQLNAME "root"
#define SQLPASSWORD "123"
#define SQLPORT 3306

CarGpsSql::CarGpsSql()
{
	if (NULL == mysql_init(&m_MySql))
	{
		return;
	}

	if (NULL == mysql_real_connect(&m_MySql, 
		SQLIP,
		SQLNAME,
		SQLPASSWORD,
		SQLWORKSPACE,
		SQLPORT,
		NULL,
		0))
	{
		return;
	}
}

// �ͷ�mysql����
CarGpsSql::~CarGpsSql()
{
	return;
}

// �������ݿ�����
bool CarGpsSql::LoadDataFromDataBase()
{
	// ������ұ�
	GetPlayerRecordFromDataBase();

	// ���������Ϣ��
	GetPlayerInfoRecordFromDataBase();

	return true;
}

// �������ݵ����ݿ�
bool CarGpsSql::SaveDataToDatabase()
{
	// ������ұ�
	SavePlayerRecordToDataBase();

	// ���������Ϣ��
	SavePlayerInfoRecordToDataBase();

	return true;
}

// ��ȡ����˺���Ϣ
bool CarGpsSql::GetPlayerByPid(int pid, CarGpsRecPlayer& player)
{
	std::map<int, CarGpsRecPlayer>::iterator it = m_mapPlayerRecPid.find(pid);
	if (it == m_mapPlayerRecPid.end())
	{
		return false;
	}

	player.pid = it->second.pid;
	player.name = it->second.name.c_str();
	player.keyword = it->second.keyword.c_str();

	return true;
}

// ��ȡ����˺���Ϣ
bool CarGpsSql::GetPlayerByName(const char* sName, CarGpsRecPlayer& player)
{
	std::map<std::string, CarGpsRecPlayer>::iterator it = m_mapPlayerRecName.find(sName);
	if (it == m_mapPlayerRecName.end())
	{
		return false;
	}

	player.pid = it->second.pid;
	player.name = it->second.name.c_str();
	player.keyword = it->second.keyword.c_str();

	return true;
}

// ��ȡ��ҼӰ���Ϣ
bool  CarGpsSql::GetPlayerInfo(int pid, std::vector<CarGpsRecPlayerInfo>& playerinfo)
{
	std::map<int, std::vector<CarGpsRecPlayerInfo>>::iterator it = m_mapPlayerInfoRec.find(pid);
	if (it == m_mapPlayerInfoRec.end())
	{
		return false;
	}

	for (int i = 0; i < it->second.size(); i++)
	{
		CarGpsRecPlayerInfo temcgpi;
		temcgpi.pid = it->second[i].pid;
		temcgpi.data = it->second[i].data;
		temcgpi.time = it->second[i].time;
		temcgpi.timestage = it->second[i].timestage;

		playerinfo.push_back(temcgpi);
	}

	return true;
}

// �������
bool CarGpsSql::SavePlayer(const CarGpsRecPlayer& player)
{
	if (m_mapPlayerRecPid.find(player.pid) == m_mapPlayerRecPid.end())
	{
		m_mapPlayerRecPid.insert(std::make_pair(player.pid, player));
	}

	if (m_mapPlayerRecName.find(player.name.c_str()) == m_mapPlayerRecName.end())
	{
		m_mapPlayerRecName.insert(std::make_pair(player.name.c_str(), player));
	}

	return true;
}

// ������ҼӰ���Ϣ
bool CarGpsSql::SavePlayerWorkInfo(const CarGpsRecPlayerInfo& playerinfo)
{
	if (m_mapPlayerInfoRec.find(playerinfo.pid) == m_mapPlayerInfoRec.end())
	{
		std::vector<CarGpsRecPlayerInfo> tempvec;
		tempvec.push_back(playerinfo);
		m_mapPlayerInfoRec.insert(std::make_pair(playerinfo.pid, tempvec));
	}
	else
	{
		std::map<int, std::vector<CarGpsRecPlayerInfo>>::iterator it = 
			m_mapPlayerInfoRec.find(playerinfo.pid);
		for (int i = 0; i < it->second.size(); i++)
		{
			if (playerinfo.data == it->second[i].data)
			{
				return false;
			}
		}

		it->second.push_back(playerinfo);
	}

	return true;
}

// ��ȡ�˺ű�
bool CarGpsSql::GetPlayerRecordFromDataBase()
{
	mysql_query(&m_MySql, "select * from player;");

	MYSQL_RES* mysqlresult = mysql_store_result(&m_MySql);
	if (NULL == mysqlresult)
	{
		return false;
	}

	int nRows = mysql_num_rows(mysqlresult);
	int nCols =  mysql_num_fields(mysqlresult);
	for (int i = 0; i < nRows; i++)
	{
		MYSQL_ROW mysqlRow = mysql_fetch_row(mysqlresult);
		if (NULL == mysqlRow)
		{
			continue;
		}

		CarGpsRecPlayer tempCGRP;
		tempCGRP.name = mysqlRow[EnumCarGpsRecPlayer_Name];
		tempCGRP.keyword = mysqlRow[EnumCarGpsRecPlayer_KeyWord];
		tempCGRP.pid = atoi(mysqlRow[EnumCarGpsRecPlayer_Pid]);
		
		// pid����
		m_mapPlayerRecPid.insert(std::make_pair(tempCGRP.pid, tempCGRP));

		// ��������
		m_mapPlayerRecName.insert(std::make_pair(tempCGRP.name, tempCGRP));
	}

	mysql_free_result(mysqlresult);

	return true;
}

// �����˺ű�
bool CarGpsSql::SavePlayerRecordToDataBase()
{
// 	std::map<int, CarGpsRecPlayer>::iterator it = m_mapPlayerRecPid.begin();
// 	for (; it != m_mapPlayerRecPid.end(); it++)
// 	{
// 		if (it->second.needsave)
// 		{
// 			// �޸Ĺ���������Ҫ����Ĳű��浽���ݿ�
// 			std::string sqlstr = "insert into player values ";
// 			sqlstr += "(";
// 			sqlstr += it->second.name.c_str();
// 			sqlstr += it->second.keyword.c_str();
// 			sqlstr += it->second.pid;
// 			sqlstr += ");";

			std::string sqlstr = "insert into player values ('123', 'abc', 123)";
			int nRes = mysql_query(&m_MySql, sqlstr.c_str());

			if (mysql_affected_rows(&m_MySql) > 0)
			{
				// ���ó��ѱ���
				//it->second.needsave = false;
			}
		/*}*/
	/*}*/

	return true;
}

// ��ȡ��Ϣ��
bool CarGpsSql::GetPlayerInfoRecordFromDataBase()
{
	mysql_query(&m_MySql, "select * from player_info;");

	MYSQL_RES* mysqlresult = mysql_store_result(&m_MySql);
	if (NULL == mysqlresult)
	{
		return false;
	}

	int nRows = mysql_num_rows(mysqlresult);
	int nCols =  mysql_num_fields(mysqlresult);
	for (int i = 0; i < nRows; i++)
	{
		MYSQL_ROW mysqlRow = mysql_fetch_row(mysqlresult);
		if (NULL == mysqlRow)
		{
			continue;
		}

		CarGpsRecPlayerInfo tempCGRPI;
		tempCGRPI.pid = atoi(mysqlRow[EnumCarGpsRecPlayerInfo_Pid]);
		tempCGRPI.data = atoi(mysqlRow[EnumCarGpsRecPlayerInfo_Data]);
		tempCGRPI.time = atoi(mysqlRow[EnumCarGpsRecPlayerInfo_Time]);
		tempCGRPI.timestage = atof(mysqlRow[EnumCarGpsRecPlayerInfo_TimeStage]);
		std::map<int, std::vector<CarGpsRecPlayerInfo>>::iterator it = 
			m_mapPlayerInfoRec.find(tempCGRPI.pid);

		if (it == m_mapPlayerInfoRec.end())
		{
			// ���
			std::vector<CarGpsRecPlayerInfo> vecTemp;
			vecTemp.push_back(tempCGRPI);
			m_mapPlayerInfoRec.insert(std::make_pair(tempCGRPI.pid, vecTemp));
		}
		else
		{
			it->second.push_back(tempCGRPI);
		}	
	}

	mysql_free_result(mysqlresult);

	return true;
}

// ������Ϣ��
bool CarGpsSql::SavePlayerInfoRecordToDataBase()
{
	std::map<int, std::vector<CarGpsRecPlayerInfo>>::iterator it = 
						m_mapPlayerInfoRec.begin();
	for (; it != m_mapPlayerInfoRec.end(); it++)
	{
		for (int i = 0 ; i < it->second.size(); i++)
		{
			if (it->second[i].needsave)
			{
				// �޸Ĺ���������Ҫ����Ĳű��浽���ݿ�
				std::string sqlstr = "insert into player_info values ";
				sqlstr += "(";
				sqlstr += it->second[i].pid;
				sqlstr += it->second[i].data;
				sqlstr += it->second[i].time;
				sqlstr += it->second[i].timestage;
				sqlstr += ");";
				mysql_query(&m_MySql, sqlstr.c_str());

				if (mysql_affected_rows(&m_MySql) > 0)
				{
					// ���ó��ѱ���
					it->second[i].needsave = false;
				}
			}
		}
	}

	return true;
}