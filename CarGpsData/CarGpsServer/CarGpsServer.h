/*
	gps�������ඨ��
*/

#ifndef _CARGPSSERVER_
#define _CARGPSSERVER_

#include "../CarGpsSql/CarGpsSql.h"
#include "../CarGpsSocket/CarGpsSocket.h"
#include "../CarGpsLogic/CarGpsLogic.h"
#include <thread>

class CarGpsSocket;
class CarGpsSql;

//using namespace std;

class CarGpsServer
{
public:
	// �����߼�ģ��
	template <typename LogicModuleType>
	bool RegisterLogicModule()
	{
		CarGpsLogic* logic = new LogicModuleType;
		if (NULL == logic)
		{
			LogInfo("");
			return false;
		}

		const char* logicName = logic->GetLogicName();
		if (strcmp("", logicName) == 0)
		{
			LogInfo("");
			return false;
		}

		m_mapLogicModules.insert(std::make_pair(logicName, logic));
		return true;
	}

	// �����߼�ģ����Ϣ�ص�
	class MsgPriority
	{
	public:
		MsgPriority(int value)
		{
			nPriority = value;
		}

		bool operator< (MsgPriority msgp)
		{
			return msgp.nPriority < nPriority;
		}

	private:
		int nPriority;
	};

	template<typename HandleType>
	class HandleClass
	{
	public:
		HandleClass(HandleType&& handle)
		{
			mhandle = handle;
		}

		static void HandleMsg(void* handleclass)
		{
			((HandleClass*)handleclass)->mhandle();
		}

	private:
		HandleType mhandle;
	};

	typedef void(*HANDLESTATICFUNC)(void*);

	struct HandleWraple
	{
		HANDLESTATICFUNC handleStaticFunc;
		void* handleBind;
	};

	typedef std::map<MsgPriority,HandleWraple> MapHandle;
	typedef std::map<int,MapHandle> MapMsgHandle;

	template<typename HandleType>
	bool RegisterMsgHandle(int msgid, HandleType handle, int priority = 1)
	{
		HandleClass handleclass = new HandleClass<HandleType>(handle);
		if (NULL == handleclass)
		{
			LogInfo("");
			return false;
		}

		HandleWraple handlewraple;
		handlewraple.handleStaticFunc = &handleclass::HandleMsg;
		handlewraple = &handleclass;

		MapMsgHandle::iterator it = m_mapMsgHandle.find(msgid);
		if (it == m_mapMsgHandle.end())
		{
			it->second.insert(std::make_pair(MsgPriority(priority), handlewraple));
		}
		else
		{
			MapHandle temp;
			temp.insert(std::make_pair(MsgPriority(priority), handlewraple));
			m_mapMsgHandle.insert(std::make_pair(msgid, temp));
		}

		LogInfo("");
		return true;
	}

	// ���캯��
	CarGpsServer();
	~CarGpsServer();

	// ���з�����
	virtual bool RunServer();

private:
	// �������߳����
	virtual void ThreadServer(void* pParam);

	// ע�������ģ��
	virtual bool RegisterServer();

	// ��ʼ��������
	virtual bool InitServer();

	// ��ʼ�������߼�
	virtual bool StartServer();

	// ������������
	virtual bool UpdataServer();

	// �رշ�����
	virtual bool EndServer();

private:
	CarGpsSql* m_pCarGpsSql; 
	CarGpsSocket* m_pCarGpsSocket;


	// �߼�ģ��
	std::map<std::string, CarGpsLogic*> m_mapLogicModules;

	// ��Ϣģ��
	MapMsgHandle m_mapMsgHandle;

	// �������߳�
	std::thread m_thread;
};

#endif // _CARGPSSERVER_
