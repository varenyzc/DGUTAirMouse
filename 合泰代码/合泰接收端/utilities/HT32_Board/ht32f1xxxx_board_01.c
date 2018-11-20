#include "ht32_board.h"

typedef struct
{
  u8 ID;
  u16 Pin;
  AFIO_MODE_Enum Mode;
} HT32_Board_GPIO_TypeDef;

typedef struct
{
  HT_USART_TypeDef* USARTx;
  HT32_Board_GPIO_TypeDef Tx_IO;
  HT32_Board_GPIO_TypeDef Rx_IO;
} HT32_Board_COM_TypeDef;

HT_GPIO_TypeDef* const GPIO_PORT[GPIO_PORT_NUM] = {
	HT_GPIOA,
	HT_GPIOB,
	HT_GPIOC,
	HT_GPIOD,
	#if (LIBCFG_GPIOE)
	HT_GPIOE
	#endif
};

const HT32_Board_COM_TypeDef gCOMInfo[COM_NUM] =
{
	{
		COM1_PORT,
		{ COM1_TX_GPIO_ID, COM1_TX_AFIO_PIN, COM1_TX_AFIO_MODE },
		{ COM1_RX_GPIO_ID, COM1_RX_AFIO_PIN, COM1_RX_AFIO_MODE },
	},
	#if defined(COM2_PORT)
	{
		COM2_PORT,
		{ COM2_TX_GPIO_ID, COM2_TX_AFIO_PIN, COM2_TX_AFIO_MODE },
		{ COM2_RX_GPIO_ID, COM2_RX_AFIO_PIN, COM2_RX_AFIO_MODE },
	},
	#endif
};


/*********************************************************************************************************//**
 * @brief Configures COM port.
 * @param  COMn: Specifies the COM port to be configured.
 *   This parameter can be one of following parameters:
 *     @arg COM1
 *     @arg COM2
 * @param USART_InitStructure: Pointer to a USART_InitTypeDef structure that contains the configuration
 *        information for the specified USART peripheral.
 * @return None
 ************************************************************************************************************/
void HT32F_DVB_COMInit(COM_TypeDef COMn, USART_InitTypeDef* USART_InitStructure)
{
  const HT32_Board_COM_TypeDef *COMInfo = &gCOMInfo[COMn];
  CKCU_PeripClockConfig_TypeDef CKCUClock = {{0}};

  /* Enable the AFIO Clock                                                                                  */
  /* Enable USART clock                                                                                     */
  #if defined(COM2_PORT)
  (COMn == COM1) ? (COM1_CLK(CKCUClock) = 1) : (COM2_CLK(CKCUClock) = 1);
  #else
  COM1_CLK(CKCUClock) = 1;
  #endif
  CKCUClock.Bit.AFIO       = 1;
  CKCU_PeripClockConfig(CKCUClock, ENABLE);

  /* Configure USART Tx/Rx as alternate function                                                            */
  HT32F_DVB_GPxConfig(COMInfo->Tx_IO.ID, COMInfo->Tx_IO.Pin, COMInfo->Tx_IO.Mode);
  HT32F_DVB_GPxConfig(COMInfo->Rx_IO.ID, COMInfo->Rx_IO.Pin, COMInfo->Rx_IO.Mode);

  /* USART configuration                                                                                    */
  USART_Init(COMInfo->USARTx, USART_InitStructure);

  /* USART Tx enable                                                                                        */
  USART_TxCmd(COMInfo->USARTx, ENABLE);
  /* USART Rx enable                                                                                        */
  USART_RxCmd(COMInfo->USARTx, ENABLE);

  #if (RETARGET_INT_MODE == 1)
  USART_TXTLConfig(COMInfo->USARTx, USART_TXTL_00);
  
  NVIC_EnableIRQ(RETARGET_UART_IRQn);
  #endif
}


/*********************************************************************************************************//**
 * @brief Enable GPIO and AFIO Clock.
 * @param  GpioId: Specifies the GPIO ID.
 * @retval None
 ************************************************************************************************************/
static void _HT32F_DVB_ClockConfig(u32 GpioId)
{
  CKCU_PeripClockConfig_TypeDef CKCUClock = {{0}};
  u8 RegCK[GPIO_PORT_NUM] = {0};
  RegCK[GpioId] = 1;

  CKCUClock.Bit.PA         = RegCK[0];
  CKCUClock.Bit.PB         = RegCK[1];
  CKCUClock.Bit.PC         = RegCK[2];
  CKCUClock.Bit.PD         = RegCK[3];
  #if defined(LIBCFG_GPIOE)
  CKCUClock.Bit.PE         = RegCK[4];
  #endif
  CKCUClock.Bit.AFIO       = 1;
  CKCU_PeripClockConfig(CKCUClock, ENABLE);
}
