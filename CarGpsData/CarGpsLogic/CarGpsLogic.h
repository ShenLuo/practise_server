/*
	gps服务器中功能模块类定义
*/

#ifndef _CARGPSLOGIC_
#define _CARGPSLOGIC_

class CarGpsLogic
{
public:
	CarGpsLogic();
	~CarGpsLogic();

	char* GetLogicName(){return "";}
	bool OnInit(){return true;}
	bool OnStart(){return true;}
	bool OnEnd(){return true;}
private:

};

#endif // _CARGPSLOGIC_

