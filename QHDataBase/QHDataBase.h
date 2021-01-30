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
			BASE_INFO = 0, //base��Ϣ
			PROFIT
		}UPDATE_TYPE;

		typedef enum {
			DIR_BUY = 1, //���
			DIR_NULL = 0,  //δ����
			DIR_SELL = -1 //����
		}OPEN_DIR_TYPE;

		typedef struct  {
			int base_num; //���Ա��
			string base_bianma; //Ʒ�ִ���  eg: MA105
			int base_multiple; //Ʒ�ָܸ�λ��
			int base_price; //��׼��
			int base_step_value; //������� eg: 10
			int base_steps_limit; //���ƵĲ����������ʽ�/��֤��
			int base_profit_limit; //ֹӯ���
			int base_loss_cut;//ֹ����
			int base_final_profit;//��������������
			string base_start_time;//�����Կ�ʼʱ��
			string base_end_time;//�����Խ���ʱ��
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
	QHDataBase();//��Ĭ�Ͽ�
	QHDataBase(char* dataPath);//�Զ����·��
	QHDataBase(char* dataPath, char* key);//�Զ����·��������

	~QHDataBase();

	//����false��ʾ���ݿ��޴��û�

	//base
	bool insertBaseData(QHDB::DB_BASE base_data);
	bool getBaseData(QHDB::DB_BASE *base_data);//��ȡ������Ϣ
	bool getBaseData(std::vector<QHDB::DB_BASE> &base_data);//��ȡ������Ϣ
	bool updateBaseData(QHDB::DB_BASE base_data);
	bool deleteBaseData(int base_num);

	//chicang
	bool insertChicangData(QHDB::DB_CHICANG chicang_data);
	bool getChicangData(int base_num, std::vector<QHDB::DB_CHICANG> &chicang_data);
	bool deleteChicangData(int base_num);

	//AAC�ڲ���������Ա�޸����ݿ�����ר��
	bool setPassWord(std::string oldKey, std::string newKey, int mode); //�޸���������ר��

private:
	QHDB::QHDataBaseLib *mark;
};

#endif 
