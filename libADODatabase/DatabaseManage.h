#pragma once
#ifndef _DATABASE_MANAGE_EDWARD_
#define _DATABASE_MANAGE_EDWARD_

#include <boost/serialization/singleton.hpp>
#include <cpprest/http_client.h>
#include <cpprest/filestream.h>
#include <cpprest/http_listener.h>              // HTTP server
#include "WcsDatabase.h"
#include "DatabaseManage.h"
#include "QueryOperation.h"
#include "AddOperation.h"
#include "DeleteOperation.h"
#include "UpdateOperation.h"
#include "WcsDatabase.h"
#include "wstring2string.h"
#include "readJson.h"

using namespace std;
using namespace web;
using namespace http;
using namespace utility;
using namespace http::experimental::listener;

class Database_Manage
{
public:
	Database_Manage();
	~Database_Manage();

	void queryOrderStatus(http_request message);

	void queryAGVInfo(http_request message);

	void queryWeightInfo(http_request message);

	void dispatchTask(std::string json_string, http_request message);

	void deleteFailedOrder(http_request meseage);

	void abortWaitingOrder(std::string josn_string, http_request message);

	void recoverWeightStatus(std::string josn_string, http_request meseage);
	
private:

	_RecordsetPtr recordPtr_;

	std::vector<QueryOperation*> Query_List_;
};

typedef boost::serialization::singleton<Database_Manage> Singleton_DB_Manage;

#define DATABASE_MANAGE Singleton_DB_Manage::get_mutable_instance()
#endif