#include "ht32.h"
#include "ht32_board.h"
#include "ht32_board_config.h"
#include "nrf24l01.h"
#include "mpu6050.h"
#include "usart0.h"
#include "key.h"
#include "led.h"
#include "delay.h"
#include "math.h"


int main(void)
{
	short temp[3];

	u8 tmp_buf[5];	 //发射寄存器
		u8 key=0;
		u32 i=0;
	u8 state;
	KEY_Init();
	LED_Init();
	usart0_Init(115200);
	delay_init();
	while(MPU_Init() != 0)

	printf("mpu成功\r\n");
	NRF24L01_Init();
	while(NRF24L01_Check())	//
	{
	//				printf("%d",NRF24L01_Check());
		printf("未检测到24l01\r\n");
						delay_ms(200);
	}
	printf("nrf成功\n");
	NRF24L01_TX_Mode();   
	
	
	
	
  while (1)
  {

	    for(i = 0 ;i<6 ;i++)
		{
			tmp_buf[i] = 0x00;
		}	
		MPU_Get_Gyroscope(temp);
		if(temp[2]>4000)
		{
			tmp_buf[4]=0x4f;
			tmp_buf[1]=0;
			tmp_buf[2]=0;
		}
		else if(temp[2]<-4000)
		{
			tmp_buf[4]=0x50;
			tmp_buf[1]=0;
			tmp_buf[2]=0;
		}
		else if(temp[0]>4000)
		{
			tmp_buf[4]=0x51;
			tmp_buf[1]=0;
			tmp_buf[2]=0;	
		}
		else if(temp[0]<-4000)
		{
			tmp_buf[4]=0x52;
			tmp_buf[1]=0;
			tmp_buf[2]=0;
		}
		else tmp_buf[4]=0;
		
		key=KEY_Scan(1,1);
		if(key==KEY_LEFT) tmp_buf[0]=0X01;			//鼠标左键    
		else if(key==KEY_RIGHT)tmp_buf[0]=0X02;		//鼠标右键
		else if(key==KEY_UP)tmp_buf[3]=0x01; //滚轮向上
		else if(key==KEY_DOWN)tmp_buf[3]=0xff; //滚轮向下
		else if(key==KEY_CENTER)	tmp_buf[4]=0x46;	//
		
		if(fabs(temp[2]/15)>=14)
			tmp_buf[1]=(u8)(temp[2]/15);
		else tmp_buf[1]=0;
		if(fabs(temp[0]/15-254)>=14)
			tmp_buf[2]=(u8)((temp[0]/15))-254;
		else tmp_buf[2]=0;
		NRF24L01_TxPacket(tmp_buf);
		printf("%8d%8d%8d%8d%8d\r\n",tmp_buf[1],tmp_buf[2],tmp_buf[0],tmp_buf[3],temp[2]);
		delay_ms(20);
  }
}

