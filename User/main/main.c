#include "sys.h"
#include "debug.h"
#include "type.h"
#include "startup_demo.h"
#include "main.h"
#include "cpm_drv.h"
#include "common.h"


/*！！！！！！！！！！！！！！！！！撃廾窃侏式哈重蛍塘！！！！！！|
哈重       | QFN32 | QFN40 | QFN48 | QFN88 |
！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！|
SPI        |   2   |   1   |   3   |   3   |
！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！|
I2C        |   1   |   1   |   1   |   3   |   
！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！|
SSI        |   0   |   1   |   0   |   1   |
！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！|
UART       |   1   |   1   |   3   |   3   |
！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！|
ISO7816    |   2   |   0   |   0   |   1   |
！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！|
USB_OTG    |   1   |   1   |   1   |   1   |
！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！|
ADC        |   0   |   1   |   2   |   3   |
！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！|
DAC        |   0   |   0   |   1   |   1   |
！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！|
PWM(鹸喘)  |   3   |   4   |   2   |   4   |
！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！|
MCC        |   0   |   0   |   0   |   0   |
！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！|
TSI(鹸喘)  |   8   |   5   |  10   |  16   |
！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！|
EPORT(鹸喘)|  10   |  18   |  19   |  20   |
！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！|
SDIO(契介) |   0   |   0   |   0   |   1   |
！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！|
C0 SUB I/O |   0   |   0   |   0   |   4   |
！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！|*/

/*！！！！！！！！！！！！！！！USB 屶隔秤趨！！！！！！！！！！！！！！|
撃廾   | USB2.0 | USB1.1 |  host  | device |
！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！|
QFN32  | 音辛參 |  辛參  | 音屶隔 |  屶隔  |
！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！|
QFN40  |  辛參  |  辛參  | 音屶隔 |  屶隔  |
！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！|
QFN48  | 音辛參 |  辛參  | 音屶隔 |  屶隔  |
！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！|
QFN88  | 音辛參 |  辛參  | 音屶隔 |  屶隔  |
！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！|*/


#include "eport_drv.h"
#include "audio.h"
#include "led.h"
#include "key.h"
#include "keypad_menu.h"
#include "uart.h"
#include "uart_fp.h"
#include "password.h"
#include "lpm.h"
#include "uart_back.h"
#include "pci_drv.h"
#include "tc_drv.h"
#include "cache_drv.h"
#include "card.h"  
#include "uart_face.h"
#include "bat.h"
#include "delay.h"
#include "rtc.h"
#include "lock_config.h"
#include "wdt_drv.h"
#include "time_cal.h"


extern void IO_Latch_Clr(void);


void Reback_Boot(void)
{
#ifdef MY_DEBUG
//距編扮蝕尼隠�妝�參契仂頭瓜迄廖
	//	IO_Latch_Clr();
		EPORT_ConfigGpio(KEY_TAMPER_PIN,GPIO_INPUT);            
		EPORT_ConfigGpio(KEY_BACK_PIN,GPIO_INPUT);  
		EPORT_PullupConfig(KEY_BACK_PIN,ENABLE);            //聞嬬貧性 
    if(EPORT_ReadGpioData(KEY_TAMPER_PIN) == Bit_RESET)           //契介防蝕��防蝕葎詰
    {
				DelayMS(20);
				if(EPORT_ReadGpioData(KEY_BACK_PIN) == Bit_RESET)      //朔医梓囚梓和 
				{
						Demo_StartupConfig(Startup_From_ROM, ENABLE);
						while(1);
				}			
    }
#else
		DelayMS(20);
#endif
}

int main()
{
		e_CPM_wakeupSource_Status rst_source=*(e_CPM_wakeupSource_Status *)CPM_WAKEUPSOURCE_REG;         //響函蚕佰坿
		Sys_Init();                                                 //狼由兜兵晒
		IO_Latch_Clr();
		Reback_Boot();
		UART_Debug_Init(SCI1,g_ips_clk,9600);                       //距編嬉咫兜兵晒
//		printf("CPM->CPM_PADWKINTCR: 0x%08x \n",CPM->CPM_PADWKINTCR);
//		printf("wakeup source: 0x%02x \n",rst_source);
//		printf("reset source: 0x%02x \n",Get_Reset_Status());
		switch(rst_source)
		{
					case WAKEUP_SOURCE_GIN3:                  //朔医堪笥蚕佰
							LedVal.ledval=LED_MASK_WAKE;
#ifndef NO_FACE_MODE       //繁然井云
									FaceIdyLock=1;       
#endif
							break;
//				case WAKEUP_SOURCE_WAKEUP:                //PIR蚕佰
//						LedVal.ledval=LED_MASK_WAKE;
//						break;
//				case WAKEUP_SOURCE_TSI:                   //乾寵梓囚蚕佰
//						LedVal.ledval=LED_MASK_WAKE;
//						break;
//				case WAKEUP_SOURCE_GIN3:                  //朔医堪笥蚕佰
//						LedVal.ledval=LED_MASK_WAKE;
//						break;
//				case WAKEUP_SOURCE_GIN4:                  //SET梓囚蚕佰
//						LedVal.ledval=LED_MASK_WAKE;
//						break;
//				case WAKEUP_SOURCE_GIN5:                  //契介梓囚蚕佰
//						LedVal.ledval=LED_MASK_WAKE;
//						break;
				case WAKEUP_SOURCE_POR:                     //貧窮鹸了�坐阻�嗤菊��掲貧窮鹸了峪疏壇槽夕炎
						LedVal.ledval=LED_MASK_WAKE;
						PowerOnCheckBatDelay=5000; 
						break;
				default:
						LedVal.ledval=LED_MASK_WAKE;        
						PowerOnCheckBatDelay=0;
						break;
		}
		printf("allright here1\n");
		Led_Init();                         //枠兜兵晒LED
		Timer_Init();                       //協扮匂兜兵晒
		SSI_FLASH_Init();                   //FLASH兜兵晒
		RtcInit();                          //RTC兜兵晒 
		LockReadSysConfig();                //紗墮狼由譜崔�� 
		Audio_Init();                       //囂咄兜兵晒 
		Uart_DriverInit();                  //堪笥駁強兜兵晒
		Uart_Init();                        //堪笥兜兵晒
		TampSetButtonInit();                //契介吉梓囚兜兵晒
		PassWordInit();                     //畜鷹兜兵晒    
		Key_Init();                         //乾寵梓囚兜兵晒
		CardIoInit();                        //触頭IO兜兵晒
		WDT_Init(0xffff);                   //心壇昂兜兵晒 
		WDT_FeedDog();                      //兜兵晒旅昂
		Key_Scan();                         //貧窮響匯肝彜蓑��契峭蚕佰窮楚侭嗤囚徒菊
		MenuNow=Menu_KeyPadNormal;          //擬秘麼暇汽 
		LPM_SetStopMode(LPM_POWERON_ID,LPM_Disable);   //貧窮决扮5S
		printf("init ok\n");
		while(1)
		{
				MenuNow();                      //塰佩荷恬暇汽  
		}
}
