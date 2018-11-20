#ifndef __KEY_H
#define __KEY_H	 
#include "sys.h"
//////////////////////////////////////////////////////////////////////////////////	 
//������ֻ��ѧϰʹ�ã�δ��������ɣ��������������κ���;
//ALIENTEKս��STM32������
//������������	   
//����ԭ��@ALIENTEK
//������̳:www.openedv.com
//�޸�����:2012/9/3
//�汾��V1.0
//��Ȩ���У�����ؾ���
//Copyright(C) ������������ӿƼ����޹�˾ 2009-2019
//All rights reserved									  
//////////////////////////////////////////////////////////////////////////////////   	 

// 
//#define KEY0 PEin(4)   	//PE4
//#define KEY1 PEin(3)	//PE3 
//#define KEY2 PEin(2)	//PE2
//#define KEY3 PAin(0)	//PA0  WK_UP
 
#define KEY1  GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_3)//��ȡ���
#define KEY2  GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_4)//��ȡ�Ҽ�
#define UP GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_12)//��ȡ�ϼ�
#define DOWN GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_11)//��ȡ�¼�
#define CENTER GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_8)//��ȡ�м�




#define KEY_LEFT		1
#define KEY_RIGHT		2
#define KEY_UP    	3
#define KEY_DOWN  	4
#define KEY_CENTER	5

#define KB_Value	0xff

void KEY_Init(void);//IO��ʼ��
u8 KEY_Scan(u8);  	//����ɨ�躯��					    
#endif
