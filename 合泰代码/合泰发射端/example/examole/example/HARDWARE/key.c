#include "key.h"
#include "delay.h"
void KEY_Init(void) //IO初始化
{
	CKCU_PeripClockConfig_TypeDef CKCUClock = {{0}};
	CKCUClock.Bit.PC = 1;
	CKCUClock.Bit.PB = 1;
	CKCUClock.Bit.AFIO = 1;
	CKCU_PeripClockConfig(CKCUClock, ENABLE);
	
	AFIO_GPxConfig(GPIO_PB,AFIO_PIN_0|AFIO_PIN_1,AFIO_MODE_DEFAULT);
	AFIO_GPxConfig(GPIO_PC,AFIO_PIN_4|AFIO_PIN_5|AFIO_PIN_6,AFIO_MODE_DEFAULT);
	
	GPIO_DirectionConfig(HT_GPIOB,GPIO_PIN_0,GPIO_DIR_IN);
	GPIO_DirectionConfig(HT_GPIOB,GPIO_PIN_1,GPIO_DIR_IN);
	GPIO_DirectionConfig(HT_GPIOC,GPIO_PIN_4,GPIO_DIR_IN);
	GPIO_DirectionConfig(HT_GPIOC,GPIO_PIN_5,GPIO_DIR_IN);
	GPIO_DirectionConfig(HT_GPIOC,GPIO_PIN_6,GPIO_DIR_IN);
	
	GPIO_PullResistorConfig(HT_GPIOB,GPIO_PIN_0|GPIO_PIN_1,GPIO_PR_UP);
	GPIO_PullResistorConfig(HT_GPIOC,GPIO_PIN_4|GPIO_PIN_5|GPIO_PIN_6,GPIO_PR_UP);
	
	GPIO_InputConfig(HT_GPIOB,GPIO_PIN_0|GPIO_PIN_1,ENABLE);
	GPIO_InputConfig(HT_GPIOC,GPIO_PIN_4|GPIO_PIN_5|GPIO_PIN_6,ENABLE);
}

u8 KEY_Scan(u8 mode1 , u8 mode2)
{
	static u8 key_up1=1;//其余按键松开标志
	static u8 key_up2=1;//滚轮按键松开标志
	if(mode1)key_up1=1;
	if(mode2)key_up2=1;
	if(key_up1&&(LEFT==0||RIGHT==0||CENTER==0))
	{
		delay_ms(10);
		key_up1 = 0;
		if(LEFT == RESET)	return KEY_LEFT;
		else if(RIGHT == RESET)	return KEY_RIGHT;
		else if(CENTER == RESET)	return KEY_CENTER;
	}
	else if(key_up2&&(UP == 0||DOWN == 0))
	{
		delay_ms(100);
		key_up2 = 0;
		if(UP == RESET)	return KEY_UP;
		else if(DOWN == RESET)	return KEY_DOWN;
	}
	else if(LEFT && RIGHT && CENTER && UP && DOWN)
	{
		key_up1 = 1;
		key_up2 = 1;
	}
	return 0;//无按键按下
}








