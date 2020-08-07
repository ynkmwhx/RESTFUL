#include "stdafx.h"
#include <iostream>
#include <sstream>
#include "DatabaseManage.h"


Database_Manage::Database_Manage()
{

}

Database_Manage::~Database_Manage()
{

}

void Database_Manage::queryOrderStatus(http_request message)
{
	utility::string_t Order_ID_t = uri::split_query(message.request_uri().to_string())[utility::string_t(L"ORDER_ID")];
	//utility::string_t START_t = uri::split_query(message.request_uri().to_string())[utility::string_t(L"START")];
	//utility::string_t TARGET_t = uri::split_query(message.request_uri().to_string())[utility::string_t(L"TARGET")];
	//utility::string_t MODE_t = uri::split_query(message.request_uri().to_string())[utility::string_t(L"MODE")];
	//utility::string_t TYPE_t = uri::split_query(message.request_uri().to_string())[utility::string_t(L"TYPE")];

	Order curren_order;
	curren_order.Order_ID_ = std::stoi(STRING_EXCHANGE.wstring2string(Order_ID_t));
	//curren_order.START_ = STRING_EXCHANGE.wstring2string(START_t);
	//curren_order.TARGET_ = STRING_EXCHANGE.wstring2string(TARGET_t);
	//curren_order.MODE_ = STRING_EXCHANGE.wstring2string(MODE_t);
	//curren_order.TYPE_ = STRING_EXCHANGE.wstring2string(TYPE_t);
	
	if (QUERY_OPERATION.queryOrderStatus(curren_order))
	{
		Json::Value out;
		Json::Value value;
		value["Order_ID"] = int(curren_order.Order_ID_);
		value["AGV_ID"] = int(curren_order.AGV_ID_);
		value["START"] = std::string(curren_order.START_);
		value["TARGET"] = std::string(curren_order.TARGET_);
		value["PRIORITY"] = int(curren_order.PRIORITY_);
		value["STATUS"] = std::string(curren_order.STATUS_);
		value["MODE"] = std::string(curren_order.MODE_);
		value["TYPE"] = std::string(curren_order.TYPE_);
		value["ENTERDATE"] = std::string(curren_order.ENTERDATE_);
		value["FINISHDATE"] = std::string(curren_order.FINISHDATE_);

		out.append(value);
		message.reply(status_codes::OK, value.toStyledString());
	}
	else
	{
		message.reply(status_codes::BadRequest,U("Query database failed"));
	}
}

void Database_Manage::queryAGVInfo(http_request message)
{
	utility::string_t AGV_ID_t = uri::split_query(message.request_uri().to_string())[utility::string_t(L"AGV_ID")];
	//utility::string_t START_t = uri::split_query(message.request_uri().to_string())[utility::string_t(L"START")];
	//utility::string_t TARGET_t = uri::split_query(message.request_uri().to_string())[utility::string_t(L"TARGET")];
	//utility::string_t MODE_t = uri::split_query(message.request_uri().to_string())[utility::string_t(L"MODE")];
	//utility::string_t TYPE_t = uri::split_query(message.request_uri().to_string())[utility::string_t(L"TYPE")];

	AGV curren_agv;
	curren_agv.AGV_ID_ = std::stoi(STRING_EXCHANGE.wstring2string(AGV_ID_t));
	//curren_order.START_ = STRING_EXCHANGE.wstring2string(START_t);
	//curren_order.TARGET_ = STRING_EXCHANGE.wstring2string(TARGET_t);
	//curren_order.MODE_ = STRING_EXCHANGE.wstring2string(MODE_t);
	//curren_order.TYPE_ = STRING_EXCHANGE.wstring2string(TYPE_t);

	if (QUERY_OPERATION.queryAgvInfo(curren_agv))
	{
		Json::Value out;
		Json::Value value;
		value["AGV_ID"] = int(curren_agv.AGV_ID_);
		value["POS_X"] = double(curren_agv.POS_X_);
		value["POS_Y"] = double(curren_agv.POS_Y_);
		value["POS_TH"] = double(curren_agv.POS_TH_);
		value["STATUS"] = int(curren_agv.STATUS_);
		value["ERROR_CODE"] = int(curren_agv.ERROR_CODE_);
		value["BATTERY_LEVEL"] = double(curren_agv.BATTERY_LEVEL_);
		value["AGV_TYPE"] = int(curren_agv.AGV_TYPE_);
		value["IS_ONLINE"] = int(curren_agv.IS_ONLINE_);
		value["IS_SERVING"] = int(curren_agv.IS_SERVING_);
		value["IS_ASSIGNED"] = int(curren_agv.IS_ASSIGNED_);
		value["IP"] = std::string(curren_agv.IP_);
		value["AT_NODE"] = int(curren_agv.AT_NODE_);
		value["AT_STATION"] = std::string(curren_agv.AT_STATION_);	
		value["STATION_ERROR_X"] = double(curren_agv.STATION_ERROR_X_);
		value["STATION_ERROR_Y"] = double(curren_agv.STATION_ERROR_Y_);
		value["STATION_ERROR_TH"] = double(curren_agv.STATION_ERROR_TH_);
		value["TIMESTAMP"] = std::string(curren_agv.TIMESTAMP_);
	
		out.append(value);
		message.reply(status_codes::OK, value.toStyledString());
	}
	else
	{
		message.reply(status_codes::BadRequest, U("Query database failed"));
	}
}

void Database_Manage::queryWeightInfo(http_request message)
{
	utility::string_t AGV_ID_t = uri::split_query(message.request_uri().to_string())[utility::string_t(L"AGV_ID")];
	//utility::string_t START_t = uri::split_query(message.request_uri().to_string())[utility::string_t(L"START")];
	//utility::string_t TARGET_t = uri::split_query(message.request_uri().to_string())[utility::string_t(L"TARGET")];
	//utility::string_t MODE_t = uri::split_query(message.request_uri().to_string())[utility::string_t(L"MODE")];
	//utility::string_t TYPE_t = uri::split_query(message.request_uri().to_string())[utility::string_t(L"TYPE")];

	Weight_Info current_weight;
	current_weight.AGV_ID_ = std::stoi(STRING_EXCHANGE.wstring2string(AGV_ID_t));
	//curren_order.START_ = STRING_EXCHANGE.wstring2string(START_t);
	//curren_order.TARGET_ = STRING_EXCHANGE.wstring2string(TARGET_t);
	//curren_order.MODE_ = STRING_EXCHANGE.wstring2string(MODE_t);
	//curren_order.TYPE_ = STRING_EXCHANGE.wstring2string(TYPE_t);

	if (QUERY_OPERATION.queryGoodsWeight(current_weight))
	{
		Json::Value out;
		Json::Value value;
		value["AGV_ID"] = int(current_weight.AGV_ID_);
		value["WEIGHT"] = double(current_weight.Good_Weight_);
		value["STATUS"] = std::string(current_weight.Status_);
		
		out.append(value);
		message.reply(status_codes::OK, value.toStyledString());
	}
	else
	{
		message.reply(status_codes::BadRequest, U("Query database failed"));
	}
}

void Database_Manage::dispatchTask(std::string json_string,http_request message)
{
	Order new_order;
	if (READ_JSON.readStrJsonAddOrder(json_string, new_order))
	{
		if (ADD_OPERATION.AddOperationDispatchTask(new_order))
		{
			message.reply(status_codes::OK, U("Dispatch new order successful"));
		}
		else
		{
			message.reply(status_codes::BadRequest, U("Dispatch new order failed"));
		}
	}
	else
	{
		message.reply(status_codes::BadRequest, U("Dispatch new order failed"));
	}
}

void Database_Manage::deleteFailedOrder(http_request message)
{
	utility::string_t WCS_TASK_ID_t = uri::split_query(message.request_uri().to_string())[utility::string_t(L"OrderID")];
	std::string WCS_TASK_ID = STRING_EXCHANGE.wstring2string(WCS_TASK_ID_t);

	if (DELETE_OPERATION.deleteFailedOrder(WCS_TASK_ID))
	{
		message.reply(status_codes::OK, U("Delete failed order successful"));
	}
	else
	{
		message.reply(status_codes::BadRequest, U("Delete failed order failed"));
	}
}

void Database_Manage::abortWaitingOrder(std::string json_string, http_request message)
{
	Order current_order;
	if (READ_JSON.readStrJsonUpdateOrderStatues(json_string, current_order))
	{
		if (UPDATE_OPERATION.UpdateOperationAbortWaitingOrder(current_order))
		{
			message.reply(status_codes::OK, U("Abort Waiting Order successful"));
		}
		else
		{
			message.reply(status_codes::BadRequest, U("Abort Waiting Order failed"));
		}
	}
	else
	{
		message.reply(status_codes::BadRequest, U("Analysis Json failed"));
	}
}

void Database_Manage::recoverWeightStatus(std::string josn_string,http_request message)
{
	Weight_Info current_weight;
	if (READ_JSON.readStrJsonRecoverWeightStatues(josn_string, current_weight))
	{
		if (UPDATE_OPERATION.UpdateOperationRecoverWeightInfo(current_weight))
		{
			message.reply(status_codes::OK, U("Recover WeightInfo successful"));
		}
		else
		{
			message.reply(status_codes::BadRequest, U("Recover WeightInfo failed"));
		}
	}
	else
	{
		message.reply(status_codes::BadRequest, U("Analysis Json failed"));
	}
}