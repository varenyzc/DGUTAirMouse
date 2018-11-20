#include "spi.h"

void SPI0_Init()
{
	SPI_InitTypeDef  SPI_InitStructure;
	
                                                          
	CKCU_PeripClockConfig_TypeDef CKCUClock = {{0}};

	CKCUClock.Bit.SPI0           = 1;
	CKCUClock.Bit.PB             = 1;
	CKCUClock.Bit.AFIO           = 1;
	CKCU_PeripClockConfig(CKCUClock, ENABLE);

	
	/*  Configure SPI SEL pin                                                                                 */
  GPIO_SetOutBits(GPIO_PORT[FLASH_SPI_SEL_GPIO_ID], FLASH_SPI_SEL_GPIO_PIN);
  GPIO_DirectionConfig(GPIO_PORT[FLASH_SPI_SEL_GPIO_ID], FLASH_SPI_SEL_GPIO_PIN, GPIO_DIR_OUT);

	/*  Configure SPI SCK pin, SPI MISO pin, SPI MOSI pin                                                     */
	AFIO_GPxConfig(GPIO_PA, GPIO_PIN_4, FLASH_SPI_SCK_AFIO_MODE);
	AFIO_GPxConfig(GPIO_PA, GPIO_PIN_5, FLASH_SPI_MOSI_AFIO_MODE);
	AFIO_GPxConfig(GPIO_PA, GPIO_PIN_6, FLASH_SPI_MISO_AFIO_MODE);

	SPI_InitStructure.SPI_Mode = SPI_MASTER;
	SPI_InitStructure.SPI_FIFO = SPI_FIFO_DISABLE;
	SPI_InitStructure.SPI_DataLength = SPI_DATALENGTH_8;
	SPI_InitStructure.SPI_SELMode = SPI_SEL_SOFTWARE;
	SPI_InitStructure.SPI_SELPolarity = SPI_SELPOLARITY_LOW;
	SPI_InitStructure.SPI_FirstBit = SPI_FIRSTBIT_MSB;
	SPI_InitStructure.SPI_CPOL = SPI_CPOL_LOW;
	SPI_InitStructure.SPI_CPHA = SPI_CPHA_FIRST;
	SPI_InitStructure.SPI_RxFIFOTriggerLevel = 0;
	SPI_InitStructure.SPI_TxFIFOTriggerLevel = 0;
	SPI_InitStructure.SPI_ClockPrescaler = 16;
	SPI_Init(HT_SPI0, &SPI_InitStructure);

	SPI_SELOutputCmd(HT_SPI0, ENABLE);

	SPI_Cmd(HT_SPI0, ENABLE);
	
	
	SPI0_ReadWriteByte(0xff);//启动传输	
}


void SPI0_SetSpeed(u8 SPI_ClockPrescaler)
{
	 Assert_Param(IS_SPI_CLOCK_PRESCALER(SPI_InitStruct->SPI_ClockPrescaler));
	 HT_SPI0->CPR = 36/SPI_ClockPrescaler;
	 SPI_Cmd(HT_SPI0,ENABLE);
}
//SPIx 读写一个字节
//TxData:要写入的字节
//返回值:读取到的字节
u8 SPI0_ReadWriteByte(u8 TxData)
{		
	u8 retry=0;				 	
	while(SPI_GetFlagStatus(HT_SPI0, SPI_FLAG_TXE) == RESET)	//检查指定的SPI标志位设置与否:发送缓存空标志位
	{
		retry++;
		if(retry>200)return 0;
	}
	SPI_SendData(HT_SPI0,TxData);
	retry=0;
	while(SPI_GetFlagStatus(HT_SPI0, SPI_FLAG_RXBNE) == RESET)	//检查指定的SPI标志位设置与否:接受缓存非空标志位
	{
		retry++;
		if(retry>200)return 0;
	}
	return SPI_ReceiveData(HT_SPI0);
}
