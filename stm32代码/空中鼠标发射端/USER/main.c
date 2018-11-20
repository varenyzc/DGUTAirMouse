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
#include "spi.h"
#include "24l01.h"


 
//计算x1,x2的绝对值
u32 usb_abs(u32 x1,u32 x2)
{
	if(x1>x2)return x1-x2;
	else return x2-x1;
}
//设置USB 连接/断线
//enable:0,断开
//       1,允许连接	   
void usb_port_set(u8 enable)
{  	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);	
	if(enable)_SetCNTR(_GetCNTR()&(~(1<<1)));//退出断电模式
	else
	{	  
		_SetCNTR(_GetCNTR()|(1<<1));  // 断电模式
		GPIOA->CRH&=0XFFF00FFF;
		GPIOA->CRH|=0X00033000;
		//PAout(12)=0;    		  
	}
}  	

 int main(void)
 {	

		short temp[3];

		u8 tmp_buf[5];	 //发射寄存器
		u8 key;
		u8 i=0;

		delay_init();	    	 //延时函数初始化	  
		NVIC_Configuration(); 	 //设置NVIC中断分组2:2位抢占优先级，2位响应优先级
		uart_init(9600);	 	//串口初始化为9600

		KEY_Init();	 			 //按键初始化
		I2C_Init();
		delay_ms(40);
		MPU6050_Init();
		delay_ms(40);
		NRF24L01_Init(); 
		while(NRF24L01_Check())	//
		{
//				printf("%d",NRF24L01_Check());
//				printf("未检测到24l01\r\n");
				delay_ms(200);
		}
//		printf("检测到24l01\r\n");
		NRF24L01_TX_Mode();
//		printf("设置24l01为发射模式\r\n");
         
 	while(1)
	{
			for(i = 0 ;i<6 ;i++)
			{
				tmp_buf[i] = 0x00;
			}	
			MPU6050ReadGyro(temp);
			key=KEY_Scan(1);//支持连按
			if(key==KEY_LEFT)tmp_buf[0]=0X01;			//鼠标左键    
			else if(key==KEY_RIGHT)tmp_buf[0]=0X02;		//鼠标右键
			else if(key==KEY_UP)tmp_buf[3]=0x01; //滚轮向上
			else if(key==KEY_DOWN)tmp_buf[3]=0xff; //滚轮向下
			else if(key==KEY_CENTER)	tmp_buf[4]=0x46;	//
			tmp_buf[1]=(u8)(-temp[2]/15);	
			tmp_buf[2]=(u8)((-temp[0]/15))-7;
			NRF24L01_TxPacket(tmp_buf);
			delay_ms(20);

	}	   										    			    
}


