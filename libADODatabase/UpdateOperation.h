#ifndef _UPDATEOPERATION_
#define _UPDATEOPERATION_

#include <boost/serialization/singleton.hpp>
#include <map>
#include "ADODatabased.h"
#include "ManageDefine.h"

class UpdateOperation
{

public:
	UpdateOperation();

	~UpdateOperation();

	void setUpdateAdo(ADOcon* UpdATe_Con);

	bool UpdateOperationAbortWaitingOrder(Order current_order);

	bool UpdateOperationRecoverWeightInfo(Weight_Info current_weight);
private:

	ADOcon UpdateAdo_;
	_RecordsetPtr recordPtr_;
};
typedef boost::serialization::singleton<UpdateOperation> SingletonUpdateOperation;

#define UPDATE_OPERATION SingletonUpdateOperation::get_mutable_instance()
#endif