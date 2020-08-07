#include "stdafx.h"
#include "ADODatabased.h"
#include "iostream"
#include <sstream>
#include <fstream>
#include <vector>
ADOcon::ADOcon(void)
{
	WMS_DSN = "Local";
	WMS_ServerIP = "127.0.0.1";
	WMS_Database_Name = "warehousedb";
	WMS_User_Name = "root";
	WMS_Password = "kunhou4081";

	AGV_Management_DSN = "Local";
	AGV_Managemnet_ServerIP = "127.0.0.1";
	AGV_Managemnet_Database_Name = "task_managementdb";
	AGV_Managemnet_User_Name = "root";
	AGV_Managemnet_Password = "kunhou4081";


	std::ifstream config_file("config.txt");
	if (!config_file.is_open())
	{
		std::cout << "can not load config file :" << std::endl;
	}
	else {
		std::string str;
		std::getline(config_file, str);
		while (str.length() > 3)
		{

			std::vector<std::string> vstr;

			splitString2(str, vstr, ":");

			if (vstr[0] == "AMS_DSN")
			{
				AGV_Management_DSN = vstr[1];
			}
			else if (vstr[0] == "AMS_ServerIP")
			{
				AGV_Managemnet_ServerIP = vstr[1];
			}
			else if (vstr[0] == "AMS_Database_Name")
			{
				AGV_Managemnet_Database_Name = vstr[1];
			}
			else if (vstr[0] == "AMS_User_Name")
			{
				AGV_Managemnet_User_Name = vstr[1];
			}
			else if (vstr[0] == "AMS_Password")
			{
				AGV_Managemnet_Password = vstr[1];
			}
			else if (vstr[0] == "WMS_DSN")
			{
				WMS_DSN = vstr[1];
			}
			else if (vstr[0] == "WMS_ServerIP")
			{
				WMS_ServerIP = vstr[1];
			}
			else if (vstr[0] == "WMS_Database_Name")
			{
				WMS_Database_Name = vstr[1];
			}
			else if (vstr[0] == "WMS_User_Name")
			{
				WMS_User_Name = vstr[1];
			}
			else if (vstr[0] == "WMS_Password")
			{
				WMS_Password = vstr[1];
			}
			std::getline(config_file, str);
		}
		Set_AMS_Connection_info(AGV_Management_DSN, AGV_Managemnet_ServerIP, AGV_Managemnet_Database_Name, AGV_Managemnet_User_Name, AGV_Managemnet_Password);
		Set_WMS_Connection_info(WMS_DSN, WMS_ServerIP, WMS_Database_Name, WMS_User_Name, WMS_Password);

	}

}

ADOcon::~ADOcon(void)
{
}

void  ADOcon::OnInitADOConn(ADO_Database Database_Type)
{
	//    
	Current_Con_ = Database_Type;
	::CoInitialize(NULL);

	std::stringstream AGV_Managemnet_Connection_Info;
	std::stringstream WMS_Connection_Info;
	AGV_Managemnet_Connection_Info << "DSN=" << AGV_Management_DSN << ";Server=" << AGV_Managemnet_ServerIP << ";Database=" << AGV_Managemnet_Database_Name;
	WMS_Connection_Info << "DSN=" << WMS_DSN << ";Server=" << WMS_ServerIP << ";Database=" << WMS_Database_Name;

	HRESULT hr;

	try
	{
		//  
		hr = m_pConnection.CreateInstance("ADODB.Connection");

		if (SUCCEEDED(hr))
		{

			m_pConnection->ConnectionTimeout = 600;// 
			m_pConnection->CommandTimeout = 120;// 

			if (Database_Type == ADO_Database::WCS_DB)
			{
				//m_pConnection->Open("DSN=Local;Server=127.0.0.1;Database=wms_greenleaf", "root", "1129", adModeUnknown); 
				m_pConnection->Open((_bstr_t)WMS_Connection_Info.str().c_str(), (_bstr_t)WMS_User_Name.c_str(), (_bstr_t)WMS_Password.c_str(), adModeUnknown);
			}
			else if (Database_Type == ADO_Database::ACS_DB)
			{
				m_pConnection->Open((_bstr_t)AGV_Managemnet_Connection_Info.str().c_str(), (_bstr_t)AGV_Managemnet_User_Name.c_str(), (_bstr_t)AGV_Managemnet_Password.c_str(), adModeUnknown);
			}
			else
				std::cout << "wrong Database ID!" << std::endl;

		}
	}
	catch (_com_error e)
	{
		std::cout << "Connect Error:" << e.Description() << std::endl;
	}
}

void ADOcon::Set_WMS_Connection_info(std::string DSN, std::string ServerIP, std::string Database_Name, std::string User_Name, std::string Password)
{
	WMS_DSN = DSN;
	WMS_ServerIP = ServerIP;
	WMS_Database_Name = Database_Name;

	WMS_User_Name = User_Name;
	WMS_Password = Password;

}

void ADOcon::Set_AMS_Connection_info(std::string DSN, std::string ServerIP, std::string Database_Name, std::string User_Name, std::string Password)
{
	AGV_Management_DSN = DSN;
	AGV_Managemnet_ServerIP = ServerIP;
	AGV_Managemnet_Database_Name = Database_Name;

	AGV_Managemnet_User_Name = User_Name;
	AGV_Managemnet_Password = Password;


}

_RecordsetPtr&  ADOcon::GetRecordSet(_bstr_t bstrSQL)
{
	try
	{
		//   
		if (m_pConnection == NULL)
			OnInitADOConn(Current_Con_);
		//   
		m_pRecordset.CreateInstance(__uuidof(Recordset));
		// 
		m_pRecordset->Open(bstrSQL, m_pConnection.GetInterfacePtr(), adOpenDynamic, adLockOptimistic, adCmdText);
	}
	// 
	catch (_com_error e)
	{
		std::cout << "GetRecordSet Error:" << e.Description() << std::endl;
	}
	//   

	return m_pRecordset;
}

BOOL ADOcon::ExecuteSQL(_bstr_t bstrSQL)
{
	// _variant_t RecordsAffected;  
	try
	{

		if (m_pConnection == NULL)
			OnInitADOConn(Current_Con_);

		m_pConnection->Execute(bstrSQL, NULL, adCmdText);

		return true;
	}
	catch (_com_error e)
	{
		std::cout << "ExecuteSQL Error:" << e.Description() << std::endl;
		return false;
	}
}

void ADOcon::ExitConnect()
{
	// 
	if (m_pRecordset != NULL)
	{
		m_pRecordset->Close();
		//m_pRecordset->Release();  
	}
	m_pConnection->Close();
	//m_pConnection->Release();  
	//   
	::CoUninitialize();
}


void ADOcon::splitString2(const std::string& s, std::vector<std::string>& v, const std::string& c)
{
	std::string::size_type pos1, pos2;
	pos2 = s.find(c);
	pos1 = 0;
	while (std::string::npos != pos2)
	{
		v.push_back(s.substr(pos1, pos2 - pos1));

		pos1 = pos2 + c.size();
		pos2 = s.find(c, pos1);
	}
	if (pos1 != s.length())
		v.push_back(s.substr(pos1));
}