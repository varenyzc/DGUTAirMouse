#include "mpuiic.h"



//MPU IIC ��ʱ����
void MPU_IIC_Delay(void)
{
	u8 i;
	u8 time=2;
	while(time--)
	{
		i=10;
		while(i--);
	}
	
	//delay_us(2);
}
//��ʼ��IIC
void MPU_IIC_Init(void)
{					     

    CKCU_PeripClockConfig_TypeDef CKCUClock = {{0}};                                              
    CKCUClock.Bit.PC = 1;
	//CKCUClock.Bit.I2C1=1;
	//CKCUClock.Bit.AFIO=1;
    CKCU_PeripClockConfig(CKCUClock, ENABLE);      //����GPIOCʱ��                       // 	RCC->APB2ENR|=1<<4;		//��ʹ������IO PORTCʱ�� 	
    
	//AFIO_GPxConfig(GPIO_PC, AFIO_PIN_9,AFIO_MODE_7);
	//AFIO_GPxConfig(GPIO_PC, AFIO_PIN_10,AFIO_MODE_7);
    GPIO_DirectionConfig(HT_GPIOC, GPIO_PIN_11, GPIO_DIR_OUT);      //PC11/12���        //	GPIOC->CRH&=0XFFF00FFF;	//PC11/12 �������																							
    GPIO_DirectionConfig(HT_GPIOC, GPIO_PIN_12, GPIO_DIR_OUT);      //PC11/12���        //	GPIOC->CRH|=0X00033000;	   
  
    GPIO_WriteOutBits(HT_GPIOC, GPIO_PIN_11, SET);                                         //	GPIOC->ODR|=3<<11;     	//PC11,12 �����
    GPIO_WriteOutBits(HT_GPIOC, GPIO_PIN_12, SET);
                                                  
}
//����IIC��ʼ�ź�
void MPU_IIC_Start(void)
{
	MPU_SDA_OUT();     //sda�����
	MPU_IIC_SDA_1;	  	  
	MPU_IIC_SCL_1;
	MPU_IIC_Delay();
 	MPU_IIC_SDA_0;//START:when CLK is high,DATA change form high to low 
	MPU_IIC_Delay();
	MPU_IIC_SCL_0;//ǯסI2C���ߣ�׼�����ͻ�������� 
}	  
//����IICֹͣ�ź�
void MPU_IIC_Stop(void)
{
	MPU_SDA_OUT();//sda�����
	MPU_IIC_SCL_0;
	MPU_IIC_SDA_0;//STOP:when CLK is high DATA change form low to high
 	MPU_IIC_Delay();
	MPU_IIC_SCL_1;  
	MPU_IIC_SDA_1;//����I2C���߽����ź�
	MPU_IIC_Delay();							   	
}
//�ȴ�Ӧ���źŵ���
//����ֵ��1������Ӧ��ʧ��
//        0������Ӧ��ɹ�
u8 MPU_IIC_Wait_Ack(void)
{
	u8 ucErrTime=0;
	MPU_SDA_IN();      //SDA����Ϊ����  
	MPU_IIC_SDA_1;MPU_IIC_Delay();	   
	MPU_IIC_SCL_1;MPU_IIC_Delay();	 
	while(MPU_READ_SDA)
	{
		ucErrTime++;
		if(ucErrTime>250)
		{
			MPU_IIC_Stop();
			return 1;
		}
	}
	MPU_IIC_SCL_0;//ʱ�����0 	   
	return 0;  
} 
//����ACKӦ��
void MPU_IIC_Ack(void)
{
	MPU_IIC_SCL_0;
	MPU_SDA_OUT();
	MPU_IIC_SDA_0;
	MPU_IIC_Delay();
	MPU_IIC_SCL_1;
	MPU_IIC_Delay();
	MPU_IIC_SCL_0;
}
//������ACKӦ��		    
void MPU_IIC_NAck(void)
{
	MPU_IIC_SCL_0;
	MPU_SDA_OUT();
	MPU_IIC_SDA_1;
	MPU_IIC_Delay();
	MPU_IIC_SCL_1;
	MPU_IIC_Delay();
	MPU_IIC_SCL_0;
}					 				     
//IIC����һ���ֽ�
//���شӻ�����Ӧ��
//1����Ӧ��
//0����Ӧ��			  
void MPU_IIC_Send_Byte(u8 txd)
{                        
    u8 t;   
		MPU_SDA_OUT(); 	    
		MPU_IIC_SCL_0;//����ʱ�ӿ�ʼ���ݴ���
    for(t=0;t<8;t++)
    {              
				GPIO_WriteOutBits(HT_GPIOC,GPIO_PIN_11,(txd&0x80)>>7);
				txd<<=1; 	  
				MPU_IIC_SCL_1;
				MPU_IIC_Delay(); 
				MPU_IIC_SCL_0;	
				MPU_IIC_Delay();
    }	 
} 	    
//��1���ֽڣ�ack=1ʱ������ACK��ack=0������nACK   
u8 MPU_IIC_Read_Byte(unsigned char ack)
{
	unsigned char i,receive=0;
	MPU_SDA_IN();//SDA����Ϊ����
    for(i=0;i<8;i++ )
	{
        MPU_IIC_SCL_0; 
        MPU_IIC_Delay();
		MPU_IIC_SCL_1;
        receive<<=1;
        if(MPU_READ_SDA)receive++;   
		MPU_IIC_Delay(); 
    }					 
    if (!ack)
        MPU_IIC_NAck();//����nACK
    else
        MPU_IIC_Ack(); //����ACK   
    return receive;
}



























