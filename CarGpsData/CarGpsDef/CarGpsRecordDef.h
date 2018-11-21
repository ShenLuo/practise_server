/*
	CarGps数据表结构定义
*/

#pragma once
#include <string>

// 玩家账号
struct  CarGpsRecPlayer
{
	std::string name;
	std::string keyword;
	int pid;
	bool needsave;

	CarGpsRecPlayer()
	{
		name = "";
		keyword = "";
		pid = 0;
		needsave = false;
	}
};

enum EnumCarGpsRecPlayer
{
	EnumCarGpsRecPlayer_Name = 0,
	EnumCarGpsRecPlayer_KeyWord = 1,
	EnumCarGpsRecPlayer_Pid = 2,
};

// 玩家信息
struct  CarGpsRecPlayerInfo
{
	int pid;
	int data;
	int time;
	float timestage; 
	bool needsave;

	CarGpsRecPlayerInfo()
	{
		pid = -1;
		data = 0;
		time = 0;
		timestage = 0;
		needsave = false;
	}
};

enum EnumCarGpsRecPlayerInfo
{
	EnumCarGpsRecPlayerInfo_Pid = 0,
	EnumCarGpsRecPlayerInfo_Data = 1,
	EnumCarGpsRecPlayerInfo_Time = 2,
	EnumCarGpsRecPlayerInfo_TimeStage = 3,
};

