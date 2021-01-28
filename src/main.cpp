#include <iostream>
#include <stdio.h>
#include <string>
#include <unordered_map>
#include "CustomMdSpi.h"
#include "CustomTradeSpi.h"
#include "TickToKlineHelper.h"

using namespace std;

// 链接库
#pragma comment (lib, "thostmduserapi_se.lib")
#pragma comment (lib, "thosttraderapi_se.lib")

// ---- 全局变量 ---- //
#define SIMNOW 1

#if SIMNOW
// 公共参数
TThostFtdcBrokerIDType gBrokerID = "9999";                         // 模拟经纪商代码
TThostFtdcInvestorIDType gInvesterID = "125170";                         // 投资者账户名
TThostFtdcPasswordType gInvesterPassword = "zsn782013";                     // 投资者密码
#else
TThostFtdcBrokerIDType gBrokerID = "90017";                         // 上海中期
TThostFtdcInvestorIDType gInvesterID = "659562";                         // 投资者账户名
TThostFtdcPasswordType gInvesterPassword = "zl782013";                     // 投资者密码
#endif
//BrokerID统一为：9999
//标准CTP：
//第一组：Trade Front：180.168.146.187:10100，Market Front：180.168.146.187:10110 【电信】
//第二组：Trade Front：180.168.146.187:10101，Market Front：180.168.146.187:10111 【电信】
//第三组：Trade Front： 218.202.237.33:10102，Market Front：218.202.237.33:10112 【移动】
//7 * 24小时环境：
//第一组：Trade Front： 180.168.146.187:10130，Market Front：180.168.146.187:10131 【电信】


// 行情参数
CThostFtdcMdApi *g_pMdUserApi = nullptr;   
// 行情指针
#if SIMNOW
char gMdFrontAddr[] = "tcp://180.168.146.187:10112";               // 模拟行情前置地址
#else
char gMdFrontAddr[] = "tcp://180.168.214.244：21213";               // 上海中期行情前置地址
#endif

//rb2015 上期所
//MA105, TA105 郑商所， 必须大写字母，年份不带第一个数字
//i2105 大商所

char *g_pInstrumentID[] = { "MA105"}; // 行情合约代码列表，郑、上、大、中交易所各选一种
int instrumentNum = 1;                                             // 行情合约订阅数量
unordered_map<string, TickToKlineHelper> g_KlineHash;              // 不同合约的k线存储表

// 交易参数
CThostFtdcTraderApi *g_pTradeUserApi = nullptr;                    // 交易指针
char gTradeFrontAddr[] = "tcp://180.168.146.187:10100";            // 模拟交易前置地址
TThostFtdcInstrumentIDType g_pTradeInstrumentID = "C2105";        // 所交易的合约代码
TThostFtdcDirectionType gTradeDirection = THOST_FTDC_D_Sell;       // 买卖方向
TThostFtdcPriceType gLimitPrice = 22735;                           // 交易价格

int main()
{
	// 账号密码
	//cout << "请输入账号： ";
	//scanf("%s", gInvesterID);
	//cout << "请输入密码： ";
	//scanf("%s", gInvesterPassword);

	// 初始化行情线程
	cout << "初始化行情..." << endl;
	g_pMdUserApi = CThostFtdcMdApi::CreateFtdcMdApi();   // 创建行情实例
	CThostFtdcMdSpi *pMdUserSpi = new CustomMdSpi;       // 创建行情回调实例
	g_pMdUserApi->RegisterSpi(pMdUserSpi);               // 注册事件类
	g_pMdUserApi->RegisterFront(gMdFrontAddr);           // 设置行情前置地址
	g_pMdUserApi->Init();                                // 连接运行
	

	/*
	// 初始化交易线程
	cout << "初始化交易..." << endl;
	g_pTradeUserApi = CThostFtdcTraderApi::CreateFtdcTraderApi(); // 创建交易实例
	//CThostFtdcTraderSpi *pTradeSpi = new CustomTradeSpi;
	CustomTradeSpi *pTradeSpi = new CustomTradeSpi;               // 创建交易回调实例
	g_pTradeUserApi->RegisterSpi(pTradeSpi);                      // 注册事件类
	g_pTradeUserApi->SubscribePublicTopic(THOST_TERT_RESTART);    // 订阅公共流
	g_pTradeUserApi->SubscribePrivateTopic(THOST_TERT_RESTART);   // 订阅私有流
	g_pTradeUserApi->RegisterFront(gTradeFrontAddr);              // 设置交易前置地址
	g_pTradeUserApi->Init();                                      // 连接运行
		*/

	// 等到线程退出
	g_pMdUserApi->Join();
	delete pMdUserSpi;
	g_pMdUserApi->Release();

	/*
	g_pTradeUserApi->Join();
	delete pTradeSpi;
	g_pTradeUserApi->Release();
	*/

	// 转换本地k线数据
	//TickToKlineHelper tickToKlineHelper;
	//tickToKlineHelper.KLineFromLocalData("market_data.csv", "K_line_data.csv");
	
	getchar();
	return 0;
}