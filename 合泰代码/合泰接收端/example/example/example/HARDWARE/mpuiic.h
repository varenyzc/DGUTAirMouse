#ifndef __MPUIIC__H
#define __MPUIIC__H
#include "ht32.h"
#include "ht32_board.h"



////IO方向设置
#define MPU_SDA_IN()    GPIO_DirectionConfig(HT_GPIOC, GPIO_PIN_11, GPIO_DIR_IN); GPIO_InputConfig(HT_GPIOC, GPIO_PIN_11,ENABLE)
#define MPU_SDA_OUT()   GPIO_DirectionConfig(HT_GPIOC, GPIO_PIN_11, GPIO_DIR_OUT)          

//IO操作函数	 
#define MPU_IIC_SCL_1      GPIO_WriteOutBits(HT_GPIOC, GPIO_PIN_12, SET)		//SCL
#define MPU_IIC_SDA_1      GPIO_WriteOutBits(HT_GPIOC, GPIO_PIN_11, SET)	    //SDA
#define MPU_IIC_SCL_0      GPIO_WriteOutBits(HT_GPIOC, GPIO_PIN_12, RESET)		//SCL
#define MPU_IIC_SDA_0      GPIO_WriteOutBits(HT_GPIOC, GPIO_PIN_11, RESET)	    //SDA	 

#define MPU_READ_SDA     GPIO_ReadInBit(HT_GPIOC, GPIO_PIN_11)	//输入SDA 

//IIC所有操作函数
void MPU_IIC_Delay(void);				//MPU IIC延时函数
void MPU_IIC_Init(void);                //初始化IIC的IO口				 
void MPU_IIC_Start(void);				//发送IIC开始信号
void MPU_IIC_Stop(void);	  			//发送IIC停止信号
void MPU_IIC_Send_Byte(u8 txd);			//IIC发送一个字节
u8 MPU_IIC_Read_Byte(unsigned char ack);//IIC读取一个字节
u8 MPU_IIC_Wait_Ack(void); 				//IIC等待ACK信号
void MPU_IIC_Ack(void);					//IIC发送ACK信号
void MPU_IIC_NAck(void);				//IIC不发送ACK信号

void IMPU_IC_Write_One_Byte(u8 daddr,u8 addr,u8 data);
u8 MPU_IIC_Read_One_Byte(u8 daddr,u8 addr);	  
#endif
















