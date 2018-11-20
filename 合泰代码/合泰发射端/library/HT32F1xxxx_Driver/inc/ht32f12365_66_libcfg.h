/*********************************************************************************************************//**
 * @file    ht32f12365_66_libcfg.h
 * @version $Rev:: 949          $
 * @date    $Date:: 2017-12-11 #$
 * @brief   The library configuration file.
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
/* Define to prevent recursive inclusion -------------------------------------------------------------------*/
#ifndef __HT32F12365_66_LIBCFG_H
#define __HT32F12365_66_LIBCFG_H

/* Settings ------------------------------------------------------------------------------------------------*/

#if !defined(USE_MEM_HT32F12365) && !defined(USE_MEM_HT32F12366) && !defined(USE_MEM_HT32F22366)
#define USE_MEM_HT32F12366
#endif

#define LIBCFG_FLASH_PAGESIZE             (1024)

#ifdef USE_MEM_HT32F12365
  #define LIBCFG_FLASH_SIZE               (LIBCFG_FLASH_PAGESIZE * 255)
  #define LIBCFG_RAM_SIZE                 (1024 * 64)
  #define LIBCFG_CHIPNAME                 (0x12365)
#endif

#ifdef USE_MEM_HT32F12366
  #define LIBCFG_FLASH_SIZE               (LIBCFG_FLASH_PAGESIZE * 255)
  #define LIBCFG_RAM_SIZE                 (1024 * 128)
  #define LIBCFG_CHIPNAME                 (0x12366)
#endif

#ifdef USE_MEM_HT32F22366
  #define LIBCFG_FLASH_SIZE               (LIBCFG_FLASH_PAGESIZE * 255)
  #define LIBCFG_RAM_SIZE                 (1024 * 128)
  #define LIBCFG_CHIPNAME                 (0x22366)
#endif

#define LIBCFG_AES                        (1)
#define LIBCFG_CSIF                       (1)
#define LIBCFG_GPIOE                      (1)
#define LIBCFG_SCI0                       (1)
#define LIBCFG_SCI1                       (1)
#define LIBCFG_SDIO                       (1)

#define LIBCFG_ADC_CH12_15                (1)
#define LIBCFC_CKCU_USB_PLL               (1)
#define LIBCFG_EBI_BYTELAND_ASYNCREADY    (1)
#define LIBCFG_FLASH_2PAGE_PER_WPBIT      (1)
#define LIBCFG_PDMA_CH8_11                (1)
#define LIBCFG_RTC_LSI_LOAD_TRIM          (1)

#endif
