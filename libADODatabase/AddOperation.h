#ifndef _ADDOPERATION_
#define _ADDOPERATION_

#include <boost/serialization/singleton.hpp>
#include <map>
#include "ADODatabased.h"
#include "ManageDefine.h"

class AddOperation
{

public:
	AddOperation();

	~AddOperation();

	void setAddAdo(ADOcon* Add_Con);

	bool AddOperationDispatchTask(Order order);
private:

	ADOcon AddAdo_;
	_RecordsetPtr recordPtr_;
};
typedef boost::serialization::singleton<AddOperation> SingletonAddOperation;

#define ADD_OPERATION SingletonAddOperation::get_mutable_instance()
#endif