#ifndef QHDataBase_H
#define QHDataBase_H
#include <vector>

using namespace std;

#if _WIN32
	#define _CDECL _cdecl
	#if defined(_QHDB_EXPORT)
		#define _QHDBExport __declspec(dllexport)
	#elif defined(_QHDB_IMPORT)
		#define _QHDBExport __declspec(dllimport)
	#else
		#define _SQLiteWrapperExport
	#endif
#else
	#define _QHDBExport
#endif

namespace QHDB
{
	#if defined(_MSC_VER) || defined(__BORLANDC__)
		typedef __int64 int64;
		typedef unsigned __int64 uint64;
	#else
		typedef long long int int64;
		typedef unsigned long long int uint64;
	#endif

		typedef enum {
			BASE_INFO = 0, //base信息
			PROFIT
		}UPDATE_TYPE;

		typedef enum {
			DIR_BUY = 1, //买多
			DIR_NULL = 0,  //未操作
			DIR_SELL = -1 //卖空
		}OPEN_DIR_TYPE;

		typedef struct  {
			int base_num; //策略编号
			string base_bianma; //品种代码  eg: MA105
			int base_multiple; //品种杠杆位数
			int base_price; //基准价
			int base_step_value; //间隔步长 eg: 10
			int base_steps_limit; //限制的步数，可用资金/保证金
			int base_profit_limit; //止盈金额
			int base_loss_cut;//止损金额
			int base_final_profit;//本策略最终收益
			string base_start_time;//本策略开始时间
			string base_end_time;//本策略结束时间
		}DB_BASE;

		typedef struct  {
			int base_num;
			int open_price;
			int open_dir;
			string open_time;
			string close_time;
		}DB_CHICANG;
	
		class QHDataBaseLib;
};

class _SQLiteWrapperExport QHDataBase {
public:
	QHDataBase();//用默认库
	QHDataBase(char* dataPath);//自定义库路径
	QHDataBase(char* dataPath, char* key);//自定义库路径和密码

	~QHDataBase();

	//返回false表示数据库无此用户

	//base
	bool insertBaseData(QHDB::DB_BASE base_data);
	bool getBaseData(QHDB::DB_BASE *base_data);//获取单个信息
	bool getBaseData(std::vector<QHDB::DB_BASE> &base_data);//获取所有信息
	bool updateBaseData(QHDB::DB_BASE base_data);
	bool deleteBaseData(int base_num);

	//chicang
	bool insertChicangData(QHDB::DB_CHICANG chicang_data);
	bool getChicangData(int base_num, std::vector<QHDB::DB_CHICANG> &chicang_data);
	bool deleteChicangData(int base_num);

	//AAC内部超级管理员修改数据库密码专用
	bool setPassWord(std::string oldKey, std::string newKey, int mode); //修改密码的软件专用

private:
	QHDB::QHDataBaseLib *mark;
};

#endif 
