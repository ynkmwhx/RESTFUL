#include "stdafx.h"
#include <iostream>
#include <sstream>
#include "stdlib.h"
#include "WcsDatabase.h"


WcsDatabase::WcsDatabase()
{

}

WcsDatabase::~WcsDatabase()
{

}

void WcsDatabase::setWcsAdo(ADOcon ADO)
{
	wcsAdo_ = ADO;
}

//void WcsDatabase::findOrderStatus(std::string wcs_task_id)
//{
//	int row_count = 0;
//	std::stringstream ss;
//	std::stringstream ss2;
//
//	ss << "SELECT COUNT(*) FROM linde_order_info WHERE WCS_TASK_ID = " << wcs_task_id << "";
//	_bstr_t SQL = ss.str().c_str();
//	recordPtr_ = wcsAdo_.GetRecordSet(SQL);
//
//	try {
//		if (recordPtr_) {
//			row_count = (int)recordPtr_->GetCollect("count(*)");
//		}
//		else
//		{
//			std::cout << "Cant get Recordset!" << std::endl;
//		}
//		if (row_count == 1)
//		{
//			ss2 << "SELECT * FROM linde_report_task_info WHERE WCS_TASK_ID = " << wcs_task_id << "";
//			_bstr_t SQL2 = ss2.str().c_str();
//			recordPtr_ = wcsAdo_.GetRecordSet(SQL2);
//
//			int ORDER_ID = atoi(_bstr_t(recordPtr_->Fields->GetItem(_variant_t("ID"))->Value));
//			int WCS_TASK_ID = atoi(_bstr_t(recordPtr_->Fields->GetItem(_variant_t("WCS_TASK_ID"))->Value));
//			std::string START = (std::string)(_bstr_t)(recordPtr_->Fields->GetItem(_variant_t("START"))->Value);
//			std::string TARGET = (std::string)(_bstr_t)(recordPtr_->Fields->GetItem(_variant_t("TARGET"))->Value);
//			std::string MODE = (std::string)(_bstr_t)(recordPtr_->Fields->GetItem(_variant_t("MODE"))->Value);
//			std::string TYPE = (std::string)(_bstr_t)(recordPtr_->Fields->GetItem(_variant_t("TYPE"))->Value);
//			std::cout << "SLQ !!!!!!!!!! OREDER_ID:" << ORDER_ID << ",WCS_TASK_ID:" << WCS_TASK_ID << ",START:" << START << ",TARGET:" << TARGET <<
//				",MODE:" << MODE << ",TYPE:" << TYPE << std::endl;
//		}
//	}
//	catch (_com_error &e) {
//		std::cout << e.ErrorMessage() << "findOrderStatus" << std::endl;
//		std::cout << e.Description() << std::endl;
//	}
//
//}
//
//bool WcsDatabase::databseDispatchTask(Order order)
//{
//
//	int row_count = 0;
//	std::stringstream ss;
//	
//
//	ss << "SELECT COUNT(*) FROM linde_order_info WHERE WCS_TASK_ID = " << order.WCS_TASK_ID_ << "";
//	_bstr_t SQL = ss.str().c_str();
//	recordPtr_ = wcsAdo_.GetRecordSet(SQL);
//
//	try {
//		if (recordPtr_) {
//			row_count = (int)recordPtr_->GetCollect("count(*)");
//		}
//		else
//		{
//			std::cout << "Cant get Recordset!" << std::endl;
//		}
//		if (row_count == 0)
//		{
//			std::stringstream ssOrder;
//			ssOrder << "INSERT INTO linde_order_info (WCS_TASK_ID,START,TARGET,PRIORITY,STATUS,MODE,TYPE)VALUES(" << order.WCS_TASK_ID_ << ",'" << order.START_ << "','" << order.TARGET_ << "','" << order.PRIORITY_ << "','" << order.STATUS_ << "','" << order.MODE_ << "','" << order.TYPE_ << "')";
//			_bstr_t SQL = ssOrder.str().c_str();
//			wcsAdo_.ExecuteSQL(SQL);
//
//			std::cout << "Add_Task_To_Order_List: " << "WCS_TASK_ID:" << order.WCS_TASK_ID_ << "," << "START:" << order.START_ << "," << "TARGETED:" << order.TARGET_ << "," << "PRIORITY:" << order.PRIORITY_ << "," << "STATUS:" << order.STATUS_ << "," << "MODE:" << order.MODE_ << "," << "TYPE:" << order.TYPE_ << std::endl;
//		}
//	}
//	catch (_com_error &e)
//	{
//		std::cout << "databseDispatchTask " << e.ErrorMessage() << std::endl;
//		std::cout << e.Description() << std::endl;
//		return false;
//	}
//	return true;
//
//}
//
//bool WcsDatabase::updateTopStorage(std::string storage_column, int full_storage_num, std::string state)
//{
//	int row_count = 0;
//	std::stringstream ss;
//
//	ss << "SELECT COUNT(*) FROM linde_receive_top_storage_info WHERE storage_column = '" << storage_column << "'";
//	_bstr_t SQL = ss.str().c_str();
//	recordPtr_ = wcsAdo_.GetRecordSet(SQL);
//
//	try {
//		if (recordPtr_) {
//			row_count = (int)recordPtr_->GetCollect("count(*)");
//		}
//		else
//		{
//			std::cout << "Cant get Recordset!" << std::endl;
//		}
//		if (row_count == 1)
//		{
//			std::stringstream ssTop;
//			ssTop << "UPDATE linde_receive_top_storage_info SET full_storage_num = " << full_storage_num << ",state = '" << state << "' WHERE storage_column = '" << storage_column << "'";
//			_bstr_t SQL2 = ssTop.str().c_str();
//			wcsAdo_.ExecuteSQL(SQL2);
//		}
//	}
//	catch (_com_error &e)
//	{
//		std::cout << "updateTopStorage" << e.ErrorMessage() << std::endl;
//		std::cout << e.Description() << std::endl;
//		return false;
//	}
//	return true;
//}
//
//bool WcsDatabase::deleteFailedOrder(std::string wcs_task_id)
//{
//	int row_count = 0;
//	std::stringstream ss;
//
//	ss << "SELECT COUNT(*) FROM linde_order_info WHERE WCS_TASK_ID = " << wcs_task_id << "";
//	_bstr_t SQL = ss.str().c_str();
//	recordPtr_ = wcsAdo_.GetRecordSet(SQL);
//
//	try {
//		if (recordPtr_) {
//			row_count = (int)recordPtr_->GetCollect("count(*)");
//		}
//		else
//		{
//			std::cout << "Cant get Recordset!" << std::endl;
//		}
//		if (row_count == 1)
//		{
//			std::stringstream ssTop;
//			ssTop << "DELETE  FROM linde_order_info  WHERE WCS_TASK_ID = " << wcs_task_id << "";
//			_bstr_t SQL2 = ssTop.str().c_str();
//			wcsAdo_.ExecuteSQL(SQL2);
//		}
//	}
//	catch (_com_error &e)
//	{
//		std::cout << "deleteFailedOrder" << e.ErrorMessage() << std::endl;
//		std::cout << e.Description() << std::endl;
//		return false;
//	}
//	return true;
//}
//
