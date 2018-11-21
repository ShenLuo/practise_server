/*
	gps数据库操作
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
	// 建立mysql连接
	CarGpsSql();

	// 释放mysql连接
	~CarGpsSql();

	// 加载数据库数据
	bool LoadDataFromDataBase();

	// 获取玩家账号信息
	bool GetPlayerByPid(int pid, CarGpsRecPlayer& player);

	// 获取玩家账号信息
	bool GetPlayerByName(const char* sName, CarGpsRecPlayer& player);

	// 获取玩家加班信息
	bool  GetPlayerInfo(int pid, std::vector<CarGpsRecPlayerInfo>& playerinfo);

	// 保存玩家
	bool SavePlayer(const CarGpsRecPlayer& player);

	// 保存玩家加班信息
	bool SavePlayerWorkInfo(const CarGpsRecPlayerInfo& playerinfo);

	// 保存数据到数据库
	bool SaveDataToDatabase();

private:
	// 读取账号表
	bool GetPlayerRecordFromDataBase();

	// 保存账号表
	bool SavePlayerRecordToDataBase();

	// 读取信息表
	bool GetPlayerInfoRecordFromDataBase();

	// 保存信息表
	bool SavePlayerInfoRecordToDataBase();

private:
	// 数据库数据结构
	MYSQL m_MySql;

	// 玩家账号信息::姓名索引
	std::map<std::string, CarGpsRecPlayer> m_mapPlayerRecName;

	// 玩家账号信息::pid索引
	std::map<int, CarGpsRecPlayer> m_mapPlayerRecPid;

	// 玩家加班信息
	std::map<int, std::vector<CarGpsRecPlayerInfo>> m_mapPlayerInfoRec;
};