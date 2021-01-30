#ifndef QHDataBaseLib_H
#define QHDataBaseLib_H

#define _AACGolden_SQLITE3_EXPORT

#ifndef HAS_PASSWORD
#define HAS_PASSWORD 0
#endif

#include <string>
#include <atltime.h>
#include "QHDataBase.h"
#include "SQLiteDatabase.h"
#include "SQLiteStatement.h"
#include "SQLiteException.h"

namespace QHDB
{

#if HAS_PASSWORD
	bool mHasPassWord = true;
#else
	bool mHasPassWord = false;
#endif

	char defDatabasePath[_MAX_PATH] = "AAC_UserData.db";
	char defKey[32] = "ZL";

	std::string  CstringToString(CString Cstr)
	{
		string str = CT2A(Cstr.GetBuffer());
		Cstr.ReleaseBuffer();
		return str;
	}

	class _SQLiteWrapperExport QHDataBaseLib
	{
	public:
		
		QHDataBaseLib();//用默认库
		QHDataBaseLib(char* dataPath);//自定义库路径
		QHDataBaseLib(char* dataPath, char* key);//自定义库路径和密码
		~QHDataBaseLib();
		char *databasePath;

		//返回false表示数据库无此用户

		//base
		bool insertBaseData(DB_BASE base_data);
		bool getBaseData(DB_BASE *base_data);//获取单个信息
		bool getBaseData(std::vector<DB_BASE> &base_data);//获取所有信息
		bool updateBaseData(DB_BASE base_data);
		bool deleteBaseData(int base_num);

		//chicang
		bool insertChicangData(DB_CHICANG chicang_data);
		bool getChicangData(int base_num, std::vector<DB_CHICANG> &chicang_data);
		bool deleteChicangData(int base_num);

		//修改数据库密码专用
		bool setPassWord(std::string oldKey, std::string newKey, int mode); //修改密码的软件专用

	private:
		std::string m_key;
	};
};

#endif 

