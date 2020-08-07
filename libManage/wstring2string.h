#pragma //readJson.h
#ifndef WSTRING2STRING_H
#define WSTRING2STRING_H

#include <Winsock2.h>
#include <Windows.h>
#include <boost/serialization/singleton.hpp>
#include <iostream>


class StringExchange
{
public:
	StringExchange();
	~StringExchange();

	std::string wstring2string(std::wstring wstr);


	std::wstring string2wstring(std::string str);
protected:

private:

};
typedef boost::serialization::singleton<StringExchange> SingletonStringExchange;

#define STRING_EXCHANGE SingletonStringExchange::get_mutable_instance()
#endif // READJSON_Honce