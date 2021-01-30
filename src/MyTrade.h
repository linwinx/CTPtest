#pragma once
using namespace std;
#include <vector>
#include "QHDataBase.h"

typedef struct  {
	int step_value;
	int take_status;
}LOGIC_STEP_VALUE;

class MyTrade
{
public:
	MyTrade();
	~MyTrade();

	//database data
	QHDB::DB_BASE m_base_strategy;
	vector<QHDB::DB_CHICANG> m_chicang_data;

	//dynamic data
	vector<LOGIC_STEP_VALUE> m_logic_step_value;
	vector<int> m_db_chicang_value;

	//ÊÇ·ñË«Ïò¿ª²Ö
	bool m_isBothWay;

	bool CalTradeSteps(vector<LOGIC_STEP_VALUE> &steps, int base_price, int base_step = 10, int base_steps_limit = 0);
	bool IsHasTake(int cur_price, vector<int> db_step_value);
	void InitTrade();
	void UpdateTakeStatus(vector<QHDB::DB_CHICANG> chicang_steps);
	int CalProfit(int cur_price, int base_price, int base_multiple, vector<LOGIC_STEP_VALUE> steps_data);

	void test();
};

