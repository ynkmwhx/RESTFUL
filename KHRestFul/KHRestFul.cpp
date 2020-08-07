// Web2.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include "pch.h"
#include <iostream>
#include "hander.h"
#include <conio.h>
#include <cpprest/http_client.h>
#include <cpprest/filestream.h>
#include <cpprest/http_listener.h>              // HTTP server
#include <cpprest/json.h>                       // JSON library
#include <cpprest/uri.h>                        // URI library
#include <cpprest/ws_client.h>                  // WebSocket client
#include <cpprest/containerstream.h>            // Async streams backed by STL containers
#include <cpprest/interopstream.h>              // Bridges for integrating Async streams with STL and WinRT streams
#include <cpprest/rawptrstream.h>               // Async streams backed by raw pointer to memory
#include <cpprest/producerconsumerstream.h>     // Async streams for producer consumer scenarios

using namespace std;
using namespace web;
using namespace http;
using namespace utility;
using namespace http::experimental::listener;

std::unique_ptr<handler> g_httpHandler;

void on_initialize(const string_t& address)
{
	ADOcon* Query_Wcs_Con = new ADOcon();
	ADOcon* Query_Agvs_Con = new ADOcon();
	ADOcon* Add_Con = new ADOcon();
	ADOcon* Update_Con = new ADOcon();
	ADOcon* Delete_Con = new ADOcon();

	Query_Wcs_Con->OnInitADOConn(ADO_Database::WCS_DB);
	Query_Agvs_Con->OnInitADOConn(ADO_Database::ACS_DB);
	Add_Con->OnInitADOConn(ADO_Database::WCS_DB);
	Update_Con->OnInitADOConn(ADO_Database::WCS_DB);
	Delete_Con->OnInitADOConn(ADO_Database::WCS_DB);

	QUERY_OPERATION.setQueryWcsAdo(Query_Wcs_Con);
	QUERY_OPERATION.setQueryAgvsAdo(Query_Agvs_Con);
	ADD_OPERATION.setAddAdo(Add_Con);
	UPDATE_OPERATION.setUpdateAdo(Update_Con);
	DELETE_OPERATION.setDeleteAdo(Delete_Con);

	uri_builder uri(address);

	auto addr = uri.to_uri().to_string();
	g_httpHandler = std::unique_ptr<handler>(new handler(addr));
	g_httpHandler->open().wait();
	ucout << utility::string_t(U("Listening for requests at: ")) << addr << std::endl;

	return;
}

void on_shutdown()
{
	g_httpHandler->close().wait();
	return;
}

#ifdef _WIN32
int wmain(int argc, wchar_t *argv[])
#else
int main(int argc, char *argv[])
#endif
{

	utility::string_t port = U("625");
	if (argc == 2)
	{
		port = argv[1];
	}

	utility::string_t address = U("http://127.0.0.1:");
	address.append(port);
	address.append(U("/api/agv?"));
	on_initialize(address);
	
	std::cout << "Press ESC to exit." << std::endl;

	/*std::string line;
	std::getline(std::cin, line);
	char ch;
	ch = getch();
	if (ch == 27) {
		on_shutdown();
		exit(1);
	}*/
	while (1)
	{
		if (_kbhit() && _getch() == 0x1b)
			return 0;
	}
}
