#include "stm32f10x.h"
#include "MyRTC.h"
#include <time.h>

uint16_t MyRTC_Time[] = {2023, 1, 1, 23, 59, 55};

void MyRTC_Init(void)
{
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_PWR | RCC_APB1Periph_BKP, ENABLE);
    PWR_BackupAccessCmd(ENABLE);

    // 读取标志位, 判断是否第一次配置
    if (BKP_ReadBackupRegister(BKP_DR1) != 0xA5A5)
    {
        RCC_LSEConfig(RCC_LSE_ON);
        while (RCC_GetFlagStatus(RCC_FLAG_LSERDY) != SET)
            ;
        RCC_RTCCLKConfig(RCC_RTCCLKSource_LSE);
        RCC_RTCCLKCmd(ENABLE);

        RTC_WaitForSynchro(); // 等待时间同步
        RTC_WaitForLastTask();

        RTC_SetPrescaler(32768 - 1); // 1s, 库函数自带进入配置模式和退出配置模式
        RTC_WaitForLastTask();

        MyRTC_SetTime();

        BKP_WriteBackupRegister(BKP_DR1, 0xA5A5); // 设置标志位
    }
    else
    {
        RTC_WaitForSynchro(); // 等待时间同步
        RTC_WaitForLastTask();
    }
}

void MyRTC_SetTime(void)
{
    time_t time_cnt = 0;
    struct tm time_date = {.tm_year = MyRTC_Time[0] - 1900,
                           .tm_mon = MyRTC_Time[1] - 1,
                           .tm_mday = MyRTC_Time[2],
                           .tm_hour = MyRTC_Time[3],
                           .tm_min = MyRTC_Time[4],
                           .tm_sec = MyRTC_Time[5]};

    time_cnt = mktime(&time_date) - 8 * 3600;
    RTC_SetCounter(time_cnt);
    RTC_WaitForLastTask();
}

void MyRTC_ReadTime(void)
{
    time_t time_cnt = 0;
    struct tm time_date;

    time_cnt = RTC_GetCounter() + 8 * 3600;
    time_date = *localtime(&time_cnt);

    MyRTC_Time[0] = time_date.tm_year + 1900;
    MyRTC_Time[1] = time_date.tm_mon + 1;
    MyRTC_Time[2] = time_date.tm_mday;
    MyRTC_Time[3] = time_date.tm_hour;
    MyRTC_Time[4] = time_date.tm_min;
    MyRTC_Time[5] = time_date.tm_sec;
}