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
		
		QHDataBaseLib();//��Ĭ�Ͽ�
		QHDataBaseLib(char* dataPath);//�Զ����·��
		QHDataBaseLib(char* dataPath, char* key);//�Զ����·��������
		~QHDataBaseLib();
		char *databasePath;

		//����false��ʾ���ݿ��޴��û�

		//base
		bool insertBaseData(DB_BASE base_data);
		bool getBaseData(DB_BASE *base_data);//��ȡ������Ϣ
		bool getBaseData(std::vector<DB_BASE> &base_data);//��ȡ������Ϣ
		bool updateBaseData(DB_BASE base_data);
		bool deleteBaseData(int base_num);

		//chicang
		bool insertChicangData(DB_CHICANG chicang_data);
		bool getChicangData(int base_num, std::vector<DB_CHICANG> &chicang_data);
		bool deleteChicangData(int base_num);

		//�޸����ݿ�����ר��
		bool setPassWord(std::string oldKey, std::string newKey, int mode); //�޸���������ר��

	private:
		std::string m_key;
	};
};

#endif 

