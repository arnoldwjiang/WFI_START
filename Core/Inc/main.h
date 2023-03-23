/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2023 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MAIN_H
#define __MAIN_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32l0xx_hal.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "delay.h"
/* USER CODE END Includes */

/* Exported types ------------------------------------------------------------*/
/* USER CODE BEGIN ET */

/* USER CODE END ET */

/* Exported constants --------------------------------------------------------*/
/* USER CODE BEGIN EC */

/* USER CODE END EC */

/* Exported macro ------------------------------------------------------------*/
/* USER CODE BEGIN EM */

/* USER CODE END EM */

/* Exported functions prototypes ---------------------------------------------*/
void Error_Handler(void);

/* USER CODE BEGIN EFP */

/* USER CODE END EFP */

/* Private defines -----------------------------------------------------------*/
#define SAT5V_DET_Pin GPIO_PIN_0
#define SAT5V_DET_GPIO_Port GPIOA
#define SAT5V_DET_EXTI_IRQn EXTI0_1_IRQn
#define LED_Pin GPIO_PIN_2
#define LED_GPIO_Port GPIOA
#define DIFF_EN_Pin GPIO_PIN_3
#define DIFF_EN_GPIO_Port GPIOA
#define DIFF_SW_Pin GPIO_PIN_4
#define DIFF_SW_GPIO_Port GPIOA
#define SSD_3V_EN_Pin GPIO_PIN_5
#define SSD_3V_EN_GPIO_Port GPIOA
#define SSD_5V_EN_Pin GPIO_PIN_6
#define SSD_5V_EN_GPIO_Port GPIOA
#define DC5V_EN2_Pin GPIO_PIN_15
#define DC5V_EN2_GPIO_Port GPIOA
#define DC5V_EN1_Pin GPIO_PIN_3
#define DC5V_EN1_GPIO_Port GPIOB
#define S5VIN_EN2_Pin GPIO_PIN_6
#define S5VIN_EN2_GPIO_Port GPIOB
#define S5VIN_EN1_Pin GPIO_PIN_7
#define S5VIN_EN1_GPIO_Port GPIOB
/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */
