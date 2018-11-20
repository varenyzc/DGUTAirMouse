#include "pwm.h"

void PWM_Init(u16 arr,u16 psc)
{
    TM_TimeBaseInitTypeDef TimeBaseIniture;   //�ṹ��  
    TM_OutputInitTypeDef   OutIniture;
  	
	CKCU_PeripClockConfig_TypeDef CKCUClock = {{0}};  
    CKCUClock.Bit.PB         = 1;       //GPIOAʱ�Ӵ�  
    CKCUClock.Bit.AFIO       = 1;       //����ʱ��  
    CKCUClock.Bit.GPTM0      = 1;  
    CKCU_PeripClockConfig(CKCUClock, ENABLE);      //ʱ��ʹ��

	AFIO_GPxConfig(GPIO_PB,AFIO_PIN_5|AFIO_PIN_6|AFIO_PIN_7|AFIO_PIN_8|AFIO_PIN_9,AFIO_MODE_4);
	//��ʱ��ʱ���Լ�������ʽ��ʼ��  
    TimeBaseIniture.CounterMode=TM_CNT_MODE_UP;            //���ض�������ģʽ  
    TimeBaseIniture.CounterReload=arr;                       //������װ�ؼ�����  
    TimeBaseIniture.Prescaler=psc;                           //Ԥ��Ƶϵ��  
    TimeBaseIniture.PSCReloadTime=TM_PSC_RLD_IMMEDIATE;    //������װ��  
    TM_TimeBaseInit(HT_GPTM0,&TimeBaseIniture);  //GPTM0
/*-----------------------���3�ţ�Motor_3��PA4 . PA5  -------------------------*/		
//  GPTM0_CH0ͨ����� PA4  
    OutIniture.Channel=TM_CH_0;  
    OutIniture.Control=TM_CHCTL_ENABLE;         //GPTMͨ��ʹ��  
    OutIniture.OutputMode=TM_OM_PWM1;          //GPTM ͨ�� PWM1���ģʽ  PWM2ģʽ��ת  
    OutIniture.Polarity=TM_CHP_NONINVERTED;    //GPTM ͨ�������Ǹߵ�ƽ��������          
    OutIniture.Compare=100;                      // ���������ռ�ձȵ�  
    TM_OutputModeConfig(HT_GPTM0,TM_CH_0,TM_OM_PWM1);  
    TM_OutputInit(HT_GPTM0,&OutIniture); 
	
	//  GPTM0_CH1ͨ����� PA5  
    OutIniture.Channel=TM_CH_1;   
    TM_OutputModeConfig(HT_GPTM0,TM_CH_1,TM_OM_PWM1);  
    TM_OutputInit(HT_GPTM0,&OutIniture);  

/*----------------------���4�ţ�Motor_4��PA6 . PA7  -------------------------*/		
//  GPTM0_CH2ͨ����� PA6  
    OutIniture.Channel=TM_CH_2;  
    TM_OutputModeConfig(HT_GPTM0,TM_CH_2,TM_OM_PWM1);  
    TM_OutputInit(HT_GPTM0,&OutIniture);  
  
//  GPTM0_CH3ͨ����� PA7  
    OutIniture.Channel=TM_CH_3;   
    TM_OutputModeConfig(HT_GPTM0,TM_CH_3,TM_OM_PWM1);  
    TM_OutputInit(HT_GPTM0,&OutIniture);  

//    GPTM_IntConfig(HT_GPTM0, GPTM_INT_CH0CC|GPTM_INT_CH1CC|GPTM_INT_CH2CC|GPTM_INT_CH3CC, ENABLE);  //�ж�  
      
			
    TM_Cmd(HT_GPTM0,ENABLE);  //HT_GPTM0ʹ��
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