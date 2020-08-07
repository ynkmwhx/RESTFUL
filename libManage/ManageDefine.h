
#ifndef _MANAGE_DEFINE_H
#define _MANAGE_DEFINE_H
#include <iostream>
typedef enum {
	STOPED,
	HALT,
	SERVING
}SYSTEM_STATUS;

typedef enum {
	QueryOrder = 1001,
	QueryAGVInfo = 1002,
	QueryWeightInfo = 1003
}QUERY_ENUM;

typedef enum {
	DispatchTask = 2001
}ADD_ENUM;

typedef enum {
	DELETE_ORDER = 3001
}DELETE_ENUM;

typedef enum {
	AbortOrder = 4001,
	RecoverWeightStatus = 4002
}UPDATE_ENUM;


typedef struct _Pos_Info
{
	float x;
	float y;
	float theta;

} Pos_Info;

typedef struct _Order
{
	int Order_ID_;
	std::string START_;
	std::string Belong_Column_;     //ø‚ŒªÀ˘ Ù¡–;
	std::string TARGET_;
	int PRIORITY_;
	std::string STATUS_;
	std::string MODE_;
	std::string TYPE_;
	int AGV_ID_;
	std::string ENTERDATE_;
	std::string FINISHDATE_;
}Order;

typedef struct _Oreder_Task
{
	int ORDER_ID;
	int WCS_TASK_ID;
	std::string STATE_POINT;
	std::string TARGET_POINT;
	std::string MODE;
	std::string TYPE;
	int AGV_ID;

}Oreder_Task;

typedef struct _Pallet_Task
{
	int ID_;
	std::string EQUIP_NAME_;
	int PRIORITY_;
	std::string ENTERDATE_;
	std::string FINISHDATE_;
	std::string STATUS_;
	std::string DIRFLG_;
}Pallet_Task;

typedef struct _Task_Dispatch
{
	int task_id_;
	std::string task_from_;
	std::string task_to_;
	int priority_;
	int agv_type_;
	int task_type_;
	int auto_dispatch_;
	int agv_id_;
	bool dispatched;

}Task_Dispatch;

typedef struct _AGV 
{
	int AGV_ID_;
	double POS_X_;
	double POS_Y_;
	double POS_TH_;
	int AGV_TYPE_;
	int IS_ONLINE_;
	int AT_NODE_;
	int STATUS_;
	int ERROR_CODE_;
	std::string AT_STATION_;
	double BATTERY_LEVEL_;
	int IS_SERVING_;
	int IS_ASSIGNED_;
	std::string IP_;
	std::string TIMESTAMP_;
	double STATION_ERROR_X_;
	double STATION_ERROR_Y_;
	double STATION_ERROR_TH_;
}AGV;

typedef struct _Storage
{
	int ID_;
	std::string Storage_Name_;
	int Storage_Row_;
	int Storage_Column_;
	int Storage_Depth_;
	std::string Storage_Status_;
	std::string Belong_Column_;
	int All_Storage_Num_;
	int Full_Storage_Num_;
	std::string Belong_Area_;
	std::string Area_Lock_;
}Storage;

typedef struct _Top_Storage_
{
	std::string Storage_Column_;
	int All_Storage_Num_;
	int Full_Storage_Num_;
	std::string State_;
}Top_Storage;

typedef struct _Weight_Info_
{
	int AGV_ID_;
	double Good_Weight_;
	std::string Status_;
}Weight_Info;

typedef enum {
	UNLOCKED = 0,
	LOCKED = 1,
	BUSY = 2,
	IDEL = 3
}RESOURCE_STATUS;

typedef enum {
	IDLE = 0,
	RUNNING = 2
}AGV_SUB_STATUS;

#endif //_MANAGE_DEFINE_H
