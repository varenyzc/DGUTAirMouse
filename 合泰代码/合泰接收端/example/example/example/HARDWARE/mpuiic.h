#ifndef __MPUIIC__H
#define __MPUIIC__H
#include "ht32.h"
#include "ht32_board.h"



////IO��������
#define MPU_SDA_IN()    GPIO_DirectionConfig(HT_GPIOC, GPIO_PIN_11, GPIO_DIR_IN); GPIO_InputConfig(HT_GPIOC, GPIO_PIN_11,ENABLE)
#define MPU_SDA_OUT()   GPIO_DirectionConfig(HT_GPIOC, GPIO_PIN_11, GPIO_DIR_OUT)          

//IO��������	 
#define MPU_IIC_SCL_1      GPIO_WriteOutBits(HT_GPIOC, GPIO_PIN_12, SET)		//SCL
#define MPU_IIC_SDA_1      GPIO_WriteOutBits(HT_GPIOC, GPIO_PIN_11, SET)	    //SDA
#define MPU_IIC_SCL_0      GPIO_WriteOutBits(HT_GPIOC, GPIO_PIN_12, RESET)		//SCL
#define MPU_IIC_SDA_0      GPIO_WriteOutBits(HT_GPIOC, GPIO_PIN_11, RESET)	    //SDA	 

#define MPU_READ_SDA     GPIO_ReadInBit(HT_GPIOC, GPIO_PIN_11)	//����SDA 

//IIC���в�������
void MPU_IIC_Delay(void);				//MPU IIC��ʱ����
void MPU_IIC_Init(void);                //��ʼ��IIC��IO��				 
void MPU_IIC_Start(void);				//����IIC��ʼ�ź�
void MPU_IIC_Stop(void);	  			//����IICֹͣ�ź�
void MPU_IIC_Send_Byte(u8 txd);			//IIC����һ���ֽ�
u8 MPU_IIC_Read_Byte(unsigned char ack);//IIC��ȡһ���ֽ�
u8 MPU_IIC_Wait_Ack(void); 				//IIC�ȴ�ACK�ź�
void MPU_IIC_Ack(void);					//IIC����ACK�ź�
void MPU_IIC_NAck(void);				//IIC������ACK�ź�

void IMPU_IC_Write_One_Byte(u8 daddr,u8 addr,u8 data);
u8 MPU_IIC_Read_One_Byte(u8 daddr,u8 addr);	  
#endif
















