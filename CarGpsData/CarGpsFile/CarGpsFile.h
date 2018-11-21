/*
	gps数据文件操作
*/

#pragma once
#include <stdio.h>
#include <string>
#include <map>

using namespace std;

class CarGpsDataFile
{
public:
	// 创建文件
	CarGpsDataFile(const char* pFileName);
	~CarGpsDataFile();

	// 加载配置文件
	void loadFile();

	std::string getStringVal(char* sSec , char*sItem);
	int getIntVal(char* sSec , char*sItem);

private:
	int stringToInt(const char* sStr);

private:
	std::string m_sFileName;
	map<string, map<string, string>> m_stFileContent;
};
