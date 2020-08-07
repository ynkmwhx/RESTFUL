#include "stdafx.h"
#include "readJson.h"


readJson::readJson()
{
	
}
readJson::~readJson()
{

}

int readJson::analysisJsonOperationCode(std::string josn_str)
{
	Json::Value root;
	Json::Reader reader;
	int OperationCode;
	
	if (!reader.parse(josn_str, root))
	{
		OperationCode = -1;   //ERR
	}
	else
	{
		OperationCode = root["OperationCode"].asInt();
	}
	return OperationCode;
}

bool readJson::readStrJsonAddOrder(std::string str, Order &current_order)
{
	Json::Value root;
	Json::Reader reader;

	if (!reader.parse(str, root))
	{
		return false;
	}
	else
	{
		int OperationCode = root["OperationCode"].asInt();
		int ORDER_ID = root["ORDER_ID"].asInt();
		std::string START = root["START"].asString();
		std::string TARGET = root["TARGET"].asString();
		int PRIORITY = root["PRIORITY"].asInt();
		std::string STATUS = root["STATUS"].asString();
		std::string MODE = root["MODE"].asString();
		std::string TYPE = root["TYPE"].asString();

		
		current_order.Order_ID_ = ORDER_ID;
		current_order.START_ = START;
		current_order.TARGET_ = TARGET;
		current_order.STATUS_ = STATUS;
		current_order.PRIORITY_ = PRIORITY;
		current_order.MODE_ = MODE;
		current_order.TYPE_ = TYPE;
		return true;
	}
}

bool readJson::readStrJsonUpdateOrderStatues(std::string str, Order &current_order)
{
	Json::Value root;
	Json::Reader reader;

	if (!reader.parse(str, root))
	{
		return false;
	}
	else
	{
		current_order.Order_ID_ = root["ORDER_ID"].asInt();
		current_order.STATUS_ = root["STATUS"].asString();
		return true;
	}
}

bool readJson::readStrJsonRecoverWeightStatues(std::string str, Weight_Info &current_weight)
{
	Json::Value root;
	Json::Reader reader;

	if (!reader.parse(str, root))
	{
		return false;
	}
	else
	{
		current_weight.AGV_ID_ = root["AGV_ID"].asInt();
		current_weight.Status_ = root["STATUS"].asString();
		return true;
	}
}