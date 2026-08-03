
#pragma once

/* Enable C linkage for C++ Compilers: */
#if defined(__cplusplus)
extern "C" {
#endif

#include "app_types.h"

#ifndef MCU_CORE_8258
    #define MCU_CORE_8258       1
#endif

#define ON                      1
#define OFF                     0

/* for reporting */
#define REPORTING_MIN       60              /* 1 min            */
#define REPORTING_MAX       300             /* 5 min            */

#define MY_RF_POWER_INDEX   RF_POWER_INDEX_P10p46dBm


/**********************************************************************
 * Product Information
 * max 24 symbols
 */

#define ZCL_BASIC_MFG_NAME     {8,'h','o','p','s','-','D','I','Y'}
#define ZCL_BASIC_MODEL_ID     {18,'l','u','m','i','.','s','w','i','t','c','h','.','b','2','n','c','0','1'} 


/**********************************************************************
 * Version configuration
 */

#include "version_cfg.h"

/* Debug mode config */
#define UART_PRINTF_MODE                OFF
#define DEBUG_SAVE	                    ON
#define DEBUG_BUTTON                    ON
#define DEBUG_SWITCH                    ON
#define DEBUG_MONITORING                OFF
#define DEBUG_ONOFF                     ON
#define DEBUG_TIME                      OFF
#define DEBUG_REPORTING                 OFF
#define DEBUG_OTA                       OFF
#define DEBUG_STA_STATUS                OFF

#define USB_PRINTF_MODE                 OFF

/* PM */
#define PM_ENABLE                       OFF

/* PA */
#define PA_ENABLE                       OFF

/* BDB */
#define TOUCHLINK_SUPPORT               OFF
#define FIND_AND_BIND_SUPPORT           OFF

/* Board ID */
#define BOARD_826x_EVK                  0
#define BOARD_826x_DONGLE               1
#define BOARD_826x_DONGLE_PA            2
#define BOARD_8258_EVK                  3
#define BOARD_8258_EVK_V1P2             4//C1T139A30_V1.2
#define BOARD_8258_DONGLE               5
#define BOARD_8278_EVK                  6
#define BOARD_8278_DONGLE               7
#define BOARD_B91_EVK                   8
#define BOARD_B91_DONGLE                9
#define BOARD_TUYA_ZTU                  10

/* Board define */
#if defined(MCU_CORE_8258)
    #define BEGIN_USER_DATA             0x72000   // (FLASH_ADDR_OF_APP_FW + FW_DATA_SIZE)   // begin address for saving energy
    #define END_USER_DATA               0x76000   // (BEGIN_USER_DATA + USER_DATA_SIZE)
    #define USER_DATA_SIZE              (END_USER_DATA - BEGIN_USER_DATA)   //(FLASH_ADDR_OF_OTA_IMAGE - BEGIN_USER_DATA)

    #define BOARD                       BOARD_TUYA_ZTU
    #define CLOCK_SYS_CLOCK_HZ          48000000
    #define NV_ITEM_APP_USER_CFG        (NV_ITEM_APP_GP_TRANS_TABLE + 1)        // see sdk/proj/drivers/drv_nv.h
#else
    #error "MCU is undefined!"
#endif

/* Board include */
#if (BOARD == BOARD_TUYA_ZTU)
    #include "board_tuya_ztu.h"
#endif


/* Voltage detect module */
/* If VOLTAGE_DETECT_ENABLE is set,
 * 1) if MCU_CORE_826x is defined, the DRV_ADC_VBAT_MODE mode is used by default,
 * and there is no need to configure the detection IO port;
 * 2) if MCU_CORE_8258 or MCU_CORE_8278 is defined, the DRV_ADC_VBAT_MODE mode is used by default,
 * we need to configure the detection IO port, and the IO must be in a floating state.
 * 3) if MCU_CORE_B91 is defined, the DRV_ADC_BASE_MODE mode is used by default,
 * we need to configure the detection IO port, and the IO must be connected to the target under test,
 * such as VCC.
 */
#define VOLTAGE_DETECT_ENABLE                       OFF

#if defined(MCU_CORE_826x)
    #define VOLTAGE_DETECT_ADC_PIN                  0
#elif defined(MCU_CORE_8258) || defined(MCU_CORE_8278)
    #define VOLTAGE_DETECT_ADC_PIN                  GPIO_PC5
#elif defined(MCU_CORE_B91)
    #define VOLTAGE_DETECT_ADC_PIN                  ADC_GPIO_PB0
#endif


/* Watch dog module */
#define MODULE_WATCHDOG_ENABLE                      OFF

/* UART module */
#define MODULE_UART_ENABLE                          OFF

#if (ZBHCI_USB_PRINT || ZBHCI_USB_CDC || ZBHCI_USB_HID || ZBHCI_UART)
    #define ZBHCI_EN                                1
#endif

/**********************************************************************
 * ZCL cluster support setting
 */
#define ZCL_GROUP_SUPPORT                           OFF
#define ZCL_SCENE_SUPPORT                           OFF
#define ZCL_ON_OFF_SUPPORT                          ON
#define ZCL_ON_OFF_SWITCH_CFG_SUPPORT               ON
#define ZCL_OTA_SUPPORT                             OFF
#define ZCL_GP_SUPPORT                              ON
#define ZCL_METERING_SUPPORT                        OFF
#define ZCL_ELECTRICAL_MEASUREMENT_SUPPORT          OFF
#define ZCL_MULTISTATE_INPUT_SUPPORT                ON
#if TOUCHLINK_SUPPORT
#define ZCL_ZLL_COMMISSIONING_SUPPORT               OFF
#endif

/**********************************************************************
 * Stack configuration
 */
#include "stack_cfg.h"


/**********************************************************************
 * EV configuration
 */
typedef enum{
    EV_POLL_ED_DETECT,
    EV_POLL_HCI,
    EV_POLL_IDLE,
    EV_POLL_MAX,
}ev_poll_e;

/* Disable C linkage for C++ Compilers: */
#if defined(__cplusplus)
}
#endif
