#ifndef _QUERYOPERATION_
#define _QUERYOPERATION_

#include <boost/serialization/singleton.hpp>
#include <map>
#include "ADODatabased.h"
#include "ManageDefine.h"

class QueryOperation
{

public:
	QueryOperation();

	~QueryOperation();

	void setQueryWcsAdo(ADOcon* Query_Wcs_Con);

	void setQueryAgvsAdo(ADOcon* Query_Agvs_Con);

	bool queryOrderStatus(Order &current_order);

	bool queryAgvInfo(AGV &current_agv);

	bool queryGoodsWeight(Weight_Info &current_weight);

private:

	ADOcon QueryWcsAdo_;
	ADOcon QueryAgvsAdo_;
	_RecordsetPtr recordPtr_;
	_RecordsetPtr recordPtr2_;
};
typedef boost::serialization::singleton<QueryOperation> SingletonQueryOperation;

#define QUERY_OPERATION SingletonQueryOperation::get_mutable_instance()
#endif
