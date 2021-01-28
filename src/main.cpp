#include <iostream>
#include <stdio.h>
#include <string>
#include <unordered_map>
#include "CustomMdSpi.h"
#include "CustomTradeSpi.h"
#include "TickToKlineHelper.h"

using namespace std;

// ���ӿ�
#pragma comment (lib, "thostmduserapi_se.lib")
#pragma comment (lib, "thosttraderapi_se.lib")

// ---- ȫ�ֱ��� ---- //
#define SIMNOW 1

#if SIMNOW
// ��������
TThostFtdcBrokerIDType gBrokerID = "9999";                         // ģ�⾭���̴���
TThostFtdcInvestorIDType gInvesterID = "125170";                         // Ͷ�����˻���
TThostFtdcPasswordType gInvesterPassword = "zsn782013";                     // Ͷ��������
#else
TThostFtdcBrokerIDType gBrokerID = "90017";                         // �Ϻ�����
TThostFtdcInvestorIDType gInvesterID = "659562";                         // Ͷ�����˻���
TThostFtdcPasswordType gInvesterPassword = "zl782013";                     // Ͷ��������
#endif
//BrokerIDͳһΪ��9999
//��׼CTP��
//��һ�飺Trade Front��180.168.146.187:10100��Market Front��180.168.146.187:10110 �����š�
//�ڶ��飺Trade Front��180.168.146.187:10101��Market Front��180.168.146.187:10111 �����š�
//�����飺Trade Front�� 218.202.237.33:10102��Market Front��218.202.237.33:10112 ���ƶ���
//7 * 24Сʱ������
//��һ�飺Trade Front�� 180.168.146.187:10130��Market Front��180.168.146.187:10131 �����š�


// �������
CThostFtdcMdApi *g_pMdUserApi = nullptr;   
// ����ָ��
#if SIMNOW
char gMdFrontAddr[] = "tcp://180.168.146.187:10112";               // ģ������ǰ�õ�ַ
#else
char gMdFrontAddr[] = "tcp://180.168.214.244��21213";               // �Ϻ���������ǰ�õ�ַ
#endif

//rb2015 ������
//MA105, TA105 ֣������ �����д��ĸ����ݲ�����һ������
//i2105 ������

char *g_pInstrumentID[] = { "MA105"}; // �����Լ�����б�֣���ϡ����н�������ѡһ��
int instrumentNum = 1;                                             // �����Լ��������
unordered_map<string, TickToKlineHelper> g_KlineHash;              // ��ͬ��Լ��k�ߴ洢��

// ���ײ���
CThostFtdcTraderApi *g_pTradeUserApi = nullptr;                    // ����ָ��
char gTradeFrontAddr[] = "tcp://180.168.146.187:10100";            // ģ�⽻��ǰ�õ�ַ
TThostFtdcInstrumentIDType g_pTradeInstrumentID = "C2105";        // �����׵ĺ�Լ����
TThostFtdcDirectionType gTradeDirection = THOST_FTDC_D_Sell;       // ��������
TThostFtdcPriceType gLimitPrice = 22735;                           // ���׼۸�

int main()
{
	// �˺�����
	//cout << "�������˺ţ� ";
	//scanf("%s", gInvesterID);
	//cout << "���������룺 ";
	//scanf("%s", gInvesterPassword);

	// ��ʼ�������߳�
	cout << "��ʼ������..." << endl;
	g_pMdUserApi = CThostFtdcMdApi::CreateFtdcMdApi();   // ��������ʵ��
	CThostFtdcMdSpi *pMdUserSpi = new CustomMdSpi;       // ��������ص�ʵ��
	g_pMdUserApi->RegisterSpi(pMdUserSpi);               // ע���¼���
	g_pMdUserApi->RegisterFront(gMdFrontAddr);           // ��������ǰ�õ�ַ
	g_pMdUserApi->Init();                                // ��������
	

	/*
	// ��ʼ�������߳�
	cout << "��ʼ������..." << endl;
	g_pTradeUserApi = CThostFtdcTraderApi::CreateFtdcTraderApi(); // ��������ʵ��
	//CThostFtdcTraderSpi *pTradeSpi = new CustomTradeSpi;
	CustomTradeSpi *pTradeSpi = new CustomTradeSpi;               // �������׻ص�ʵ��
	g_pTradeUserApi->RegisterSpi(pTradeSpi);                      // ע���¼���
	g_pTradeUserApi->SubscribePublicTopic(THOST_TERT_RESTART);    // ���Ĺ�����
	g_pTradeUserApi->SubscribePrivateTopic(THOST_TERT_RESTART);   // ����˽����
	g_pTradeUserApi->RegisterFront(gTradeFrontAddr);              // ���ý���ǰ�õ�ַ
	g_pTradeUserApi->Init();                                      // ��������
		*/

	// �ȵ��߳��˳�
	g_pMdUserApi->Join();
	delete pMdUserSpi;
	g_pMdUserApi->Release();

	/*
	g_pTradeUserApi->Join();
	delete pTradeSpi;
	g_pTradeUserApi->Release();
	*/

	// ת������k������
	//TickToKlineHelper tickToKlineHelper;
	//tickToKlineHelper.KLineFromLocalData("market_data.csv", "K_line_data.csv");
	
	getchar();
	return 0;
}