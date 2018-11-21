/*
	gps数据文件操作
*/

#include "CarGpsFile.h"
#include <time.h>
#include <stdio.h>
#include<io.h>
#include <map>

CarGpsDataFile::CarGpsDataFile(const char* pFileName)
{
	m_pFile = NULL;

	if (NULL != pFileName)
	{
		m_pFile = fopen(pFileName, "r");


// 		if (m_pFile)
// 		{
// 			time_t nNow;
// 			time(&nNow);
// 			tm* tmTemp = localtime(&nNow);
// 			char cTime[128] = {0};
// 			sprintf_s(cTime, "Time:Year-%d,Month-%d,Day-%d,Hour-%d,Minute-%d,Second-%d\n", 
// 				tmTemp->tm_year + 1900, tmTemp->tm_mon + 1,
// 				tmTemp->tm_mday, tmTemp->tm_hour,
// 				tmTemp->tm_min, tmTemp->tm_sec);
// 
// 			int nCount = fputs(cTime, m_pFile);
// 			fflush(m_pFile);
// 		}
	}
}
	
CarGpsDataFile::~CarGpsDataFile()
{
	if (m_pFile)
	{
		fclose(m_pFile);
	}
}

// 加载文件
void CarGpsDataFile::loadFile()
{
	if (NULL == m_pFile)
	{
		return;
	}

	// 文件开头
	fseek(m_pFile, 0, SEEK_SET);

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

	while ((temp = fgetc(m_pFile)) != EOF)
	{
		tempInt = ftell(m_pFile);
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
			fseek(m_pFile, (-1 - nChaCSectionTitle), SEEK_CUR);
			fgets(temid, nChaCSectionTitle + 1, m_pFile);
			fseek(m_pFile, 1, SEEK_CUR);
			nChaCSectionTitle = 0;
			bSectionItem = true;
		}
		else if (temp == '=')
		{
			bSectionItem =false;
			fseek(m_pFile, (-1 - nCharCItemTitle), SEEK_CUR);
			fgets(temItemid, nCharCItemTitle + 1, m_pFile);
			fseek(m_pFile, 1, SEEK_CUR);
			nCharCItemTitle = 0;
			bSetcionItemContent = true;
		}
		else if (bSetcionItemContent && (temp == '\n'))
		{
			nCharCSItemContent ++;/*windows中文本文件的换行是\r\n*/

			tempInt = ftell(m_pFile);
			bSetcionItemContent = false;
			fseek(m_pFile, (-1 - nCharCSItemContent), SEEK_CUR);
			fgets(temItemval, nCharCSItemContent, m_pFile);
			tempInt = ftell(m_pFile);
			fseek(m_pFile, 2, SEEK_CUR);
			tempInt = ftell(m_pFile);
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
}

// 保存文件数据
bool CarGpsDataFile::SaveFileData(float x, float y)
{
	if (m_pFile)
	{
		char cTime[128] = {0};
		sprintf_s(cTime, "Pos:X=%f, Y=%f\n", x, y);
		fputs(cTime, m_pFile);
		fflush(m_pFile);
	}

	return true;
}

