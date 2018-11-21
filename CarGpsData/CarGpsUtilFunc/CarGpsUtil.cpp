/*
	gps公用操作
*/

#include "CarGpsUtil.h"

TypeVector::TypeVector(const char* sinfo)
{
	if (NULL == sinfo)
	{
		return;
	}

	std::string temp = "";
	for (const char* cbegin = sinfo; *cbegin != '\0'; cbegin++)
	{
		if (*cbegin != '|') 
		{
			temp += *cbegin;
		}
		else
		{
			m_vecString.push_back(temp.c_str());
			temp = "";
		}
	}
		
	return;
}

TypeVector::~TypeVector()
{

}

// 获取Int类型数据
int TypeVector::GetInt(int nIndex)
{
	if (m_vecInt.size() <= nIndex || nIndex < 0)
	{
		return 0;
	}

	return m_vecInt[nIndex];
}

// 获取String类型数据
const char* TypeVector::GetString(int nIndex)
{
	if (m_vecString.size() <= nIndex || nIndex < 0)
	{
		return "";
	}

	return m_vecString[nIndex].c_str();
}