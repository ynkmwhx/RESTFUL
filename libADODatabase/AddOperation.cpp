#include "stdafx.h"
#include <iostream>
#include <sstream>
#include "AddOperation.h"

AddOperation::AddOperation()
{
}

AddOperation::~AddOperation()
{
}

void AddOperation::setAddAdo(ADOcon* Add_Con)
{
	AddAdo_ = *Add_Con;
}


bool AddOperation::AddOperationDispatchTask(Order order)
{
	int row_count = 0;
	std::stringstream ss;

	ss << "SELECT COUNT(*) FROM kh_order_info WHERE ORDER_ID = " << order.Order_ID_ << "";
	_bstr_t SQL = ss.str().c_str();
	recordPtr_ = AddAdo_.GetRecordSet(SQL);

	try {
		if (recordPtr_) {
			row_count = (int)recordPtr_->GetCollect("count(*)");
		}
		else
		{
			std::cout << "Cant get Recordset!" << std::endl;
		}
		if (row_count == 0)
		{
			std::stringstream ssOrder;
			ssOrder << "INSERT INTO kh_order_info (ORDER_ID,START,TARGET,PRIORITY,STATUS,MODE,TYPE)VALUES(" << order.Order_ID_ << ",'" << order.START_ << "','" << order.TARGET_ << "','" << order.PRIORITY_ << "','" << order.STATUS_ << "','" << order.MODE_ << "','" << order.TYPE_ << "')";
			_bstr_t SQL = ssOrder.str().c_str();
			AddAdo_.ExecuteSQL(SQL);

			std::cout << "Add_Task_To_Order_List: " << "Order_ID:" << order.Order_ID_ << "," << "START:" << order.START_ << "," << "TARGETED:" << order.TARGET_ << "," << "PRIORITY:" << order.PRIORITY_ << "," << "STATUS:" << order.STATUS_ << "," << "MODE:" << order.MODE_ << "," << "TYPE:" << order.TYPE_ << std::endl;
			return true;
		}
		else
		{
			return false;
		}
	}
	catch (_com_error &e)
	{
		std::cout << "AddOperationDispatchTask " << e.ErrorMessage() << std::endl;
		std::cout << e.Description() << std::endl;
		return false;
	}
}
