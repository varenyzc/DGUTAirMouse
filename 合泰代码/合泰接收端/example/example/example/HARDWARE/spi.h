#ifndef __SPI_H_
#define __SPI_H_

#include "ht32.h"
#include "ht32_board.h"

void SPI0_Init(void);
u8 SPI0_ReadWriteByte(u8 TxData);
void SPIO_SetSpeed(u8 speed);
#endif

