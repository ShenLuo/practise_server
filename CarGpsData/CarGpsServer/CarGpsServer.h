/*
	gps服务器类定义
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
	// 加载逻辑模块
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

	// 加载逻辑模块消息回调
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

	// 构造函数
	CarGpsServer();
	~CarGpsServer();

	// 运行服务器
	virtual bool RunServer();

private:
	// 服务器线程入口
	virtual void ThreadServer(void* pParam);

	// 注册服务器模块
	virtual bool RegisterServer();

	// 初始化服务器
	virtual bool InitServer();

	// 开始服务器逻辑
	virtual bool StartServer();

	// 服务器运行中
	virtual bool UpdataServer();

	// 关闭服务器
	virtual bool EndServer();

private:
	CarGpsSql* m_pCarGpsSql; 
	CarGpsSocket* m_pCarGpsSocket;


	// 逻辑模块
	std::map<std::string, CarGpsLogic*> m_mapLogicModules;

	// 消息模块
	MapMsgHandle m_mapMsgHandle;

	// 服务器线程
	std::thread m_thread;
};

#endif // _CARGPSSERVER_
