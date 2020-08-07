#ifndef ADOBO_H_  
#define ADOBO_H_

#include<string>
#include <vector>
#import "c:\\program files\\common files\\system\\ado\\msado15.dll" no_namespace rename("EOF","adoEOF")



typedef enum {
	ACS_DB = 1,
	WCS_DB = 2


}ADO_Database;

class ADOcon
{
public:
	ADOcon(void);
	~ADOcon(void);

public:
	//Add a pointer to Connection:
	_ConnectionPtr m_pConnection;
	//add an pointer to Recordset:
	_RecordsetPtr m_pRecordset;
public:
	// initial connection
	void OnInitADOConn(ADO_Database Database_Type);
	// "get record" query
	_RecordsetPtr& GetRecordSet(_bstr_t bstrSQL);
	// "execute" query
	BOOL ExecuteSQL(_bstr_t bstrSQL);

	void Set_WMS_Connection_info(std::string DSN, std::string ServerIP, std::string Database_Name, std::string User_Name, std::string Password);

	void Set_AMS_Connection_info(std::string DSN, std::string ServerIP, std::string Database_Name, std::string User_Name, std::string Password);

	void splitString2(const std::string& s, std::vector<std::string>& v, const std::string& c);

	void ExitConnect();

	int DBID_;

private:
	std::string WMS_DSN;
	std::string WMS_ServerIP;
	std::string WMS_Database_Name;
	std::string WMS_User_Name;
	std::string WMS_Password;

	std::string AGV_Management_DSN;
	std::string AGV_Managemnet_ServerIP;
	std::string AGV_Managemnet_Database_Name;
	std::string AGV_Managemnet_User_Name;
	std::string AGV_Managemnet_Password;

	ADO_Database Current_Con_;
};




#endif  #pragma once
