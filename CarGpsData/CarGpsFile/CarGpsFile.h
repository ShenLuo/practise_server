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

	// �����ļ�����
	bool SaveFileData(float x, float y);

private:
	FILE* m_pFile;
	map<string, map<string, string>> m_stFileContent;
};
