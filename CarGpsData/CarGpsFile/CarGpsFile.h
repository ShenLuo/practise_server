/*
	gps�����ļ�����
*/

#pragma once
#include <stdio.h>
#include <string>
#include <map>

using namespace std;

class CarGpsDataFile
{
public:
	// �����ļ�
	CarGpsDataFile(const char* pFileName);
	~CarGpsDataFile();

	// ���������ļ�
	void loadFile();

	std::string getStringVal(char* sSec , char*sItem);
	int getIntVal(char* sSec , char*sItem);

private:
	int stringToInt(const char* sStr);

private:
	std::string m_sFileName;
	map<string, map<string, string>> m_stFileContent;
};
