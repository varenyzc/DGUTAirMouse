#include "usart0.h"

void usart0_Init(u32 bound)
{
	USART_InitTypeDef USART_InitStructure;
	
	/* Enable peripheral clock of AFIO, UART                                                                  */
	CKCU_PeripClockConfig_TypeDef CKCUClock = {{0}};
	CKCUClock.Bit.AFIO   = 1;
	CKCUClock.Bit.USART0 = 1;
	CKCU_PeripClockConfig(CKCUClock, ENABLE);

	/* Config AFIO mode as Rx and Tx function.                                                                */
	AFIO_GPxConfig(GPIO_PA, AFIO_PIN_2,AFIO_MODE_6);  //PA2 USART0_TX
	AFIO_GPxConfig(GPIO_PA, AFIO_PIN_3,AFIO_MODE_6);  //PA3 USART0_RX
	/* UART configuration ------------------------------------------------------------------------------------*/
	/* UART configured as follow:
		- BaudRate = bound baud
		- Word Length = 8 Bits
		- One Stop Bit
		- None parity bit
	*/
	USART_InitStructure.USART_BaudRate = bound;
	USART_InitStructure.USART_WordLength = USART_WORDLENGTH_8B;
	USART_InitStructure.USART_StopBits = USART_STOPBITS_1;
	USART_InitStructure.USART_Parity = USART_PARITY_NO;
	USART_InitStructure.USART_Mode = USART_MODE_NORMAL;

	USART_Init(HT_USART0, &USART_InitStructure);
	USART_TxCmd(HT_USART0, ENABLE);
	USART_RxCmd(HT_USART0, ENABLE);
}
