#include "mpuiic.h"



//MPU IIC 延时函数
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
//初始化IIC
void MPU_IIC_Init(void)
{					     

    CKCU_PeripClockConfig_TypeDef CKCUClock = {{0}};                                              
    CKCUClock.Bit.PC = 1;
	//CKCUClock.Bit.I2C1=1;
	//CKCUClock.Bit.AFIO=1;
    CKCU_PeripClockConfig(CKCUClock, ENABLE);      //开启GPIOC时钟                       // 	RCC->APB2ENR|=1<<4;		//先使能外设IO PORTC时钟 	
    
	//AFIO_GPxConfig(GPIO_PC, AFIO_PIN_9,AFIO_MODE_7);
	//AFIO_GPxConfig(GPIO_PC, AFIO_PIN_10,AFIO_MODE_7);
    GPIO_DirectionConfig(HT_GPIOC, GPIO_PIN_11, GPIO_DIR_OUT);      //PC11/12输出        //	GPIOC->CRH&=0XFFF00FFF;	//PC11/12 推挽输出																							
    GPIO_DirectionConfig(HT_GPIOC, GPIO_PIN_12, GPIO_DIR_OUT);      //PC11/12输出        //	GPIOC->CRH|=0X00033000;	   
  
    GPIO_WriteOutBits(HT_GPIOC, GPIO_PIN_11, SET);                                         //	GPIOC->ODR|=3<<11;     	//PC11,12 输出高
    GPIO_WriteOutBits(HT_GPIOC, GPIO_PIN_12, SET);
                                                  
}
//产生IIC起始信号
void MPU_IIC_Start(void)
{
	MPU_SDA_OUT();     //sda线输出
	MPU_IIC_SDA_1;	  	  
	MPU_IIC_SCL_1;
	MPU_IIC_Delay();
 	MPU_IIC_SDA_0;//START:when CLK is high,DATA change form high to low 
	MPU_IIC_Delay();
	MPU_IIC_SCL_0;//钳住I2C总线，准备发送或接收数据 
}	  
//产生IIC停止信号
void MPU_IIC_Stop(void)
{
	MPU_SDA_OUT();//sda线输出
	MPU_IIC_SCL_0;
	MPU_IIC_SDA_0;//STOP:when CLK is high DATA change form low to high
 	MPU_IIC_Delay();
	MPU_IIC_SCL_1;  
	MPU_IIC_SDA_1;//发送I2C总线结束信号
	MPU_IIC_Delay();							   	
}
//等待应答信号到来
//返回值：1，接收应答失败
//        0，接收应答成功
u8 MPU_IIC_Wait_Ack(void)
{
	u8 ucErrTime=0;
	MPU_SDA_IN();      //SDA设置为输入  
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
	MPU_IIC_SCL_0;//时钟输出0 	   
	return 0;  
} 
//产生ACK应答
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
//不产生ACK应答		    
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
//IIC发送一个字节
//返回从机有无应答
//1，有应答
//0，无应答			  
void MPU_IIC_Send_Byte(u8 txd)
{                        
    u8 t;   
		MPU_SDA_OUT(); 	    
		MPU_IIC_SCL_0;//拉低时钟开始数据传输
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
//读1个字节，ack=1时，发送ACK，ack=0，发送nACK   
u8 MPU_IIC_Read_Byte(unsigned char ack)
{
	unsigned char i,receive=0;
	MPU_SDA_IN();//SDA设置为输入
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
        MPU_IIC_NAck();//发送nACK
    else
        MPU_IIC_Ack(); //发送ACK   
    return receive;
}



























