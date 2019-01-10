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
	virtual bool OnInit(){return true;}
	virtual bool OnStart(){return true;}
	virtual bool OnUpdata(){return true;}
	virtual bool OnEnd(){return true;}
private:

};

#endif // _CARGPSLOGIC_

