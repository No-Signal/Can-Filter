/* USER CODE BEGIN Header */
/**
 ******************************************************************************
 * @file           : main.c
 * @brief          : Main program body
 ******************************************************************************
 * @attention
 *
 * Copyright (c) 2022 STMicroelectronics.
 * All rights reserved.
 *
 * This software is licensed under terms that can be found in the LICENSE file
 * in the root directory of this software component.
 * If no LICENSE file comes with this software, it is provided AS-IS.
 *
 ******************************************************************************
 */
#include "main.h"
#include "can.h"
#include "iwdg.h"
#include "gpio.h"

#include "stdio.h"
#include <string.h>
#include "can-filter.h"
#include "can-remap.h"
#include "USER_SETTINGS.h"

void SystemClock_Config(void);

int main(void)
{
  /* USER CODE BEGIN 1 */
  CAN_FRAME frame;
  /* USER CODE END 1 */

  /* MCU Configuration--------------------------------------------------------*/
  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */

  HAL_Init();

  /* Configure the system clock */
  SystemClock_Config();

  MX_GPIO_Init();
  MX_CAN1_Init();
  MX_CAN2_Init();

  //MX_IWDG_Init(); //Init watchdog

  HAL_CAN_RegisterCallback(&hcan1, HAL_CAN_RX_FIFO0_MSG_PENDING_CB_ID, HAL_CAN_RxFIFO0MsgPendingCallback1);
  HAL_CAN_RegisterCallback(&hcan1, HAL_CAN_RX_FIFO1_MSG_PENDING_CB_ID, HAL_CAN_RxFIFO1MsgPendingCallback1);
  HAL_CAN_RegisterCallback(&hcan2, HAL_CAN_RX_FIFO0_MSG_PENDING_CB_ID, HAL_CAN_RxFIFO0MsgPendingCallback2);
  HAL_CAN_RegisterCallback(&hcan2, HAL_CAN_RX_FIFO1_MSG_PENDING_CB_ID, HAL_CAN_RxFIFO1MsgPendingCallback2);

  HAL_CAN_ActivateNotification(&hcan1, CAN_IT_RX_FIFO0_MSG_PENDING);
  HAL_CAN_ActivateNotification(&hcan2, CAN_IT_RX_FIFO1_MSG_PENDING);

  AddCANFilters(&hcan1);
  AddCANFilters(&hcan2);

  while (1)
  {
    //HAL_IWDG_Refresh(&hiwdg);

    // From Battery Emulator
    if (LenCan(MYCAN1, CAN_RX) > 0)
    {
      PopCan(MYCAN1, CAN_RX, &frame);

#ifdef INVERTER_ALLOWLIST
      can_filter_allow_list(MYCAN2, &frame);
#endif
#ifdef BATTERY_REMAP
      can_handler_to_battery(MYCAN2, &frame);
#endif
#ifdef BLOCK_NON_EXTENDED_IDS
      can_filter_extended_ids_only(MYCAN2, &frame);
#endif
    }

    // From Inverter
    if (LenCan(MYCAN2, CAN_RX) > 0)
    {
      PopCan(MYCAN2, CAN_RX, &frame);

#if defined(INVERTER_ALLOWLIST) || defined(BLOCK_NON_EXTENDED_IDS)
      PushCan(MYCAN1, CAN_TX, &frame);
#endif
#ifdef BATTERY_REMAP
      can_handler_to_battery_emulator(MYCAN1, &frame);
#endif
    }

    sendCan(MYCAN1);
    sendCan(MYCAN2);
  }
}

/**
 * @brief System Clock Configuration
 * @retval None
 */
void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

  /** Initializes the RCC Oscillators according to the specified parameters
   * in the RCC_OscInitTypeDef structure.
   */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_LSI | RCC_OSCILLATORTYPE_HSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_ON;
  RCC_OscInitStruct.HSEPredivValue = RCC_HSE_PREDIV_DIV5;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.LSIState = RCC_LSI_ON;
  RCC_OscInitStruct.Prediv1Source = RCC_PREDIV1_SOURCE_PLL2;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
  RCC_OscInitStruct.PLL.PLLMUL = RCC_PLL_MUL9;
  RCC_OscInitStruct.PLL2.PLL2State = RCC_PLL2_ON;
  RCC_OscInitStruct.PLL2.PLL2MUL = RCC_PLL2_MUL8;
  RCC_OscInitStruct.PLL2.HSEPrediv2Value = RCC_HSE_PREDIV2_DIV5;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }

  /** Initializes the CPU, AHB and APB buses clocks
   */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK | RCC_CLOCKTYPE_SYSCLK | RCC_CLOCKTYPE_PCLK1 | RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV2; // DIV1 is original for 72Mhz
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;  // DIV2 is original for 72Mhz
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_2) != HAL_OK)
  {
    Error_Handler();
  }

  /** Configure the Systick interrupt time
   */
  __HAL_RCC_PLLI2S_ENABLE();
}

/**
 * @brief  This function is executed in case of error occurrence.
 * @retval None
 */
void Error_Handler(void)
{
  /* User can add his own implementation to report the HAL error return state */
  __disable_irq();
  HAL_NVIC_SystemReset();
}
