#pragma //readJson.h
#ifndef READJSON_H
#define READJSON_H
#include <Winsock2.h>
#include <boost/serialization/singleton.hpp>
#include <iostream>
#include "json/json.h"
#include "ManageDefine.h"

class readJson
{
public:
	 readJson();
	 ~readJson();

	 int analysisJsonOperationCode(std::string josn_str);

	 bool readStrJsonAddOrder(std::string str, Order &current_order); //从Json解析字符串，添加工单;

	 bool readStrJsonUpdateOrderStatues(std::string str, Order &current_order); //从Json解析字符串，修改工单状态;

	 bool readStrJsonRecoverWeightStatues(std::string str, Weight_Info &current_weight); //从Json解析字符串，修改工单状态;
protected:

private:

	
};
typedef boost::serialization::singleton<readJson> SingletonreadJson;

#define READ_JSON SingletonreadJson::get_mutable_instance()
#endif // READJSON_Honce