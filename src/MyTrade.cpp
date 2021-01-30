#include "MyTrade.h"

#define MAX_BASE_STEPS_LIMIT 20 //最大步数


MyTrade::MyTrade()
{
}


MyTrade::~MyTrade()
{
}


bool MyTrade::CalTradeSteps(vector<LOGIC_STEP_VALUE> &steps, int base_price, int base_step_value, int base_steps_limit)
{
	int start_price, t_price, t_base_step_value, t_base_steps_limit;
	LOGIC_STEP_VALUE t_step_value;

	t_base_step_value = base_step_value;
	if (t_base_step_value <= 0)
		return false;

	t_base_steps_limit = base_steps_limit;
	if (t_base_steps_limit == 0)
		t_base_steps_limit = MAX_BASE_STEPS_LIMIT;

	if (m_isBothWay)
	{
		if (t_base_steps_limit % 2 != 0)
			t_base_steps_limit += 1;
	}
	else
	{
		if (t_base_steps_limit % 2 == 0)
			t_base_steps_limit += 1;
	}


	start_price = base_price - t_base_steps_limit / 2 * t_base_step_value;
	for (int i = 0; i < t_base_steps_limit; i++)
	{
		t_price = start_price + i * t_base_step_value;
		if (m_isBothWay)
		{
			if (t_price == base_price)
			{
				t_step_value.step_value = t_price;
				t_step_value.take_status = QHDB::DIR_NULL;
				steps.push_back(t_step_value);
			}

			t_step_value.step_value = t_price;
			t_step_value.take_status = QHDB::DIR_NULL;
			steps.push_back(t_step_value);
		}
		else
		{
			t_step_value.step_value = t_price;
			t_step_value.take_status = QHDB::DIR_NULL;
			steps.push_back(t_step_value);
		}

		
	}
	return true;
}

bool MyTrade::IsHasTake(int cur_price, vector<int> db_chicang_value)
{
	int t_price;
	bool isTake = false;
	for (int i = 0; i < db_chicang_value.size(); i++)
	{
		if (abs(cur_price - db_chicang_value[i]) <= 2)
		{
			isTake = true;
		}
	}
	return true;
}

void MyTrade::InitTrade()
{	
	m_isBothWay = false;

	//from database
	m_base_strategy.base_num = 0;
	m_base_strategy.base_bianma = "MA105";
	m_base_strategy.base_multiple = 10;
	m_base_strategy.base_price = 4000;
	m_base_strategy.base_step_value = 10;
	m_base_strategy.base_steps_limit = 20;
	m_base_strategy.base_profit_limit = 1000;
	m_base_strategy.base_loss_cut = 500;
	m_base_strategy.base_final_profit = 0;
	//from database

	if (CalTradeSteps(m_logic_step_value, m_base_strategy.base_price, m_base_strategy.base_step_value, m_base_strategy.base_steps_limit))
	{
		for (int i = 0; i < m_logic_step_value.size(); i++)
		{
			printf("0#value = %d, status = %d\n", m_logic_step_value[i].step_value, m_logic_step_value[i].take_status);
		}
	}

	//from database
	QHDB::DB_CHICANG t_data; 
	t_data.base_num = 0;
	t_data.open_price = 4000;
	t_data.open_dir = QHDB::DIR_BUY;
	m_chicang_data.push_back(t_data);

	if (m_isBothWay)
	{
		t_data.open_price = 4000;
		t_data.open_dir = QHDB::DIR_SELL;
		m_chicang_data.push_back(t_data);
	}

	t_data.open_price = 4010;
	t_data.open_dir = QHDB::DIR_BUY;
	m_chicang_data.push_back(t_data);

	t_data.open_price = 3990;
	t_data.open_dir = QHDB::DIR_SELL;
	m_chicang_data.push_back(t_data);

	t_data.open_price = 3980;
	t_data.open_dir = QHDB::DIR_SELL;
	m_chicang_data.push_back(t_data);

	t_data.open_price = 4020;
	t_data.open_dir = QHDB::DIR_BUY;
	m_chicang_data.push_back(t_data);

	t_data.open_price = 4030;
	t_data.open_dir = QHDB::DIR_BUY;
	m_chicang_data.push_back(t_data);

	t_data.open_price = 4040;
	t_data.open_dir = QHDB::DIR_BUY;
	m_chicang_data.push_back(t_data);

	t_data.open_price = 4050;
	t_data.open_dir = QHDB::DIR_BUY;
	m_chicang_data.push_back(t_data);

	t_data.open_price = 4060;
	t_data.open_dir = QHDB::DIR_BUY;
	m_chicang_data.push_back(t_data);

	t_data.open_price = 3970;
	t_data.open_dir = QHDB::DIR_SELL;
	m_chicang_data.push_back(t_data);

	t_data.open_price = 3960;
	t_data.open_dir = QHDB::DIR_SELL;
	m_chicang_data.push_back(t_data);
	//from database

	UpdateTakeStatus(m_chicang_data);

	printf("\n");
	for (int i = 0; i < m_logic_step_value.size(); i++)
	{	
		printf("1#value = %d, status = %d\n", m_logic_step_value[i].step_value, m_logic_step_value[i].take_status);
	}

	int t_profit = CalProfit(4066, m_base_strategy.base_price, m_base_strategy.base_multiple, m_logic_step_value);
	printf("\n");
	printf("2#profit = %d\n", t_profit);

}

int MyTrade::CalProfit(int cur_price, int base_price, int base_multiple, vector<LOGIC_STEP_VALUE> steps_data)
{
	int i;
	int sum = 0, step_profit_points;
	int symbol = cur_price > base_price ? 1 : -1;
	for (i = 0; i < steps_data.size(); i++)
	{
		if (steps_data[i].take_status != QHDB::DIR_NULL)
		{
			step_profit_points = symbol * steps_data[i].take_status * abs(steps_data[i].step_value - cur_price);
			sum += step_profit_points * base_multiple;
			printf("3#sum = %d, step[%d, %d] = %d \n", sum, steps_data[i].step_value, steps_data[i].take_status, step_profit_points);
		}
	}
	return sum;
}

void MyTrade::UpdateTakeStatus(vector<QHDB::DB_CHICANG> chicang)
{
	int i, j;

	for (j = 0; j < chicang.size(); j++)
	{
		for (i = 0; i < m_logic_step_value.size(); i++)
		{
			if (abs(chicang[j].open_price - m_logic_step_value[i].step_value) <= 2)
			{
				if (m_logic_step_value[i].take_status != QHDB::DIR_NULL)
				{
					continue;
				}					
				m_logic_step_value[i].take_status = chicang[j].open_dir;

				break;
			}
		}
	}
}

void MyTrade::test()
{
	InitTrade();
}