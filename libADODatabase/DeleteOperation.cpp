#include "stdafx.h"
#include <iostream>
#include <sstream>
#include "DeleteOperation.h"

DeleteOperation::DeleteOperation()
{
}

DeleteOperation::~DeleteOperation()
{
}

void DeleteOperation::setDeleteAdo(ADOcon* Delete_Con)
{
	DeleteAdo_ = *Delete_Con;
}

bool DeleteOperation::deleteFailedOrder(std::string wcs_task_id)
{
	int row_count = 0;
	std::stringstream ss;

	ss << "SELECT COUNT(*) FROM linde_order_info WHERE WCS_TASK_ID = " << wcs_task_id << "";
	_bstr_t SQL = ss.str().c_str();
	recordPtr_ = DeleteAdo_.GetRecordSet(SQL);

	try {
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
			ssTop << "DELETE  FROM linde_order_info  WHERE WCS_TASK_ID = " << wcs_task_id << "";
			_bstr_t SQL2 = ssTop.str().c_str();
			DeleteAdo_.ExecuteSQL(SQL2);
		}
	}
	catch (_com_error &e)
	{
		std::cout << "deleteFailedOrder" << e.ErrorMessage() << std::endl;
		std::cout << e.Description() << std::endl;
		return false;
	}
	return true;
}