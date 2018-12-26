/*
	gps服务器类定义
*/

#ifndef _CARGPSSERVER_
#define _CARGPSSERVER_

#include "../CarGpsSql/CarGpsSql.h"
#include "../CarGpsSocket/CarGpsSocket.h"
#include "../CarGpsLogic/CarGpsLogic.h"
#include "../CarGpsCommon/CarGpsCommon.h"

class CarGpsSocket;

class CarGpsServer
{
public:
	CarGpsServer();
	~CarGpsServer();

	// 初始化服务器
	bool InitServer();

	// 运行服务器逻辑
	bool StartServer();

	// 关闭服务器
	bool EndServer();

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
	template<typename HandleType>
	class HandleClass
	{
	public:
		static void HandleMsg(void* handle)
		{
			((HandleType*)handle)();
		}
	};

	typedef void(*HANDLESTATICFUNC)(void*);

	struct HandleWraple
	{
		HANDLESTATICFUNC handleStaticFunc;
		void* handleBind;
	};

	template<typename HandleType>
	bool RegisterMsgHandle(HandleType handle)
	{

	}

private:
	CarGpsSql* m_pCarGpsSql; 
	CarGpsSocket* m_pCarGpsSocket;


	// 逻辑模块
	std::map<std::string, CarGpsLogic*> m_mapLogicModules;
};

#endif // _CARGPSSERVER_
