#include <iostream>
#include <exception>

#include "QHDataBaseLib.h"

#define OPEN_DEBUG 1

namespace QHDB
{

	QHDataBaseLib::QHDataBaseLib()
	{
		databasePath = defDatabasePath;
		if (mHasPassWord)
		{
			m_key = defKey;
		}
	}

	QHDataBaseLib::QHDataBaseLib(char* dataPath)
	{
		databasePath = dataPath;
		if (mHasPassWord)
		{
			m_key = defKey;
		}
	}

	QHDataBaseLib::QHDataBaseLib(char* dataPath, char* key)
	{
		databasePath = dataPath;
		if (mHasPassWord)
		{
			m_key = key;
		}
	}


	QHDataBaseLib::~QHDataBaseLib()
	{
	}


	bool QHDataBaseLib::insertBaseData(DB_BASE base_data)
	{
		int t_count = 1;
		bool flag = false;

		//DB_BASE t_baseData;
		//t_userData.userid = user_data.userid;
		//flag = getUser(&t_userData); //防止数据重复插入
		//if (flag)
		//{
		//	return false;
		//}

		if (base_data.base_bianma.length() == 0 || base_data.base_multiple == 0 || base_data.base_price == 0 ||
			base_data.base_step_value == 0)
		{
			return false;
		}
			
		try
		{
			// create and open database
			SQLiteDatabase *pDatabase;
			if (mHasPassWord)
				pDatabase = new SQLiteDatabase(databasePath, SQLITE_OPEN_READWRITE, m_key);
			else
				pDatabase = new SQLiteDatabase(databasePath, SQLITE_OPEN_READWRITE, 0);
			// create statement instance for sql queries/statements
			SQLiteStatement *pStmt = new SQLiteStatement(pDatabase);
			//version = pDatabase->GetLibVersionNumber();

			CTime tm = CTime::GetCurrentTime();
			CString gtime = tm.Format(L"%Y-%m-%d %H:%M:%S");
			std::string time = CstringToString(gtime);

			// insert some data with Bind..() methods	
			pStmt->Sql("INSERT INTO base (base_bianma, base_multiple, base_price, base_step_value, base_steps_limit, base_profit_limit, base_loss_cut, base_start_time) VALUES(?, ?, ?, ?, ?, ?, ?, ?);");
			pStmt->BindString(1, base_data.base_bianma);
			pStmt->BindInt(2, base_data.base_multiple);
			pStmt->BindInt(3, base_data.base_price);
			pStmt->BindInt(4, base_data.base_step_value);
			pStmt->BindInt(5, base_data.base_steps_limit);
			pStmt->BindInt(6, base_data.base_profit_limit);
			pStmt->BindInt(7, base_data.base_loss_cut);
			pStmt->BindString(8, time);
			// executes the INSERT statement and cleans-up automatically
			pStmt->ExecuteAndFree();

			// clean-up
			delete pStmt;		
			delete pDatabase;

		}
		catch (SQLiteException &exception)
		{
#if OPEN_DEBUG
			std::cerr << "\nException Occured" << std::endl;
			exception.Show();
			std::cerr << "SQLite result code: " << exception.GetSqliteResultCode() << std::endl;
#endif
			t_count = 0;
		}

		if (t_count == 1)
			return true;
		else
			return false;
	}

	bool QHDataBaseLib::getBaseData(DB_BASE *base_data)
	{
		int t_count = 0;

		try
		{
			// create and open database
			SQLiteDatabase *pDatabase;
			if (mHasPassWord)
				pDatabase = new SQLiteDatabase(databasePath, SQLITE_OPEN_READWRITE, m_key);
			else
				pDatabase = new SQLiteDatabase(databasePath, SQLITE_OPEN_READWRITE, 0);
			// create statement instance for sql queries/statements
			SQLiteStatement *pStmt = new SQLiteStatement(pDatabase);
			//version = pDatabase->GetLibVersionNumber();
			char sqlCmd[_MAX_FNAME];
			sprintf(sqlCmd, "SELECT * FROM base WHERE base_num = %d;", base_data->base_num);

			pStmt->Sql(sqlCmd);

			while (pStmt->FetchRow())
			{
				base_data->base_bianma = pStmt->GetColumnString("base_bianma");
				base_data->base_multiple = pStmt->GetColumnInt("base_multiple");
				base_data->base_price = pStmt->GetColumnInt("base_price");
				base_data->base_step_value = pStmt->GetColumnInt("base_step_value");
				base_data->base_steps_limit = pStmt->GetColumnInt("base_steps_limit");
				base_data->base_profit_limit = pStmt->GetColumnInt("base_profit_limit");
				base_data->base_loss_cut = pStmt->GetColumnInt("base_loss_cut");
				base_data->base_final_profit = pStmt->GetColumnInt("base_final_profit");
				base_data->base_start_time = pStmt->GetColumnString("base_start_time");
				base_data->base_end_time = pStmt->GetColumnString("base_end_time");

				t_count += 1;
			}

			pStmt->FreeQuery();

			// ---------------------------------------------------------------------------------------------------------
			// clean-up
			delete pStmt;
			delete pDatabase;
		}
		catch (SQLiteException &exception)
		{
#if OPEN_DEBUG
			std::cerr << "\nException Occured" << std::endl;
			exception.Show();
			std::cerr << "SQLite result code: " << exception.GetSqliteResultCode() << std::endl;
#endif
			t_count = 0;
		}

		if (t_count == 1)
			return true;
		else
			return false;
	}

	bool QHDataBaseLib::getBaseData(std::vector<DB_BASE> &base_data)
	{
		int t_count = 0;
		try
		{
			// create and open database
			SQLiteDatabase *pDatabase;
			if (mHasPassWord)
				pDatabase = new SQLiteDatabase(databasePath, SQLITE_OPEN_READWRITE, m_key);
			else
				pDatabase = new SQLiteDatabase(databasePath, SQLITE_OPEN_READWRITE, 0);
			// create statement instance for sql queries/statements
			SQLiteStatement *pStmt = new SQLiteStatement(pDatabase);
			//version = pDatabase->GetLibVersionNumber();
			char sqlCmd[_MAX_FNAME];
			sprintf(sqlCmd, "SELECT * FROM base ORDER BY rowid ASC;");

			pStmt->Sql(sqlCmd);
			DB_BASE t_data;

			while (pStmt->FetchRow())
			{
				t_data.base_num = pStmt->GetColumnInt("base_num");
				t_data.base_bianma = pStmt->GetColumnString("base_bianma");
				t_data.base_multiple = pStmt->GetColumnInt("base_multiple");
				t_data.base_price = pStmt->GetColumnInt("base_price");
				t_data.base_step_value = pStmt->GetColumnInt("base_step_value");
				t_data.base_steps_limit = pStmt->GetColumnInt("base_steps_limit");
				t_data.base_profit_limit = pStmt->GetColumnInt("base_profit_limit");
				t_data.base_loss_cut = pStmt->GetColumnInt("base_loss_cut");
				t_data.base_final_profit = pStmt->GetColumnInt("base_final_profit");
				t_data.base_start_time = pStmt->GetColumnString("base_start_time");
				t_data.base_end_time = pStmt->GetColumnString("base_end_time");

				t_count += 1;
				base_data.push_back(t_data);
			}

			pStmt->FreeQuery();

			// ---------------------------------------------------------------------------------------------------------
			// clean-up
			delete pStmt;
			delete pDatabase;
		}
		catch (SQLiteException &exception)
		{
#if OPEN_DEBUG
			std::cerr << "\nException Occured" << std::endl;
			exception.Show();
			std::cerr << "SQLite result code: " << exception.GetSqliteResultCode() << std::endl;
#endif
			t_count = 0;
		}

		if (t_count >= 1)
			return true;
		else
			return false;
	}

	bool QHDataBaseLib::updateBaseData(DB_BASE base_data)
	{
		bool flag = false;
		int t_count = 1;

		DB_BASE t_baseData;
		t_baseData.base_num = base_data.base_num;
		flag = getBaseData(&t_baseData); //防止数据重复插入
		if (flag)
		{
			if (t_baseData.base_bianma.length() != 0 && t_baseData.base_bianma != base_data.base_bianma)
			{
				t_baseData.base_bianma = base_data.base_bianma;
			}

			if (t_baseData.base_multiple != 0 && t_baseData.base_multiple != base_data.base_multiple)
			{
				t_baseData.base_multiple = base_data.base_multiple;
			}

			if (t_baseData.base_price != 0 && t_baseData.base_price != base_data.base_price)
			{
				t_baseData.base_price = base_data.base_price;
			}

			if (t_baseData.base_step_value != 0 && t_baseData.base_step_value != base_data.base_step_value)
			{
				t_baseData.base_step_value = base_data.base_step_value;
			}

			if (t_baseData.base_steps_limit != 0 && t_baseData.base_steps_limit != base_data.base_steps_limit)
			{
				t_baseData.base_steps_limit = base_data.base_steps_limit;
			}

			if (t_baseData.base_profit_limit != 0 && t_baseData.base_profit_limit != base_data.base_profit_limit)
			{
				t_baseData.base_profit_limit = base_data.base_profit_limit;
			}

			if (t_baseData.base_loss_cut != 0 && t_baseData.base_loss_cut != base_data.base_loss_cut)
			{
				t_baseData.base_loss_cut = base_data.base_loss_cut;
			}

			if (t_baseData.base_final_profit != 0 && t_baseData.base_final_profit != base_data.base_final_profit)
			{
				t_baseData.base_final_profit = base_data.base_final_profit;
			}

			if (t_baseData.base_start_time.length() != 0 && t_baseData.base_start_time != base_data.base_start_time)
			{
				t_baseData.base_start_time = base_data.base_start_time;
			}

			if (t_baseData.base_end_time.length() != 0 && t_baseData.base_end_time != base_data.base_end_time)
			{
				t_baseData.base_end_time = base_data.base_end_time;
			}
		}
		else
		{
			return false;
		}

		try
		{
			// create and open database
			SQLiteDatabase *pDatabase;
			if (mHasPassWord)
				pDatabase = new SQLiteDatabase(databasePath, SQLITE_OPEN_READWRITE, m_key);
			else
				pDatabase = new SQLiteDatabase(databasePath, SQLITE_OPEN_READWRITE, 0);
			// create statement instance for sql queries/statements
			SQLiteStatement *pStmt = new SQLiteStatement(pDatabase);
			//version = pDatabase->GetLibVersionNumber();

			CTime tm = CTime::GetCurrentTime();
			CString gtime = tm.Format(L"%Y-%m-%d %H:%M:%S");

			pStmt->Sql("UPDATE base SET base_bianma=@base_bianma, \
				                        base_multiple=@base_multiple, \
										base_price=@base_price, \
										base_step_value=@base_step_value, \
										base_steps_limit=@base_steps_limit, \
										base_profit_limit=@base_profit_limit,\
										base_loss_cut=@base_loss_cut,\
									    base_final_profit=@base_final_profit, \
										base_start_time=@base_start_time,\
										base_end_time=@base_end_time,\
										WHERE base_num=@base_num");

			// bind an integer to the prepared statement			
			pStmt->BindString(1, base_data.base_bianma);
			pStmt->BindInt(2, base_data.base_multiple);
			pStmt->BindInt(3, base_data.base_price);
			pStmt->BindInt(4, base_data.base_step_value);
			pStmt->BindInt(5, base_data.base_steps_limit);
			pStmt->BindInt(6, base_data.base_profit_limit);
			pStmt->BindInt(7, base_data.base_loss_cut);
			pStmt->BindInt(8, base_data.base_final_profit);
			pStmt->BindString(9, base_data.base_start_time);
			pStmt->BindString(10, base_data.base_end_time);
			pStmt->BindInt(11, base_data.base_num);
			// execute it and clean-up
			pStmt->ExecuteAndFree();

			// ---------------------------------------------------------------------------------------------------------
			// clean-up
			delete pStmt;
			delete pDatabase;
		}
		catch (SQLiteException &exception)
		{
#if OPEN_DEBUG
			std::cerr << "\nException Occured" << std::endl;
			exception.Show();
			std::cerr << "SQLite result code: " << exception.GetSqliteResultCode() << std::endl;
#endif
			t_count = 0;
		}

		if (t_count == 1)
			return true;
		else
			return false;
	}

	bool QHDataBaseLib::deleteBaseData(int base_num)
	{
		int t_count = 0;
		bool flag = false;

		//DB_BASE t_baseData;
		//t_baseData.base_num = base_num;
		//flag = getBaseData(&t_baseData); 
		//if (!flag)
		//{
		//	return false;
		//}

		try
		{
			// create and open database
			SQLiteDatabase *pDatabase;
			if (mHasPassWord)
				pDatabase = new SQLiteDatabase(databasePath, SQLITE_OPEN_READWRITE, m_key);
			else
				pDatabase = new SQLiteDatabase(databasePath, SQLITE_OPEN_READWRITE, 0);
			// create statement instance for sql queries/statements
			SQLiteStatement *pStmt = new SQLiteStatement(pDatabase);
			//version = pDatabase->GetLibVersionNumber();

			char sqlcmd[_MAX_FNAME];
			sprintf(sqlcmd, "DELETE FROM base WHERE base_num = %d", base_num);

			// DELETE statement and get afterwards the number of affected rows
			pStmt->SqlStatement(sqlcmd);
			t_count = pDatabase->GetDatabaseChanges();

			// ---------------------------------------------------------------------------------------------------------
			// clean-up
			delete pStmt;
			delete pDatabase;
		}
		catch (SQLiteException &exception)
		{
#if OPEN_DEBUG
			std::cerr << "\nException Occured" << std::endl;
			exception.Show();
			std::cerr << "SQLite result code: " << exception.GetSqliteResultCode() << std::endl;
#endif
			t_count = 0;
		}

		if (t_count > 0)
			return true;
		else
			return false;
	}

//////////////////chicang start /////////////
	bool QHDataBaseLib::insertChicangData(DB_CHICANG chicang_data)
	{
		int t_count = 1;
		bool flag = false;

		if (chicang_data.open_price == 0 || chicang_data.open_dir == 0)
		{
			return false;
		}

		vector<DB_CHICANG> t_data;
		flag = getChicangData(chicang_data.base_num, t_data); //防止数据重复插入
		if (flag)
		{
			for (UINT i = 0; i < t_data.size(); i++)
			{
				if (t_data[i].open_price == chicang_data.open_price && t_data[i].open_dir == chicang_data.open_dir)
				{
					return false;
				}
			}		
		}

		try
		{
			// create and open database
			SQLiteDatabase *pDatabase;
			if (mHasPassWord)
				pDatabase = new SQLiteDatabase(databasePath, SQLITE_OPEN_READWRITE, m_key);
			else
				pDatabase = new SQLiteDatabase(databasePath, SQLITE_OPEN_READWRITE, 0);
			// create statement instance for sql queries/statements
			SQLiteStatement *pStmt = new SQLiteStatement(pDatabase);
			//version = pDatabase->GetLibVersionNumber();

			CTime tm = CTime::GetCurrentTime();
			CString gtime = tm.Format(L"%Y-%m-%d %H:%M:%S");
			std::string time = CstringToString(gtime);

			// insert some data with Bind..() methods	
			pStmt->Sql("INSERT INTO chicang (base_num, open_price, open_dir, open_time) VALUES(?, ?, ?, ?);");
			pStmt->BindInt(1, chicang_data.base_num);
			pStmt->BindInt(2, chicang_data.open_price);
			pStmt->BindInt(3, chicang_data.open_dir);
			pStmt->BindString(4, time);
			// executes the INSERT statement and cleans-up automatically
			pStmt->ExecuteAndFree();

			// clean-up
			delete pStmt;
			delete pDatabase;

		}
		catch (SQLiteException &exception)
		{
#if OPEN_DEBUG
			std::cerr << "\nException Occured" << std::endl;
			exception.Show();
			std::cerr << "SQLite result code: " << exception.GetSqliteResultCode() << std::endl;
#endif
			t_count = 0;
		}

		if (t_count == 1)
			return true;
		else
			return false;
	}


	bool QHDataBaseLib::getChicangData(int base_num, std::vector<DB_CHICANG> &chicang_data)
	{
		int t_count = 0;
		try
		{
			// create and open database
			SQLiteDatabase *pDatabase;
			if (mHasPassWord)
				pDatabase = new SQLiteDatabase(databasePath, SQLITE_OPEN_READWRITE, m_key);
			else
				pDatabase = new SQLiteDatabase(databasePath, SQLITE_OPEN_READWRITE, 0);
			// create statement instance for sql queries/statements
			SQLiteStatement *pStmt = new SQLiteStatement(pDatabase);
			//version = pDatabase->GetLibVersionNumber();
			char sqlCmd[_MAX_FNAME];
			sprintf(sqlCmd, "SELECT * FROM chicang where base_num = %d ORDER BY rowid ASC;", base_num);

			pStmt->Sql(sqlCmd);
			DB_CHICANG t_data;

			while (pStmt->FetchRow())
			{
				t_data.base_num = pStmt->GetColumnInt("base_num");
				t_data.open_price = pStmt->GetColumnInt("open_price");
				t_data.open_dir = pStmt->GetColumnInt("open_dir");
				t_data.open_time = pStmt->GetColumnString("open_time");
				t_data.close_time = pStmt->GetColumnString("close_time");
				t_count += 1;
				chicang_data.push_back(t_data);
			}

			pStmt->FreeQuery();

			// ---------------------------------------------------------------------------------------------------------
			// clean-up
			delete pStmt;
			delete pDatabase;
		}
		catch (SQLiteException &exception)
		{
#if OPEN_DEBUG
			std::cerr << "\nException Occured" << std::endl;
			exception.Show();
			std::cerr << "SQLite result code: " << exception.GetSqliteResultCode() << std::endl;
#endif
			t_count = 0;
		}

		if (t_count >= 1)
			return true;
		else
			return false;
	}

	bool QHDataBaseLib::deleteChicangData(int base_num)
	{
		int t_count = 0;
		bool flag = false;

		//DB_BASE t_baseData;
		//t_baseData.base_num = base_num;
		//flag = getBaseData(&t_baseData); 
		//if (!flag)
		//{
		//	return false;
		//}

		try
		{
			// create and open database
			SQLiteDatabase *pDatabase;
			if (mHasPassWord)
				pDatabase = new SQLiteDatabase(databasePath, SQLITE_OPEN_READWRITE, m_key);
			else
				pDatabase = new SQLiteDatabase(databasePath, SQLITE_OPEN_READWRITE, 0);
			// create statement instance for sql queries/statements
			SQLiteStatement *pStmt = new SQLiteStatement(pDatabase);
			//version = pDatabase->GetLibVersionNumber();

			char sqlcmd[_MAX_FNAME];
			sprintf(sqlcmd, "DELETE FROM chicang WHERE base_num = %d", base_num);

			// DELETE statement and get afterwards the number of affected rows
			pStmt->SqlStatement(sqlcmd);
			t_count = pDatabase->GetDatabaseChanges();

			// ---------------------------------------------------------------------------------------------------------
			// clean-up
			delete pStmt;
			delete pDatabase;
		}
		catch (SQLiteException &exception)
		{
#if OPEN_DEBUG
			std::cerr << "\nException Occured" << std::endl;
			exception.Show();
			std::cerr << "SQLite result code: " << exception.GetSqliteResultCode() << std::endl;
#endif
			t_count = 0;
		}

		if (t_count > 0)
			return true;
		else
			return false;
	}

//////////////////chicang end/////////////
	bool QHDataBaseLib::setPassWord(std::string oldKey, std::string newKey, int mode)
	{
		bool flag = TRUE;

		try
		{
			// create and open database
			SQLiteDatabase *pDatabase = new SQLiteDatabase(databasePath, SQLITE_OPEN_READWRITE, oldKey, newKey, mode);
			// create statement instance for sql queries/statements
			//SQLiteStatement *pStmt = new SQLiteStatement(pDatabase);
			//version = pDatabase->GetLibVersionNumber();

			// ---------------------------------------------------------------------------------------------------------
			// clean-up
			//delete pStmt;
			delete pDatabase;
		}
		catch (SQLiteException &exception)
		{
#if OPEN_DEBUG
			std::cerr << "\nException Occured" << std::endl;
			exception.Show();
			std::cerr << "SQLite result code: " << exception.GetSqliteResultCode() << std::endl;
#endif
			flag = FALSE;
		}

			return flag;
	}
}


///////////////////////////////API//////////////////////////////////////////

QHDataBase::QHDataBase()//用默认库
{
	mark = new QHDB::QHDataBaseLib(); 
}
QHDataBase::QHDataBase(char* dataPath)//自定义库路径
{
	mark = new QHDB::QHDataBaseLib(dataPath);
}
QHDataBase::QHDataBase(char* dataPath, char* key)//自定义库路径和密码
{
	mark = new QHDB::QHDataBaseLib(dataPath, key);
}
QHDataBase::~QHDataBase()
{
	delete mark;
}

//操作成功返回: true  失败返回: false
bool QHDataBase::insertBaseData(QHDB::DB_BASE base_data)
{
	return mark->insertBaseData(base_data);
}

bool QHDataBase::getBaseData(QHDB::DB_BASE *base_data)
{
	return mark->getBaseData(base_data);
}

bool QHDataBase::getBaseData(std::vector<QHDB::DB_BASE> &base_data)
{
	return mark->getBaseData(base_data);
}

bool QHDataBase::updateBaseData(QHDB::DB_BASE base_data)
{
	return mark->updateBaseData(base_data);
}

bool QHDataBase::deleteBaseData(int base_num)
{
	return mark->deleteBaseData(base_num);
}

bool QHDataBase::insertChicangData(QHDB::DB_CHICANG chicang_data)
{
	return mark->insertChicangData(chicang_data);
}

bool QHDataBase::getChicangData(int base_num, std::vector<QHDB::DB_CHICANG> &chicang_data)
{
	return mark->getChicangData(base_num, chicang_data);
}

bool QHDataBase::deleteChicangData(int base_num)
{
	return mark->deleteChicangData(base_num);
}

bool QHDataBase::setPassWord(std::string oldKey, std::string newKey, int mode)
{
	return mark->setPassWord(oldKey, newKey, mode);
}
