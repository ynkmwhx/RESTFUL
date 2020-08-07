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

	 bool readStrJsonAddOrder(std::string str, Order &current_order); //��Json�����ַ�������ӹ���;

	 bool readStrJsonUpdateOrderStatues(std::string str, Order &current_order); //��Json�����ַ������޸Ĺ���״̬;

	 bool readStrJsonRecoverWeightStatues(std::string str, Weight_Info &current_weight); //��Json�����ַ������޸Ĺ���״̬;
protected:

private:

	
};
typedef boost::serialization::singleton<readJson> SingletonreadJson;

#define READ_JSON SingletonreadJson::get_mutable_instance()
#endif // READJSON_Honce