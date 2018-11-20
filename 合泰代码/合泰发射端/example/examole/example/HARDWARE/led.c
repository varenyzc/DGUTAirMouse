#include<led.h>

void LED_Init()
{
	CKCU_PeripClockConfig_TypeDef CKCUClock = {{0}};
	CKCUClock.Bit.PB = 1;
	CKCUClock.Bit.AFIO = 1;
	CKCU_PeripClockConfig(CKCUClock, ENABLE);
	AFIO_GPxConfig(GPIO_PB,AFIO_PIN_5|AFIO_PIN_6|AFIO_PIN_7|AFIO_PIN_8|AFIO_PIN_9,AFIO_MODE_DEFAULT);
	GPIO_DirectionConfig(HT_GPIOB, GPIO_PIN_5|GPIO_PIN_6|GPIO_PIN_7|GPIO_PIN_8|GPIO_PIN_9, GPIO_DIR_OUT);      																						   
  
    GPIO_WriteOutBits(HT_GPIOB,GPIO_PIN_5|GPIO_PIN_6|GPIO_PIN_7|GPIO_PIN_8|GPIO_PIN_9,SET);
}