#ifndef _DELETEOPERATION_
#define _DELETEOPERATION_

#include <boost/serialization/singleton.hpp>
#include <map>
#include "ADODatabased.h"
#include "ManageDefine.h"

class DeleteOperation
{

public:
	DeleteOperation();

	~DeleteOperation();

	void setDeleteAdo(ADOcon* Delete_Con);

	bool deleteFailedOrder(std::string wcs_task_id);
private:

	ADOcon DeleteAdo_;
	_RecordsetPtr recordPtr_;
};
typedef boost::serialization::singleton<DeleteOperation> SingletonDeleteOperation;

#define DELETE_OPERATION SingletonDeleteOperation::get_mutable_instance()
#endif