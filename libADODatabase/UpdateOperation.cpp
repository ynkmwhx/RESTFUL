#include "stdafx.h"
#include <sstream>
#include <iostream>
#include "UpdateOperation.h"

UpdateOperation::UpdateOperation()
{
}

UpdateOperation::~UpdateOperation()
{
}

void UpdateOperation::setUpdateAdo(ADOcon* UpdATe_Con)
{
	UpdateAdo_ = *UpdATe_Con;
}

bool UpdateOperation::UpdateOperationAbortWaitingOrder(Order current_order)
{
	int row_count = 0;
	std::stringstream ss;
	try {
		ss << "SELECT COUNT(*) FROM kh_order_info WHERE ORDER_ID = '" << current_order.Order_ID_ << "'";
		_bstr_t SQL = ss.str().c_str();
		recordPtr_ = UpdateAdo_.GetRecordSet(SQL);

		if (recordPtr_) {
			row_count = (int)recordPtr_->GetCollect("count(*)");
		}
		else
		{
			std::cout << "Cant get Recordset!" << std::endl;
		}
		if (row_count == 1)
		{
			std::stringstream ssTop;
			ssTop << "UPDATE kh_order_info SET STATUS = '" << current_order.STATUS_ << "' WHERE ORDER_ID = " << current_order.Order_ID_ << "";
			_bstr_t SQL2 = ssTop.str().c_str();
			UpdateAdo_.ExecuteSQL(SQL2);
		}
		else
		{
			return false;
		}
	}
	catch (_com_error &e)
	{
		std::cout << "UpdateOperationAbortWaitingOrder" << e.ErrorMessage() << std::endl;
		std::cout << e.Description() << std::endl;
		return false;
	}
}

bool UpdateOperation::UpdateOperationRecoverWeightInfo(Weight_Info current_weight)
{
	int row_count = 0;
	std::stringstream ss;
	try {
		ss << "SELECT COUNT(*) FROM kh_report_weight_info WHERE AGV_ID = '" << current_weight.AGV_ID_ << "'";
		_bstr_t SQL = ss.str().c_str();
		recordPtr_ = UpdateAdo_.GetRecordSet(SQL);

		if (recordPtr_) {
			row_count = (int)recordPtr_->GetCollect("count(*)");
		}
		else
		{
			std::cout << "Cant get Recordset!" << std::endl;
		}
		if (row_count == 1)
		{
			std::stringstream ssTop;
			ssTop << "UPDATE kh_report_weight_info SET STATUS = '" << current_weight.Status_ << "' WHERE AGV_ID = " << current_weight.AGV_ID_ << "";
			_bstr_t SQL2 = ssTop.str().c_str();
			UpdateAdo_.ExecuteSQL(SQL2);
		}
		else
		{
			return false;
		}
	}
	catch (_com_error &e)
	{
		std::cout << "UpdateOperationRecoverWeightInfo" << e.ErrorMessage() << std::endl;
		std::cout << e.Description() << std::endl;
		return false;
	}
}


