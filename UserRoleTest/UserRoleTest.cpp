// UserRoleTest.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <iostream>

//#define _AACUser_SQLITEWRAPPER_DYN
#include "AACUserRole.h"
#include<Windows.h>

using namespace AACUser;



int main()
{
	//char databasePath[_MAX_FNAME] = "\\\\10.170.96.14\\SZLGCCM_Share\\11.SW\\UserRoleDatabase\\AAC_UserRoleSamples.db";
	char databasePath[_MAX_FNAME] = "E:\\vsproject\\AAC_UserRole\\Release\\AAC_UserData.db";
	//char databasePath[_MAX_FNAME] = "\\\\10.40.35.15\\中恒光学测试软件\\UserRoleDatabase\\AAC_UserRoleSamples_test.db";
	//char databasePath[_MAX_FNAME] = "AAC_UserRoleSamples_test.db";
	//char databasePath[_MAX_FNAME] = "\\\\10.170.96.14\\SZLGCCM_Share\\11.SW\\ServerTest\\AAC_UserRoleSamples_test.db";


	char gtime[32] = "";
	int golden_type = 0;
	bool isok = false;

	//AACUserRole *pt = new AACUserRole(); //用默认库
	AACUserRole *pt = new AACUserRole(databasePath);//自定义库路径

	USER_DATA user_data;
	user_data.userid = "60057357";
	user_data.username = "张林";
	user_data.userpassword = "666666";
	user_data.rolelevel = ROLE_SUPER_ADMIN;
	user_data.stafftype = STAFF_SW;
	isok = pt->insertUser(user_data);
	if(isok)
	{ 
		std::cerr << "insert ok " << std::endl;
	}
	else
	{
		std::cerr << "insert ng " << std::endl;
	}

	user_data.userid = "60057353";
	user_data.username = "张洪忠";
	user_data.userpassword = "777777";
	user_data.rolelevel = ROLE_MODIFY;
	user_data.stafftype = STAFF_TE;
	isok = pt->insertUser(user_data);
	if (isok)
	{
		std::cerr << "insert ok " << std::endl;
	}
	else
	{
		std::cerr << "insert ng " << std::endl;
	}

	USER_DATA get_data;
	get_data.userid = "60057357";
	isok = pt->getUser(&get_data);
	if (isok)
	{
		std::cerr << "get ok " << get_data.username.c_str() << std::endl;
	}
	else
	{
		std::cerr << "get ng " << std::endl;
	}


	std::vector<AACUser::USER_DATA> user_list;
	std::vector<AACUser::USER_DATA>().swap(user_list);
	isok = pt->getUser(user_list);
	if (isok)
	{
		for (int i = 0; i < user_list.size(); i++)
		{
			std::cerr << "[vector]get ok " << user_list[i].userid.c_str() << std::endl;
		}
	}


	USER_DATA update_data;
	update_data.userid = "600333";
	update_data.username = "444444";
	update_data.userpassword= "666666";
	update_data.stafftype = AACUser::STAFF_ME;
	update_data.rolelevel = AACUser::ROLE_UPLOAD;

	isok = pt->updateUser(update_data);
	if (isok)
	{
		std::cerr << "update ok " << get_data.username.c_str() << std::endl;
	}
	else
	{
		std::cerr << "update ng " << std::endl;
	}

	HISTORY_DATA history_data;
	history_data.userid = "60057357";
	history_data.projectname = "P05FX01";
	history_data.filename = "P05FX01_config.ini";
	history_data.mcontent = "A: 000000.586728, 1606924781994837400, 00:00:00.586, calc_step_data imagedata sharedMemoryName:AutoFocusMEM06_1_0";

	isok = pt->insertHistory(history_data);
	if (isok)
	{
		std::cerr << "intsert history ok " << get_data.username.c_str() << std::endl;
	}
	else
	{
		std::cerr << "intsert history  ng " << std::endl;
	}

	vector<AACUser::HISTORY_DATA> get_history_data;
	isok = pt->getHistoryUser("60057357", get_history_data);
	if (isok)
	{
		std::cerr << "get history ok " << get_history_data[0].mcontent.c_str() << std::endl;
	}
	else
	{
		std::cerr << "get history  ng " << std::endl;
	}



	//std::string userid  = "60057357";
	//isok = pt->deleteUser(userid);
	//if (isok)
	//{
	//	std::cerr << "delete ok " << std::endl;
	//}
	//else
	//{
	//	std::cerr << "delet ng " << std::endl;
	//}

//-------------------------------------------------------------

	std::cerr << "test end" << std::endl;
	delete pt;
	std::cin.get();
    return 0;
}

