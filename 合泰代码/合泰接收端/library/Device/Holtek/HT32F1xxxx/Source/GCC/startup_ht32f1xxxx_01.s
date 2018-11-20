/*
;/*---------------------------------------------------------------------------------------------------------*/
;/* Holtek Semiconductor Inc.                                                                               */
;/*                                                                                                         */
;/* Copyright (C) Holtek Semiconductor Inc.                                                                 */
;/* All rights reserved.                                                                                    */
;/*                                                                                                         */
;/*-----------------------------------------------------------------------------------------------------------
;  File Name        : startup_ht32f1xxxx_01.s
;  Version          : $Rev:: 102          $
;  Date             : $Date:: 2017-06-01 #$
;  Description      : Startup code for CodeSourcery Sourcery G++ Lite (with CS3).
;-----------------------------------------------------------------------------------------------------------*/
*/

/*
//  Supported Device
//  ========================================
//   HT32F1653, HT32F1654
//   HT32F1655, HT32F1656
//   HT32F12365, HT32F12366
//   HT32F12345
*/

/*
//*** <<< Use Configuration Wizard in Context Menu >>> ***
*/

/*
;// <o>  HT32 Device
;//      <0=> By Project Asm Define
;//      <1=> HT32F1653/1654/1655/1656
;//      <2=> HT32F12365/12366
;//      <3=> HT32F12345
*/
    .equ    USE_HT32_CHIP_SET, 0
    .equ    _HT32FWID, 0xFFFFFFFF
    /*.equ    _HT32FWID, 0x00012366*/

    .equ    HT32F1653_54_55_56, 1
    .equ    HT32F12365_66, 2
    .equ    HT32F12345, 3

    .if (USE_HT32_CHIP_SET==0)
    .else
    .equ    USE_HT32_CHIP, USE_HT32_CHIP_SET
    .endif

/*
// <h> Stack Configuration
//   <o> Stack Size (in Bytes) <0-131072:8>
// </h>
*/

    .equ    Stack_Size, 512
    .section ".stack", "w"
    .align  3
    .globl  __cs3_stack_mem
    .globl  __cs3_stack
    .globl  __cs3_stack_size
__cs3_stack_mem:
    .if     Stack_Size
    .space  Stack_Size
    .endif
__cs3_stack:
    .size   __cs3_stack_mem,  . - __cs3_stack_mem
    .set    __cs3_stack_size, . - __cs3_stack_mem


/*
// <h> Heap Configuration
//   <o>  Heap Size (in Bytes) <0-131072:8>
// </h>
*/

    .equ    Heap_Size, 0

    .section ".heap", "w"
    .align  3
    .globl  __cs3_heap_start
    .globl  __cs3_heap_end
__cs3_heap_start:
    .if     Heap_Size
    .space  Heap_Size
    .endif
__cs3_heap_end:

/* Vector Table */

    .section ".cs3.interrupt_vector"
    .globl  __cs3_interrupt_vector_cortex_m
    .type   __cs3_interrupt_vector_cortex_m, %object
    .equ    _RESERVED, 0xFFFFFFFF

__cs3_interrupt_vector_cortex_m:
    .long   __cs3_stack                 /* Top of Stack                 */
    .long   __cs3_reset                 /* Reset Handler                */
    .long   NMI_Handler                 /* NMI Handler                  */
    .long   HardFault_Handler           /* Hard Fault Handler           */
    .long   MemManage_Handler           /* MPU Fault Handler            */
    .long   BusFault_Handler            /* Bus Fault Handler            */
    .long   UsageFault_Handler          /* Usage Fault Handler          */
    .long   _RESERVED                   /* Reserved                     */
    .long   _HT32FWID                   /* Reserved                     */
    .long   _RESERVED                   /* Reserved                     */
    .long   _RESERVED                   /* Reserved                     */
    .long   SVC_Handler                 /* SVCall Handler               */
    .long   DebugMon_Handler            /* Debug Monitor Handler        */
    .long   _RESERVED                   /* Reserved                     */
    .long   PendSV_Handler              /* PendSV Handler               */
    .long   SysTick_Handler             /* SysTick Handler              */

    /* External Interrupts */
    .long   CKRDY_IRQHandler
    .long   LVD_IRQHandler
    .long   BOD_IRQHandler
  .if ((USE_HT32_CHIP==HT32F1653_54_55_56))
    .long   WDT_IRQHandler
  .else
    .long   _RESERVED
  .endif
    .long   RTC_IRQHandler
    .long   FLASH_IRQHandler
    .long   EVWUP_IRQHandler
    .long   LPWUP_IRQHandler
    .long   EXTI0_IRQHandler
    .long   EXTI1_IRQHandler
    .long   EXTI2_IRQHandler
    .long   EXTI3_IRQHandler
    .long   EXTI4_IRQHandler
    .long   EXTI5_IRQHandler
    .long   EXTI6_IRQHandler
    .long   EXTI7_IRQHandler
    .long   EXTI8_IRQHandler
    .long   EXTI9_IRQHandler
    .long   EXTI10_IRQHandler
    .long   EXTI11_IRQHandler
    .long   EXTI12_IRQHandler
    .long   EXTI13_IRQHandler
    .long   EXTI14_IRQHandler
    .long   EXTI15_IRQHandler
    .long   COMP_IRQHandler
    .long   ADC_IRQHandler
    .long   _RESERVED
    .long   MCTM0BRK_IRQHandler
    .long   MCTM0UP_IRQHandler
    .long   MCTM0TR_IRQHandler
    .long   MCTM0CC_IRQHandler
    .long   MCTM1BRK_IRQHandler
    .long   MCTM1UP_IRQHandler
    .long   MCTM1TR_IRQHandler
    .long   MCTM1CC_IRQHandler
    .long   GPTM0_IRQHandler
    .long   GPTM1_IRQHandler
    .long   _RESERVED
    .long   _RESERVED
    .long   _RESERVED
    .long   _RESERVED
    .long   BFTM0_IRQHandler
    .long   BFTM1_IRQHandler
    .long   I2C0_IRQHandler
    .long   I2C1_IRQHandler
    .long   SPI0_IRQHandler
    .long   SPI1_IRQHandler
    .long   USART0_IRQHandler
    .long   USART1_IRQHandler
    .long   UART0_IRQHandler
    .long   UART1_IRQHandler
  .if (USE_HT32_CHIP==HT32F12345)
    .long   _RESERVED
  .else
    .long   SCI_IRQHandler
  .endif
    .long   I2S_IRQHandler
    .long   USB_IRQHandler
  .if ((USE_HT32_CHIP==HT32F1653_54_55_56))
    .long   _RESERVED
  .else
    .long   SDIO_IRQHandler
  .endif
    .long   PDMA_CH0_IRQHandler
    .long   PDMA_CH1_IRQHandler
    .long   PDMA_CH2_IRQHandler
    .long   PDMA_CH3_IRQHandler
    .long   PDMA_CH4_IRQHandler
    .long   PDMA_CH5_IRQHandler
    .long   PDMA_CH6_IRQHandler
    .long   PDMA_CH7_IRQHandler
  .if ((USE_HT32_CHIP==HT32F1653_54_55_56))
    .long   _RESERVED
    .long   _RESERVED
    .long   _RESERVED
    .long   _RESERVED
  .else
    .long   PDMA_CH8_IRQHandler
    .long   PDMA_CH9_IRQHandler
    .long   PDMA_CH10_IRQHandler
    .long   PDMA_CH11_IRQHandler
  .endif
  .if (USE_HT32_CHIP==HT32F12365_66)
    .long   CSIF_IRQHandler
  .else
    .long   _RESERVED
  .endif
    .long   EBI_IRQHandler
  .if (USE_HT32_CHIP==HT32F12365_66)
    .long   AES_IRQHandler
  .endif

    .size   __cs3_interrupt_vector_cortex_m, . - __cs3_interrupt_vector_cortex_m


    .thumb


/* Reset Handler */

    .section .cs3.reset,"x",%progbits
    .thumb_func
    .globl  __cs3_reset_cortex_m
    .type   __cs3_reset_cortex_m, %function
__cs3_reset_cortex_m:
    .fnstart
    LDR     R0, =SystemInit
    BLX     R0
    LDR     R0,=_start
    BX      R0
    .pool
    .cantunwind
    .fnend
    .size   __cs3_reset_cortex_m,.-__cs3_reset_cortex_m

    .section ".text"

/* Exception Handlers */

    .weak   NMI_Handler
    .type   NMI_Handler, %function
NMI_Handler:
    B       .
    .size   NMI_Handler, . - NMI_Handler

    .weak   HardFault_Handler
    .type   HardFault_Handler, %function
HardFault_Handler:
    B       .
    .size   HardFault_Handler, . - HardFault_Handler

    .weak   MemManage_Handler
    .type   MemManage_Handler, %function
MemManage_Handler:
    B       .
    .size   MemManage_Handler, . - MemManage_Handler

    .weak   BusFault_Handler
    .type   BusFault_Handler, %function
BusFault_Handler:
    B       .
    .size   BusFault_Handler, . - BusFault_Handler

    .weak   UsageFault_Handler
    .type   UsageFault_Handler, %function
UsageFault_Handler:
    B       .
    .size   UsageFault_Handler, . - UsageFault_Handler

    .weak   SVC_Handler
    .type   SVC_Handler, %function
SVC_Handler:
    B       .
    .size   SVC_Handler, . - SVC_Handler

    .weak   DebugMon_Handler
    .type   DebugMon_Handler, %function
DebugMon_Handler:
    B       .
    .size   DebugMon_Handler, . - DebugMon_Handler

    .weak   PendSV_Handler
    .type   PendSV_Handler, %function
PendSV_Handler:
    B       .
    .size   PendSV_Handler, . - PendSV_Handler

    .weak   SysTick_Handler
    .type   SysTick_Handler, %function
SysTick_Handler:
    B       .
    .size   SysTick_Handler, . - SysTick_Handler


/* IRQ Handlers */

    .globl  Default_Handler
    .type   Default_Handler, %function
Default_Handler:
    B       .
    .size   Default_Handler, . - Default_Handler

    .macro  IRQ handler
    .weak   \handler
    .set    \handler, Default_Handler
    .endm

    IRQ     CKRDY_IRQHandler
    IRQ     LVD_IRQHandler
    IRQ     BOD_IRQHandler
    IRQ     WDT_IRQHandler
    IRQ     RTC_IRQHandler
    IRQ     FLASH_IRQHandler
    IRQ     EVWUP_IRQHandler
    IRQ     LPWUP_IRQHandler
    IRQ     EXTI0_IRQHandler
    IRQ     EXTI1_IRQHandler
    IRQ     EXTI2_IRQHandler
    IRQ     EXTI3_IRQHandler
    IRQ     EXTI4_IRQHandler
    IRQ     EXTI5_IRQHandler
    IRQ     EXTI6_IRQHandler
    IRQ     EXTI7_IRQHandler
    IRQ     EXTI8_IRQHandler
    IRQ     EXTI9_IRQHandler
    IRQ     EXTI10_IRQHandler
    IRQ     EXTI11_IRQHandler
    IRQ     EXTI12_IRQHandler
    IRQ     EXTI13_IRQHandler
    IRQ     EXTI14_IRQHandler
    IRQ     EXTI15_IRQHandler
    IRQ     COMP_IRQHandler
    IRQ     ADC_IRQHandler
    IRQ     MCTM0BRK_IRQHandler
    IRQ     MCTM0UP_IRQHandler
    IRQ     MCTM0TR_IRQHandler
    IRQ     MCTM0CC_IRQHandler
    IRQ     MCTM1BRK_IRQHandler
    IRQ     MCTM1UP_IRQHandler
    IRQ     MCTM1TR_IRQHandler
    IRQ     MCTM1CC_IRQHandler
    IRQ     GPTM0_IRQHandler
    IRQ     GPTM1_IRQHandler
    IRQ     BFTM0_IRQHandler
    IRQ     BFTM1_IRQHandler
    IRQ     I2C0_IRQHandler
    IRQ     I2C1_IRQHandler
    IRQ     SPI0_IRQHandler
    IRQ     SPI1_IRQHandler
    IRQ     USART0_IRQHandler
    IRQ     USART1_IRQHandler
    IRQ     UART0_IRQHandler
    IRQ     UART1_IRQHandler
    IRQ     SCI_IRQHandler
    IRQ     I2S_IRQHandler
    IRQ     USB_IRQHandler
    IRQ     SDIO_IRQHandler
    IRQ     PDMA_CH0_IRQHandler
    IRQ     PDMA_CH1_IRQHandler
    IRQ     PDMA_CH2_IRQHandler
    IRQ     PDMA_CH3_IRQHandler
    IRQ     PDMA_CH4_IRQHandler
    IRQ     PDMA_CH5_IRQHandler
    IRQ     PDMA_CH6_IRQHandler
    IRQ     PDMA_CH7_IRQHandler
    IRQ     PDMA_CH8_IRQHandler
    IRQ     PDMA_CH9_IRQHandler
    IRQ     PDMA_CH10_IRQHandler
    IRQ     PDMA_CH11_IRQHandler
    IRQ     CSIF_IRQHandler
    IRQ     EBI_IRQHandler
    IRQ     AES_IRQHandler

    .end
