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

//ALIENTEKս��STM32������ʵ��49
//����USB��� ʵ��  
//����֧�֣�www.openedv.com
//������������ӿƼ����޹�˾  		 	

////����x1,x2�ľ���ֵ
u32 usb_abs(u32 x1,u32 x2)
{
	if(x1>x2)return x1-x2;
	else return x2-x1;
}


 int main(void)
 {	
	
		u8 tmp_buf[5]={0};	 //����Ĵ���
		delay_init();	    	 //��ʱ������ʼ��
		delay_ms(10);		
		NVIC_Configuration(); 	 //����NVIC�жϷ���2:2λ��ռ���ȼ���2λ��Ӧ���ȼ�
		delay_ms(10);
//		uart_init(9600);	 	//���ڳ�ʼ��Ϊ9600
		NRF24L01_Init(); 
		delay_ms(10);
	 while(NRF24L01_Check())	//
		{
//				printf("%d",NRF24L01_Check());
//				printf("δ��⵽24l01\r\n");
					delay_ms(10);
		}
		NRF24L01_RX_Mode();
		
		//USB����
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
	
