/*
	gps公用操作
*/

#pragma once

#include <vector>
#include <string>

class TypeVector
{
public:
	// 初始化数据
	TypeVector(const char* sinfo);

	// 释放数据
	~TypeVector();


	// 获取Int类型数据
	int GetInt(int nIndex);

	// 获取String类型数据
	const char* GetString(int nIndex);

private:
	std::vector<int> m_vecInt;
	std::vector<std::string> m_vecString;
};

