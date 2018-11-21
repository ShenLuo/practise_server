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

	// 保存文件数据
	bool SaveFileData(float x, float y);

private:
	FILE* m_pFile;
	map<string, map<string, string>> m_stFileContent;
};
