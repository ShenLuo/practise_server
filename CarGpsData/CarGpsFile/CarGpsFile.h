/*
	gps�����ļ�����
*/

#ifndef _CARGPSFILE_
#define _CARGPSFILE_

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

	string getStringVal(char* sSec , char*sItem);
	int getIntVal(char* sSec , char*sItem);

private:
	int stringToInt(const char* sStr);

private:
	string m_sFileName;
	map<string, map<string, string>> m_stFileContent;
};

#endif // _CARGPSFILE_
