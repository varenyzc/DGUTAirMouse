#ifndef __KEY_H
#define __KEY_H

#include "ht32.h"
#include "ht32_board.h"

#define LEFT 		GPIO_ReadInBit(HT_GPIOB,GPIO_PIN_0)
#define RIGHT		GPIO_ReadInBit(HT_GPIOB,GPIO_PIN_1)
#define CENTER	GPIO_ReadInBit(HT_GPIOC,GPIO_PIN_4)
#define UP 			GPIO_ReadInBit(HT_GPIOC,GPIO_PIN_5)
#define DOWN		GPIO_ReadInBit(HT_GPIOC,GPIO_PIN_6)

#define KEY_LEFT		1
#define KEY_RIGHT		2
#define KEY_UP    	3
#define KEY_DOWN  	4
#define KEY_CENTER	5

void KEY_Init(void);//IO初始化
u8 KEY_Scan(u8 mode1 , u8 mode2);  	//按键扫描函数
u8 KEY_Double();  //按键同时按下

#endif
