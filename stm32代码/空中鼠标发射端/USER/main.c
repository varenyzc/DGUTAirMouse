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


 
//����x1,x2�ľ���ֵ
u32 usb_abs(u32 x1,u32 x2)
{
	if(x1>x2)return x1-x2;
	else return x2-x1;
}
//����USB ����/����
//enable:0,�Ͽ�
//       1,��������	   
void usb_port_set(u8 enable)
{  	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);	
	if(enable)_SetCNTR(_GetCNTR()&(~(1<<1)));//�˳��ϵ�ģʽ
	else
	{	  
		_SetCNTR(_GetCNTR()|(1<<1));  // �ϵ�ģʽ
		GPIOA->CRH&=0XFFF00FFF;
		GPIOA->CRH|=0X00033000;
		//PAout(12)=0;    		  
	}
}  	

 int main(void)
 {	

		short temp[3];

		u8 tmp_buf[5];	 //����Ĵ���
		u8 key;
		u8 i=0;

		delay_init();	    	 //��ʱ������ʼ��	  
		NVIC_Configuration(); 	 //����NVIC�жϷ���2:2λ��ռ���ȼ���2λ��Ӧ���ȼ�
		uart_init(9600);	 	//���ڳ�ʼ��Ϊ9600

		KEY_Init();	 			 //������ʼ��
		I2C_Init();
		delay_ms(40);
		MPU6050_Init();
		delay_ms(40);
		NRF24L01_Init(); 
		while(NRF24L01_Check())	//
		{
//				printf("%d",NRF24L01_Check());
//				printf("δ��⵽24l01\r\n");
				delay_ms(200);
		}
//		printf("��⵽24l01\r\n");
		NRF24L01_TX_Mode();
//		printf("����24l01Ϊ����ģʽ\r\n");
         
 	while(1)
	{
			for(i = 0 ;i<6 ;i++)
			{
				tmp_buf[i] = 0x00;
			}	
			MPU6050ReadGyro(temp);
			key=KEY_Scan(1);//֧������
			if(key==KEY_LEFT)tmp_buf[0]=0X01;			//������    
			else if(key==KEY_RIGHT)tmp_buf[0]=0X02;		//����Ҽ�
			else if(key==KEY_UP)tmp_buf[3]=0x01; //��������
			else if(key==KEY_DOWN)tmp_buf[3]=0xff; //��������
			else if(key==KEY_CENTER)	tmp_buf[4]=0x46;	//
			tmp_buf[1]=(u8)(-temp[2]/15);	
			tmp_buf[2]=(u8)((-temp[0]/15))-7;
			NRF24L01_TxPacket(tmp_buf);
			delay_ms(20);

	}	   										    			    
}


