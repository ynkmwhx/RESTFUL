#ifndef _WCS_Database_EDWARD_
#define _WCS_Database_EDWARD_

#include <map>
#include "ADODatabased.h"
#include "ManageDefine.h"



class WcsDatabase
{

public:
	WcsDatabase();

	~WcsDatabase();

	void setWcsAdo(ADOcon ADO);

	/*void findOrderStatus(std::string wcs_task_id);

	bool databseDispatchTask (Order order);

	bool updateTopStorage(std::string storage_column,int full_storage_num,std::string state);

	bool deleteFailedOrder(std::string wcs_task_id);*/
private:

	ADOcon wcsAdo_;
	_RecordsetPtr recordPtr_;
};

#endif