#include "stdafx.h"
#include <iostream>
#include <sstream>
#include "QueryOperation.h"

QueryOperation::QueryOperation()
{
}

QueryOperation::~QueryOperation()
{
}

void QueryOperation::setQueryWcsAdo(ADOcon* Query_Wcs_Con)
{
	 QueryWcsAdo_ = *Query_Wcs_Con;
}

void QueryOperation::setQueryAgvsAdo(ADOcon* Query_Agvs_Con)
{
	QueryAgvsAdo_ = *Query_Agvs_Con;
}

bool QueryOperation::queryOrderStatus(Order &current_order)
{
	int row_count = 0;
	std::stringstream ss;
	std::stringstream ss2;

	ss << "SELECT COUNT(*) FROM kh_report_order_info WHERE ORDER_ID = "<< current_order.Order_ID_ << " AND TYPE ='CARRY' ORDER BY ID DESC LIMIT 0,1 ";
	_bstr_t SQL = ss.str().c_str();
	recordPtr_ = QueryWcsAdo_.GetRecordSet(SQL);

	try {
		if (recordPtr_) {
			row_count = (int)recordPtr_->GetCollect("COUNT(*)");
		}
		else
		{
			std::cout << "Cant get Recordset!" << std::endl;
		}
		if (row_count != 0)
		{
			ss2 << "SELECT * FROM kh_report_order_info WHERE ORDER_ID = " << current_order.Order_ID_ << " AND TYPE ='CARRY' ORDER BY ID DESC LIMIT 0,1 ";
			_bstr_t SQL2 = ss2.str().c_str();
			recordPtr_ = QueryWcsAdo_.GetRecordSet(SQL2);

			current_order.Order_ID_ = atoi(_bstr_t(recordPtr_->Fields->GetItem(_variant_t("ORDER_ID"))->Value));
			current_order.AGV_ID_ = atoi(_bstr_t(recordPtr_->Fields->GetItem(_variant_t("AGV_ID"))->Value));
			current_order.START_ = (std::string)(_bstr_t)(recordPtr_->Fields->GetItem(_variant_t("START"))->Value);
			current_order.TARGET_ = (std::string)(_bstr_t)(recordPtr_->Fields->GetItem(_variant_t("TARGET"))->Value);
			current_order.PRIORITY_ = atoi(_bstr_t(recordPtr_->Fields->GetItem(_variant_t("PRIORITY"))->Value));
			current_order.STATUS_ = (std::string)(_bstr_t(recordPtr_->Fields->GetItem(_variant_t("STATUS"))->Value));
			current_order.MODE_ = (std::string)(_bstr_t)(recordPtr_->Fields->GetItem(_variant_t("MODE"))->Value);
			current_order.TYPE_ = (std::string)(_bstr_t)(recordPtr_->Fields->GetItem(_variant_t("TYPE"))->Value);
			current_order.ENTERDATE_ = (std::string)(_bstr_t)(recordPtr_->Fields->GetItem(_variant_t("ENTERDATE"))->Value);
			current_order.FINISHDATE_ = (std::string)(_bstr_t)(recordPtr_->Fields->GetItem(_variant_t("FINISHDATE"))->Value);
			return true;
		}
		else
		{
			return false;
		}
	}
	catch (_com_error &e) {
		std::cout << e.ErrorMessage() << "queryOrderStatus" << std::endl;
		std::cout << e.Description() << std::endl;
		return false;
	}

}

bool QueryOperation::queryAgvInfo(AGV &current_agv)
{
	int row_count = 0;
	int row_count2 = 0;
	std::stringstream ss;
	std::stringstream ss2;
	std::stringstream ss3;
	std::stringstream ss4;
	try {
		ss << "SELECT COUNT(*) FROM kh_agv_data WHERE agv_id = " << current_agv.AGV_ID_ << "";
		_bstr_t SQL = ss.str().c_str();
		recordPtr_ = QueryWcsAdo_.GetRecordSet(SQL);

		if (recordPtr_) 
		{
			row_count = (int)recordPtr_->GetCollect("COUNT(*)");
		}
		
		if (row_count == 1 )
		{
			ss2 << "SELECT * FROM kh_agv_data WHERE agv_id = " << current_agv.AGV_ID_ << "";
			_bstr_t SQL2= ss2.str().c_str();
			recordPtr_ = QueryWcsAdo_.GetRecordSet(SQL2);
			current_agv.AGV_ID_ = atoi(_bstr_t(recordPtr_->Fields->GetItem(_variant_t("AGV_ID"))->Value));
			current_agv.POS_X_ = atof(_bstr_t(recordPtr_->Fields->GetItem(_variant_t("pos_x"))->Value));
			current_agv.POS_Y_ = atof(_bstr_t(recordPtr_->Fields->GetItem(_variant_t("pos_y"))->Value));
			current_agv.POS_TH_ = atof(_bstr_t(recordPtr_->Fields->GetItem(_variant_t("pos_th"))->Value));
			current_agv.STATUS_ = atoi(_bstr_t(recordPtr_->Fields->GetItem(_variant_t("status"))->Value));
			current_agv.ERROR_CODE_ = atoi(_bstr_t(recordPtr_->Fields->GetItem(_variant_t("error_code"))->Value));
			current_agv.BATTERY_LEVEL_ = atof(_bstr_t(recordPtr_->Fields->GetItem(_variant_t("battery_level"))->Value));
			current_agv.AGV_TYPE_ = atof(_bstr_t(recordPtr_->Fields->GetItem(_variant_t("agv_type"))->Value));
			current_agv.IS_ONLINE_ = atof(_bstr_t(recordPtr_->Fields->GetItem(_variant_t("is_online"))->Value));
			current_agv.IS_SERVING_ = atof(_bstr_t(recordPtr_->Fields->GetItem(_variant_t("is_serving"))->Value));
			current_agv.IS_ASSIGNED_ = atof(_bstr_t(recordPtr_->Fields->GetItem(_variant_t("is_assigned"))->Value));
			current_agv.IP_ = (std::string)(_bstr_t)(recordPtr_->Fields->GetItem(_variant_t("ip"))->Value);
			current_agv.AT_NODE_ = atoi(_bstr_t(recordPtr_->Fields->GetItem(_variant_t("at_node"))->Value));
			current_agv.AT_STATION_ = (std::string)(_bstr_t)(recordPtr_->Fields->GetItem(_variant_t("at_station"))->Value);
			current_agv.STATION_ERROR_X_ = atof(_bstr_t(recordPtr_->Fields->GetItem(_variant_t("station_error_x"))->Value));
			current_agv.STATION_ERROR_Y_ = atoi(_bstr_t(recordPtr_->Fields->GetItem(_variant_t("station_error_y"))->Value));
			current_agv.STATION_ERROR_TH_ = atof(_bstr_t(recordPtr_->Fields->GetItem(_variant_t("station_error_th"))->Value));
			current_agv.TIMESTAMP_ = (std::string)(_bstr_t)(recordPtr_->Fields->GetItem(_variant_t("timestamp"))->Value);
			return true;
		}
		else
		{
			return false;
		}
	}
	catch (_com_error &e) {
		std::cout << e.ErrorMessage() << "queryAgvInfo" << std::endl;
		std::cout << e.Description() << std::endl;
		return false;
	}

}

bool QueryOperation::queryGoodsWeight(Weight_Info &current_weight)
{
	int row_count = 0;
	std::stringstream ss;
	std::stringstream ss2;

	ss << "SELECT COUNT(*) FROM kh_report_weight_info WHERE AGV_ID = " << current_weight.AGV_ID_ << " AND STATUS ='SUCCESS'";
	_bstr_t SQL = ss.str().c_str();
	recordPtr_ = QueryWcsAdo_.GetRecordSet(SQL);

	try {
		if (recordPtr_) {
			row_count = (int)recordPtr_->GetCollect("COUNT(*)");
		}
		else
		{
			std::cout << "Cant get Recordset!" << std::endl;
		}
		if (row_count == 1)
		{
			ss2 << "SELECT * FROM kh_report_weight_info WHERE AGV_ID = " << current_weight.AGV_ID_ << " AND STATUS ='SUCCESS'";
			_bstr_t SQL2 = ss2.str().c_str();
			recordPtr_ = QueryWcsAdo_.GetRecordSet(SQL2);

			current_weight.Good_Weight_ = atof(_bstr_t(recordPtr_->Fields->GetItem(_variant_t("WEIGHT"))->Value));
			current_weight.Status_ = (std::string)(_bstr_t)(recordPtr_->Fields->GetItem(_variant_t("STATUS"))->Value);
			
			return true;
		}
		else
		{
			return false;
		}
	}
	catch (_com_error &e) {
		std::cout << e.ErrorMessage() << "queryGoodsWeight" << std::endl;
		std::cout << e.Description() << std::endl;
		return false;
	}
}