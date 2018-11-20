#ifndef __LED_H
#define __LED_H

#include "ht32.h"
#include "ht32_board.h"

#define LEFTon GPIO_WriteOutBits(HT_GPIOB,GPIO_PIN_5, SET)
#define LEFToff GPIO_WriteOutBits(HT_GPIOB,GPIO_PIN_5, RESET)
#define RIGHTon GPIO_WriteOutBits(HT_GPIOB,GPIO_PIN_6, SET)
#define RIGHToff GPIO_WriteOutBits(HT_GPIOB,GPIO_PIN_6, RESET)
#define UPon GPIO_WriteOutBits(HT_GPIOB,GPIO_PIN_8, SET)
#define UPoff GPIO_WriteOutBits(HT_GPIOB,GPIO_PIN_8, RESET)
#define DOWNon GPIO_WriteOutBits(HT_GPIOB,GPIO_PIN_9, SET)
#define DOWNoff GPIO_WriteOutBits(HT_GPIOB,GPIO_PIN_9, RESET)
void LED_Init();

#endif
