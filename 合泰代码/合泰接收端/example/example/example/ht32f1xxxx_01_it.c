/*********************************************************************************************************//**
 * @file    USBD/HID_Keyboard_Joystick/ht32f1xxxx_01_it.c
 * @version $Rev:: 427          $
 * @date    $Date:: 2017-07-04 #$
 * @brief   This file provides all interrupt service routine.
 *************************************************************************************************************
 * @attention
 *
 * Firmware Disclaimer Information
 *
 * 1. The customer hereby acknowledges and agrees that the program technical documentation, including the
 *    code, which is supplied by Holtek Semiconductor Inc., (hereinafter referred to as "HOLTEK") is the
 *    proprietary and confidential intellectual property of HOLTEK, and is protected by copyright law and
 *    other intellectual property laws.
 *
 * 2. The customer hereby acknowledges and agrees that the program technical documentation, including the
 *    code, is confidential information belonging to HOLTEK, and must not be disclosed to any third parties
 *    other than HOLTEK and the customer.
 *
 * 3. The program technical documentation, including the code, is provided "as is" and for customer reference
 *    only. After delivery by HOLTEK, the customer shall use the program technical documentation, including
 *    the code, at their own risk. HOLTEK disclaims any expressed, implied or statutory warranties, including
 *    the warranties of merchantability, satisfactory quality and fitness for a particular purpose.
 *
 * <h2><center>Copyright (C) Holtek Semiconductor Inc. All rights reserved</center></h2>
 ************************************************************************************************************/

/* Includes ------------------------------------------------------------------------------------------------*/
#include "ht32.h"
#include "ht32_board.h"
#include "ht32_board_config.h"
#include "ht32_usbd_core.h"
#include "ht32_usbd_class.h"

/** @addtogroup HT32_Series_Peripheral_Examples HT32 Peripheral Examples
  * @{
  */

/** @addtogroup USBD_Examples USBD
  * @{
  */

/** @addtogroup HID_Keyboard_Joystick
  * @{
  */


/* Global functions ----------------------------------------------------------------------------------------*/
/*********************************************************************************************************//**
 * @brief   This function CAPSLOCK handles EXTI interrupt.
 * @retval  None
 ************************************************************************************************************/
void HTCFG_EXTI_CAPSLOCK_FUN(void)
{
  extern vu32 gKeyStatus[HID_KEY_COUNT];
  gKeyStatus[HID_KEY_CAPSLOCK] = 1;
  EXTI_ClearEdgeFlag(KEY1_BUTTON_EXTI_CHANNEL);
}

/*********************************************************************************************************//**
 * @brief   This function handles SCROLLLOCK EXTI interrupt.
 * @retval  None
 ************************************************************************************************************/
void HTCFG_EXTI_SCROLLLOCK_FUN(void)
{
  extern vu32 gKeyStatus[HID_KEY_COUNT];
  gKeyStatus[HID_KEY_SCROLLLOCK] = 1;
  EXTI_ClearEdgeFlag(KEY2_BUTTON_EXTI_CHANNEL);
}

/*********************************************************************************************************//**
 * @brief   This function handles NUMLOCK EXTI interrupt.
 * @retval  None
 ************************************************************************************************************/
void HTCFG_EXTI_NUMLOCK_FUN(void)
{
  extern vu32 gKeyStatus[HID_KEY_COUNT];
  gKeyStatus[HID_KEY_NUMLOCK] = 1;
  EXTI_ClearEdgeFlag(WAKEUP_BUTTON_EXTI_CHANNEL);
}

/*********************************************************************************************************//**
 * @brief   This function handles USB interrupt.
 * @retval  None
 ************************************************************************************************************/
void USB_IRQHandler(void)
{
  __ALIGN4 extern USBDCore_TypeDef gUSBCore;
  USBDCore_IRQHandler(&gUSBCore);
}


/**
  * @}
  */

/**
  * @}
  */

/**
  * @}
  */
