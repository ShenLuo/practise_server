/*
	gps���ò���
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

// ��ȡInt��������
int TypeVector::GetInt(int nIndex)
{
	if (m_vecInt.size() <= nIndex || nIndex < 0)
	{
		return 0;
	}

	return m_vecInt[nIndex];
}

// ��ȡString��������
const char* TypeVector::GetString(int nIndex)
{
	if (m_vecString.size() <= nIndex || nIndex < 0)
	{
		return "";
	}

	return m_vecString[nIndex].c_str();
}