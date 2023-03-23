/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
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
/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "tim.h"
#include "gpio.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "delay.h"
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */
#define IDLE			0
#define SATA_CLOSE		1
#define SW_DELAY		2
#define SATA_IN			3
#define SATA_WIFI		4
#define WIFI_DELAY		5
#define WIFI_OFF		6
#define MCU_WFI			7


#define TIME_START	0
#define TIME_COUNT	1
#define TIME_STOP	2

#define SATAIN_MODE		0
#define WIFI_MODE		1
/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/

/* USER CODE BEGIN PV */
uint8_t mode_flag;

uint8_t current_state;

uint8_t time_flag;
uint32_t time_count;

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
/* USER CODE BEGIN PFP */
void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin);
void  HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim);
void TIM2_Start(void);
void TIM2_Stop(void);
/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{
  /* USER CODE BEGIN 1 */

  /* USER CODE END 1 */

  /* MCU Configuration--------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();

  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* Configure the system clock */
  SystemClock_Config();

  /* USER CODE BEGIN SysInit */

  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  MX_TIM2_Init();
  /* USER CODE BEGIN 2 */
  SATA_SW_CLOSE();
  
  if(SAT5V_DET_VALUE)	//SATA INPUT MODE
  {
	current_state = SATA_CLOSE;
	mode_flag = SATAIN_MODE;
  }
  else					//WIFI INPUT MODE
  {
	current_state = SATA_CLOSE;
	mode_flag = WIFI_MODE;
  }
  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {

	  switch(current_state)
	  {
		  case IDLE:
				delay_ms(1);
		  break;
		  
		  case SATA_CLOSE:	//关闭数据通道
				SATA_SW_CLOSE();

				current_state = SW_DELAY;
				time_flag = TIME_START;
		  break;
		  
		  case SW_DELAY:	//延时0.2s
			  if(time_flag == TIME_START)
			  {
				TIM2_Start();
				time_flag = TIME_COUNT;
			  }
			  else if(time_flag == TIME_COUNT)
			  {
				if(time_count >= 2)
				{
					time_flag = TIME_STOP;
				}
			  }
			  else if(time_flag == TIME_STOP)
			  {
				TIM2_Stop();
				  
				if(mode_flag == SATAIN_MODE)	//流程图2，SATA INPUT连接SSD
				{
					current_state = SATA_IN;
				}
				else if(mode_flag == WIFI_MODE)	//流程图1，WIFI模块连接SSD
				{
					current_state = SATA_WIFI;
				}
			  }

		  break;
				  
		  case SATA_IN:		//通道切换至SATA INPUT
				SATA_SW_IN();
				current_state = MCU_WFI;
		  break;
		  
		  case SATA_WIFI:	//通道切换至WIFI模块
				SATA_SW_WIFI();
				current_state = WIFI_DELAY;
				time_flag = TIME_START;
		  break;	  
		  
		  case WIFI_DELAY:		//延时5分钟,10*60*5=3000
			  if(time_flag == TIME_START)
			  {
				TIM2_Start();
				time_flag = TIME_COUNT;
			  }
			  else if(time_flag == TIME_COUNT)
			  {
				if(time_count >= 300)
				{
					time_flag = TIME_STOP;
				}
			  }
			  else if(time_flag == TIME_STOP)
			  {
				TIM2_Stop();

				current_state = WIFI_OFF;
			  }
		  break;
		  
		  case WIFI_OFF:
				WIFI_PWR_OFF();
				current_state = MCU_WFI;
		  break;
		  
		  case MCU_WFI:
				current_state = IDLE;
				__WFI();
		  break;
		  
		  default:
		  break;
	  
	  }
	  
	  
	  
	  
	  
	  
    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
  }
  /* USER CODE END 3 */
}

/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

  /** Configure the main internal regulator output voltage
  */
  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE1);

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSI;
  RCC_OscInitStruct.PLL.PLLMUL = RCC_PLLMUL_4;
  RCC_OscInitStruct.PLL.PLLDIV = RCC_PLLDIV_4;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }

  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_0) != HAL_OK)
  {
    Error_Handler();
  }
}

/* USER CODE BEGIN 4 */
void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)
{
	if(SAT5V_DET_VALUE)		//SATA INPUT MODE
	{
		mode_flag = SATAIN_MODE;
		current_state = SATA_CLOSE;
	}
	else		//WIFI INPUT MODE
	{
		mode_flag = WIFI_MODE;
		current_state = SATA_CLOSE;
	}
}

void  HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
	time_count++;
	HAL_GPIO_TogglePin(GPIOA,GPIO_PIN_2);
}

void TIM2_Start(void)
{			
	time_count = 0;
	
	/******** 清除定时器2的更新标志位 ********/
	__HAL_TIM_CLEAR_IT(&htim2, TIM_IT_UPDATE);

	/******** 开启定时器中断 并启动定时器 ********/
	HAL_TIM_Base_Start_IT(&htim2);
}

void TIM2_Stop(void)
{
	time_count = 0;

	/******** 关闭定时器中断 并关闭定时器********/
	HAL_TIM_Base_Stop_IT(&htim2);
	
	LED_OFF;
}



/* USER CODE END 4 */

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */
  __disable_irq();
  while (1)
  {
  }
  /* USER CODE END Error_Handler_Debug */
}

#ifdef  USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t *file, uint32_t line)
{
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */
