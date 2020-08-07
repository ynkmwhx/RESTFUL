//hander.cpp
 
#include "pch.h"
#include "hander.h"
#include "map"
#include <locale>
#include <codecvt>
#include "json/json.h"
#include "readJson.h"
#include "ManageDefine.h"

handler::handler()
{
	
	//ctor
}
handler::handler(utility::string_t url) :m_listener(url)
{
	m_listener.support(methods::GET, std::bind(&handler::handle_get, this, std::placeholders::_1));
	m_listener.support(methods::PUT, std::bind(&handler::handle_put, this, std::placeholders::_1));
	m_listener.support(methods::POST, std::bind(&handler::handle_post, this, std::placeholders::_1));
	m_listener.support(methods::DEL, std::bind(&handler::handle_delete, this, std::placeholders::_1));
	//WCS_CON_ = DATABASE_MANAGE.Get_WCS_DB();
}
handler::~handler()
{
	//dtor
}

void handler::handle_error(pplx::task<void>& t)
{
	try
	{
		t.get();
	}
	catch (...)
	{
		// Ignore the error, Log it if a logger is available
	}
}




//
// Get Request 
//
void handler::handle_get(http_request message)
{
	//ucout << message.request_uri().to_string() << endl;
	auto aa = uri::split_query(message.absolute_uri().to_string());
	//first = L"/api/agv?OperationCode"
	
	utility::string_t OperationCode_t = uri::split_query(message.request_uri().to_string())[utility::string_t(L"/api/agv/?OperationCode")];
	std::string OperationCode = STRING_EXCHANGE.wstring2string(OperationCode_t);
	int op_code = std::stoi(OperationCode);
	
	switch (op_code)
	{
	case QUERY_ENUM::QueryOrder:
		DATABASE_MANAGE.queryOrderStatus(message);
		break;

	case QUERY_ENUM::QueryAGVInfo:
		DATABASE_MANAGE.queryAGVInfo(message);
		break;

	case QUERY_ENUM::QueryWeightInfo:
		DATABASE_MANAGE.queryWeightInfo(message);
		break;

	default:
		message.reply(status_codes::RangeNotSatisfiable, U("Requested range not satisfiable,please check OperationCode"));
	}

	//auto paths = http::uri::split_path(http::uri::decode(message.relative_uri().path()));

	//message.relative_uri().path();
	//Dbms* d  = new Dbms();
	//d->connect();

	//concurrency::streams::fstream::open_istream(U("static/index.html"), std::ios::in).then([=](concurrency::streams::istream is)
	//{
	//	message.reply(status_codes::OK, is, U("text/html"))
	//		.then([](pplx::task<void> t)
	//	{
	//		try {
	//			t.get();
	//		}
	//		catch (...) {
	//			//
	//		}
	//	});
	//}).then([=](pplx::task<void>t)
	//{
	//	try {
	//		t.get();
	//	}
	//	catch (...) {
	//		message.reply(status_codes::InternalError, U("INTERNAL ERROR "));
	//	}
	//});

	return;

};

//
// A POST request
//
void handler::handle_post(http_request message)
{
	ucout << message.to_string() << endl;
	
	Concurrency::streams::container_buffer<std::vector<uint8_t> >inBuffer;

	message.body().read_to_end(inBuffer).then([inBuffer,message](size_t bytesRead)
	{
		const auto& bodyStrVector = inBuffer.collection();
		std::string jsonStr;
		for each (auto ch in bodyStrVector)
		{
			jsonStr.push_back(ch);
		}
		cout << "jsonStr = " << jsonStr << endl;
		
		int op_code = READ_JSON.analysisJsonOperationCode(jsonStr);

		switch (op_code)
		{
		case ADD_ENUM::DispatchTask:

			DATABASE_MANAGE.dispatchTask(jsonStr,message);
			break;


		default:
			cout << "jsonStr = " << jsonStr << endl;
		//	message.reply(status_codes::RangeNotSatisfiable, U("Requested range not satisfiable,please check OperationCode"));
		}

	});

	//message.reply(status_codes::OK, message.to_string());
	return;
}


//
// A DELETE request
//
void handler::handle_delete(http_request message)
{
	auto aa = uri::split_query(message.absolute_uri().to_string());

	utility::string_t OperationCode_t = uri::split_query(message.request_uri().to_string())[utility::string_t(L"/?OperationCode")];
	std::string OperationCode = STRING_EXCHANGE.wstring2string(OperationCode_t);
	int op_code = std::stoi(OperationCode);

	switch (op_code)
	{
	case DELETE_ENUM::DELETE_ORDER:
		DATABASE_MANAGE.deleteFailedOrder(message);
		break;


	default:
		message.reply(status_codes::RangeNotSatisfiable, U("Requested range not satisfiable,please check OperationCode"));
	}
	wstring rep = U("WRITE YOUR OWN DELETE OPERATION");
	
	//message.reply(status_codes::OK, rep);
	return;
};


//
// A PUT request 
//
void handler::handle_put(http_request message)
{
	//ucout << message.to_string() << endl;
	Concurrency::streams::container_buffer<std::vector<uint8_t> >inBuffer;

	message.body().read_to_end(inBuffer).then([inBuffer,message](size_t bytesRead)
	{
		const auto& bodyStrVector = inBuffer.collection();
		std::string jsonStr;
		for each (auto ch in bodyStrVector)
		{
			jsonStr.push_back(ch);
		}
		cout << "jsonStr = " << jsonStr << endl;

		int op_code = READ_JSON.analysisJsonOperationCode(jsonStr);

		switch (op_code)
		{
		case UPDATE_ENUM::AbortOrder:

			DATABASE_MANAGE.abortWaitingOrder(jsonStr,message);
			break;

		case UPDATE_ENUM::RecoverWeightStatus:

			DATABASE_MANAGE.recoverWeightStatus(jsonStr,message);
			break;

		default:
			message.reply(status_codes::RangeNotSatisfiable, U("Requested range not satisfiable,please check OperationCode"));
		}

	});
	wstring rep = U("WRITE YOUR OWN PUT OPERATION");
	//message.reply(status_codes::OK, rep);
	return;
};



