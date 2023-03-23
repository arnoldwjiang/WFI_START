/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file    gpio.h
  * @brief   This file contains all the function prototypes for
  *          the gpio.c file
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
#ifndef __GPIO_H__
#define __GPIO_H__

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "main.h"

/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* USER CODE BEGIN Private defines */
	
#define SAT5V_DET_VALUE		HAL_GPIO_ReadPin(GPIOA,GPIO_PIN_0)		//PA0=0
	
#define LED_ON			HAL_GPIO_WritePin(GPIOA,GPIO_PIN_2,GPIO_PIN_RESET)		//PA2=0
#define LED_OFF			HAL_GPIO_WritePin(GPIOA,GPIO_PIN_2,GPIO_PIN_SET)		//PA2=1
	
#define DIFF_ON			HAL_GPIO_WritePin(GPIOA,GPIO_PIN_3,GPIO_PIN_RESET)		//PA3=0
#define DIFF_OFF		HAL_GPIO_WritePin(GPIOA,GPIO_PIN_3,GPIO_PIN_SET)		//PA3=1	
	
#define DIFF_SWWIFI		HAL_GPIO_WritePin(GPIOA,GPIO_PIN_4,GPIO_PIN_RESET)		//PA4=0
#define DIFF_SWSATIN	HAL_GPIO_WritePin(GPIOA,GPIO_PIN_4,GPIO_PIN_SET)		//PA4=1	
	
#define DC3V_OFF		HAL_GPIO_WritePin(GPIOA,GPIO_PIN_5,GPIO_PIN_RESET)		//PA5=0
#define DC3V_ON			HAL_GPIO_WritePin(GPIOA,GPIO_PIN_5,GPIO_PIN_SET)		//PA5=1
	
#define DC5V_OFF		HAL_GPIO_WritePin(GPIOA,GPIO_PIN_6,GPIO_PIN_RESET)		//PA6=0
#define DC5V_ON			HAL_GPIO_WritePin(GPIOA,GPIO_PIN_6,GPIO_PIN_SET)		//PA6=1	

#define SSD_DC5VIN_ON	HAL_GPIO_WritePin(GPIOB,GPIO_PIN_3,GPIO_PIN_RESET); \
						HAL_GPIO_WritePin(GPIOA,GPIO_PIN_15,GPIO_PIN_RESET)		//PB3=0 & PA15=0
#define SSD_DC5VIN_OFF	HAL_GPIO_WritePin(GPIOB,GPIO_PIN_3,GPIO_PIN_SET); \
						HAL_GPIO_WritePin(GPIOA,GPIO_PIN_15,GPIO_PIN_SET)		//PB3=1 & PA15=1
						
#define SSD_SAT5VIN_ON	HAL_GPIO_WritePin(GPIOB,GPIO_PIN_7,GPIO_PIN_RESET); \
						HAL_GPIO_WritePin(GPIOB,GPIO_PIN_6,GPIO_PIN_RESET)		//PB7=0 & PB6=0
#define SSD_SAT5VIN_OFF	HAL_GPIO_WritePin(GPIOB,GPIO_PIN_7,GPIO_PIN_SET); \
						HAL_GPIO_WritePin(GPIOB,GPIO_PIN_6,GPIO_PIN_SET)		//PB7=1 & PB6=1
						
/* USER CODE END Private defines */

void MX_GPIO_Init(void);

/* USER CODE BEGIN Prototypes */
void SATA_SW_CLOSE(void);
void SATA_SW_IN(void);
void SATA_SW_WIFI(void);
void WIFI_PWR_ON(void);
void WIFI_PWR_OFF(void);

/* USER CODE END Prototypes */

#ifdef __cplusplus
}
#endif
#endif /*__ GPIO_H__ */

