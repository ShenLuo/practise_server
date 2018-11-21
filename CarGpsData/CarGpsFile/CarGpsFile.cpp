/*
	gps数据文件操作
*/

#include "CarGpsFile.h"
#include "../CarGpsDef/CarGpsCommonDef.h"
#include <time.h>
#include <stdio.h>
#include<io.h>
#include <map>

CarGpsDataFile::CarGpsDataFile(const char* pFileName)
{
	m_sFileName = pFileName;
}
	
CarGpsDataFile::~CarGpsDataFile()
{
}

// 加载文件
void CarGpsDataFile::loadFile()
{
	if (strcmp("", m_sFileName.c_str()) == 0)
	{
		return;
	}

	FILE* file = fopen(m_sFileName.c_str(), "r");
	if (NULL == file)
	{
		return;
	}

	// 文件开头
	fseek(file, 0, SEEK_SET);

	char temid[32] = "";
	char temItemid[32] = "";
	char temItemval[1024] = "";
	char temp = 0;

	m_stFileContent.clear();
	std::map<string, string> temItem;
	temItem.clear();

	bool bSection = false;
	int nChaCSectionTitle = 0;
	bool bSectionItem = false;
	int nCharCItemTitle = 0;
	bool bSetcionItemContent = false;
	int nCharCSItemContent = 0;

	int tempInt = 0;

	while ((temp = fgetc(file)) != EOF)
	{
		tempInt = ftell(file);
		if(temp == '[')
		{
			// 保存上一个段落
			if (strcmp(temid, "") != 0)
			{
				m_stFileContent.insert(std::make_pair(temid, temItem));
			}

			// 初始每个段落
			bSection = true, bSectionItem = false, bSetcionItemContent = false;
			nChaCSectionTitle = 0, nCharCItemTitle = 0, nCharCSItemContent = 0;
			temItem.clear();
			memset(temid, 0, sizeof(temid));
			memset(temItemid, 0, sizeof(temItemid));
			memset(temItemval, 0, sizeof(temItemval));
		}
		else if (temp == ']')
		{
			bSection =false;
			fseek(file, (-1 - nChaCSectionTitle), SEEK_CUR);
			fgets(temid, nChaCSectionTitle + 1, file);
			fseek(file, 1, SEEK_CUR);
			nChaCSectionTitle = 0;
			bSectionItem = true;
		}
		else if (temp == '=')
		{
			bSectionItem =false;
			fseek(file, (-1 - nCharCItemTitle), SEEK_CUR);
			fgets(temItemid, nCharCItemTitle + 1, file);
			fseek(file, 1, SEEK_CUR);
			nCharCItemTitle = 0;
			bSetcionItemContent = true;
		}
		else if (bSetcionItemContent && (temp == '\n'))
		{
			nCharCSItemContent ++;/*windows中文本文件的换行是\r\n*/

			tempInt = ftell(file);
			bSetcionItemContent = false;
			fseek(file, (-1 - nCharCSItemContent), SEEK_CUR);
			fgets(temItemval, nCharCSItemContent, file);
			tempInt = ftell(file);
			fseek(file, 2, SEEK_CUR);
			tempInt = ftell(file);
			nCharCSItemContent = 0;
			temItem.insert(std::make_pair(temItemid, temItemval));
			memset(temItemid, 0, sizeof(temItemid));
			memset(temItemval, 0, sizeof(temItemval));
			bSectionItem = true;
		}
		else
		{
			if (bSection)
			{
				// 短标题字符数+1
				nChaCSectionTitle++;
			}
			else if (bSectionItem)
			{
				// 段的条目标题字符数+1
				if (temp != '\n' && temp != ' ' && temp != '	')
				{
					nCharCItemTitle++;
				}
			}
			else if (bSetcionItemContent)
			{
				// 段的条目内容字符数+1
				if (temp != '\n' && temp != ' ' && temp != '	')
				{
					nCharCSItemContent++;
				}
			}
		}
	}

	if (strcmp(temid, "") != 0)
	{
		// 保存最后一段
		m_stFileContent.insert(std::make_pair(temid, temItem));
	}

	// 关闭文件
	fclose(file);
}

std::string CarGpsDataFile::getStringVal(char* sSec , char*sItem)
{
	map<string, map<string, string>>::iterator it = m_stFileContent.find(sSec);
	if (it == m_stFileContent.end())
	{
		return "";
	}

	std::map<string, string>::iterator it_item = it->second.find(sItem);
	if (it_item == it->second.end())
	{
		return "";
	}

	return it_item->second.c_str();
}

int CarGpsDataFile::getIntVal(char* sSec , char*sItem)
{
	map<string, map<string, string>>::iterator it = m_stFileContent.find(sSec);
	if (it == m_stFileContent.end())
	{
		return MagicNum0;
	}

	std::map<string, string>::iterator it_item = it->second.find(sItem);
	if (it_item == it->second.end())
	{
		return MagicNum0;
	}

	return stringToInt(it_item->second.c_str());
}

int CarGpsDataFile::stringToInt(const char* sStr)
{
	if (strcmp("", sStr) == 0)
	{
		return MagicNum0;
	}

	std::string tempStr = sStr;
	char* temp = tempStr.c_str();
	int tempI = 0;
	while (*temp != 0)
	{
		if (*temp <= '0' && *temp <= '9')
		{
			tempI = tempI * 10 + *temp - '0';
		}

		temp += 1;
	}

	return tempI;
}



