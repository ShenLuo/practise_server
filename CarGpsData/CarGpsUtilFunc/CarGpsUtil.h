/*
	gps���ò���
*/

#pragma once

#include <vector>
#include <string>

class TypeVector
{
public:
	// ��ʼ������
	TypeVector(const char* sinfo);

	// �ͷ�����
	~TypeVector();


	// ��ȡInt��������
	int GetInt(int nIndex);

	// ��ȡString��������
	const char* GetString(int nIndex);

private:
	std::vector<int> m_vecInt;
	std::vector<std::string> m_vecString;
};

