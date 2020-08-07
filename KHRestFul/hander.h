#pragma //hander.h
#ifndef HANDLER_H
#define HANDLER_H
#include <Winsock2.h>
#include <iostream>
#include <cpprest/http_client.h>
#include <cpprest/filestream.h>
#include <cpprest/http_listener.h>              // HTTP server
#include "wstring2string.h"
#include "DatabaseManage.h"


//#include "stdafx.h"
//#include "../dbms/include/Dbms.h"

using namespace std;
using namespace web;
using namespace http;
using namespace utility;
using namespace http::experimental::listener;


class handler
{
public:
	handler();
	handler(utility::string_t url);
	virtual ~handler();
	//string handler:wstring2string(wstring wstr);
	pplx::task<void>open() { return m_listener.open(); }
	pplx::task<void>close() { return m_listener.close(); }

protected:

private:
	void handle_get(http_request message);
	void handle_put(http_request message);
	void handle_post(http_request message);
	void handle_delete(http_request message);
	void handle_error(pplx::task<void>& t);
	http_listener m_listener;

	void getLaser(std::map<std::string, std::string> &input_data, std::string &out_data);
	WcsDatabase* WCS_CON_;
};

#endif // HANDLER_Honce
