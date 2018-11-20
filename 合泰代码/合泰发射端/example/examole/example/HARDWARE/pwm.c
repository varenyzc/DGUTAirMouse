#include "pwm.h"

void PWM_Init(u16 arr,u16 psc)
{
    TM_TimeBaseInitTypeDef TimeBaseIniture;   //结构体  
    TM_OutputInitTypeDef   OutIniture;
  	
	CKCU_PeripClockConfig_TypeDef CKCUClock = {{0}};  
    CKCUClock.Bit.PB         = 1;       //GPIOA时钟打开  
    CKCUClock.Bit.AFIO       = 1;       //复用时钟  
    CKCUClock.Bit.GPTM0      = 1;  
    CKCU_PeripClockConfig(CKCUClock, ENABLE);      //时钟使能

	AFIO_GPxConfig(GPIO_PB,AFIO_PIN_5|AFIO_PIN_6|AFIO_PIN_7|AFIO_PIN_8|AFIO_PIN_9,AFIO_MODE_4);
	//定时器时基以及计数方式初始化  
    TimeBaseIniture.CounterMode=TM_CNT_MODE_UP;            //边沿对齐向上模式  
    TimeBaseIniture.CounterReload=arr;                       //计数重装载计数器  
    TimeBaseIniture.Prescaler=psc;                           //预分频系数  
    TimeBaseIniture.PSCReloadTime=TM_PSC_RLD_IMMEDIATE;    //立即重装载  
    TM_TimeBaseInit(HT_GPTM0,&TimeBaseIniture);  //GPTM0
/*-----------------------电机3号：Motor_3：PA4 . PA5  -------------------------*/		
//  GPTM0_CH0通道输出 PA4  
    OutIniture.Channel=TM_CH_0;  
    OutIniture.Control=TM_CHCTL_ENABLE;         //GPTM通道使能  
    OutIniture.OutputMode=TM_OM_PWM1;          //GPTM 通道 PWM1输出模式  PWM2模式翻转  
    OutIniture.Polarity=TM_CHP_NONINVERTED;    //GPTM 通道极性是高电平或上升沿          
    OutIniture.Compare=100;                      // 这个是配置占空比的  
    TM_OutputModeConfig(HT_GPTM0,TM_CH_0,TM_OM_PWM1);  
    TM_OutputInit(HT_GPTM0,&OutIniture); 
	
	//  GPTM0_CH1通道输出 PA5  
    OutIniture.Channel=TM_CH_1;   
    TM_OutputModeConfig(HT_GPTM0,TM_CH_1,TM_OM_PWM1);  
    TM_OutputInit(HT_GPTM0,&OutIniture);  

/*----------------------电机4号：Motor_4：PA6 . PA7  -------------------------*/		
//  GPTM0_CH2通道输出 PA6  
    OutIniture.Channel=TM_CH_2;  
    TM_OutputModeConfig(HT_GPTM0,TM_CH_2,TM_OM_PWM1);  
    TM_OutputInit(HT_GPTM0,&OutIniture);  
  
//  GPTM0_CH3通道输出 PA7  
    OutIniture.Channel=TM_CH_3;   
    TM_OutputModeConfig(HT_GPTM0,TM_CH_3,TM_OM_PWM1);  
    TM_OutputInit(HT_GPTM0,&OutIniture);  

//    GPTM_IntConfig(HT_GPTM0, GPTM_INT_CH0CC|GPTM_INT_CH1CC|GPTM_INT_CH2CC|GPTM_INT_CH3CC, ENABLE);  //中断  
      
			
    TM_Cmd(HT_GPTM0,ENABLE);  //HT_GPTM0使能
}

void TM0_IRQHandler(void)
{
	FlagStatus Status=SET;
	if(TM_GetFlagStatus(HT_GPTM0,TM_FLAG_CH0CC|TM_FLAG_CH1CC|TM_FLAG_CH2CC|TM_FLAG_CH3CC)!=RESET)
	{
		TM_ClearFlag(HT_GPTM0,TM_FLAG_CH0CC|TM_FLAG_CH1CC|TM_FLAG_CH2CC|TM_FLAG_CH3CC);
		Status=~Status;
		GPIO_WriteOutBits(HT_GPIOB,GPIO_PIN_5|GPIO_PIN_6|GPIO_PIN_7|GPIO_PIN_8|GPIO_PIN_9, Status);
	}
		
}