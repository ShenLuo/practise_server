/*
	gps数据文件操作
*/

#ifndef _CARGPSFILE_
#define _CARGPSFILE_

#include <stdio.h>
#include <string>
#include <map>

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
	std::map<std::string, std::map<std::string, std::string>> m_stFileContent;
};

#endif // _CARGPSFILE_
