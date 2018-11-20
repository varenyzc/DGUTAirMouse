#include "led.h"
#include "delay.h"
#include "key.h"
#include "sys.h"
#include "usart.h"	 
#include "string.h"
#include "usb_lib.h"
#include "hw_config.h"
#include "usb_pwr.h"
#include "I2C.h"
#include "mpu6050.h"
#include "24l01.h"

//ALIENTEK战舰STM32开发板实验49
//触控USB鼠标 实验  
//技术支持：www.openedv.com
//广州市星翼电子科技有限公司  		 	

////计算x1,x2的绝对值
u32 usb_abs(u32 x1,u32 x2)
{
	if(x1>x2)return x1-x2;
	else return x2-x1;
}


 int main(void)
 {	
	
		u8 tmp_buf[5]={0};	 //发射寄存器
		delay_init();	    	 //延时函数初始化
		delay_ms(10);		
		NVIC_Configuration(); 	 //设置NVIC中断分组2:2位抢占优先级，2位响应优先级
		delay_ms(10);
//		uart_init(9600);	 	//串口初始化为9600
		NRF24L01_Init(); 
		delay_ms(10);
	 while(NRF24L01_Check())	//
		{
//				printf("%d",NRF24L01_Check());
//				printf("未检测到24l01\r\n");
					delay_ms(10);
		}
		NRF24L01_RX_Mode();
		
		//USB配置
		USB_Interrupts_Config();  	
		Set_USBClock();
		USB_Init();
 	while(1)
	{	 	
			if(NRF24L01_RxPacket(tmp_buf)==0)
			{
				delay_ms(10);	
				Joystick_Send(tmp_buf[0],tmp_buf[1],tmp_buf[2],tmp_buf[3],tmp_buf[4]);							
			}
			delay_ms(10);

	}
}
	
