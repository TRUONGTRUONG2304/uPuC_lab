/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2021 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under BSD 3-Clause license,
  * the "License"; You may not use this file except in compliance with the
  * License. You may obtain a copy of the License at:
  *                        opensource.org/licenses/BSD-3-Clause
  *
  ******************************************************************************
  */
/* USER CODE END Header */
/* Includes ------------------------------------------------------------------*/
#include "main.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */
/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
TIM_HandleTypeDef htim2;

/* USER CODE BEGIN PV */

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_TIM2_Init(void);
/* USER CODE BEGIN PFP */

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
  HAL_TIM_Base_Start_IT(&htim2);
  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
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

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_NONE;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }
  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_HSI;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_0) != HAL_OK)
  {
    Error_Handler();
  }
}

/**
  * @brief TIM2 Initialization Function
  * @param None
  * @retval None
  */
static void MX_TIM2_Init(void)
{

  /* USER CODE BEGIN TIM2_Init 0 */

  /* USER CODE END TIM2_Init 0 */

  TIM_ClockConfigTypeDef sClockSourceConfig = {0};
  TIM_MasterConfigTypeDef sMasterConfig = {0};

  /* USER CODE BEGIN TIM2_Init 1 */

  /* USER CODE END TIM2_Init 1 */
  htim2.Instance = TIM2;
  htim2.Init.Prescaler = 7999;
  htim2.Init.CounterMode = TIM_COUNTERMODE_UP;
  htim2.Init.Period = 9;
  htim2.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
  htim2.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;
  if (HAL_TIM_Base_Init(&htim2) != HAL_OK)
  {
    Error_Handler();
  }
  sClockSourceConfig.ClockSource = TIM_CLOCKSOURCE_INTERNAL;
  if (HAL_TIM_ConfigClockSource(&htim2, &sClockSourceConfig) != HAL_OK)
  {
    Error_Handler();
  }
  sMasterConfig.MasterOutputTrigger = TIM_TRGO_RESET;
  sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
  if (HAL_TIMEx_MasterConfigSynchronization(&htim2, &sMasterConfig) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN TIM2_Init 2 */

  /* USER CODE END TIM2_Init 2 */

}

/**
  * @brief GPIO Initialization Function
  * @param None
  * @retval None
  */
static void MX_GPIO_Init(void)
{
  GPIO_InitTypeDef GPIO_InitStruct = {0};

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOD_CLK_ENABLE();
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOA, GPIO_PIN_4|GPIO_PIN_5|GPIO_PIN_6|GPIO_PIN_7
                          |GPIO_PIN_8|GPIO_PIN_9, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOB, GPIO_PIN_0|GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3
                          |GPIO_PIN_4|GPIO_PIN_5|GPIO_PIN_6, GPIO_PIN_RESET);

  /*Configure GPIO pins : PA4 PA5 PA6 PA7
                           PA8 PA9 */
  GPIO_InitStruct.Pin = GPIO_PIN_4|GPIO_PIN_5|GPIO_PIN_6|GPIO_PIN_7
                          |GPIO_PIN_8|GPIO_PIN_9;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

  /*Configure GPIO pins : PB0 PB1 PB2 PB3
                           PB4 PB5 PB6 */
  GPIO_InitStruct.Pin = GPIO_PIN_0|GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3
                          |GPIO_PIN_4|GPIO_PIN_5|GPIO_PIN_6;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

}

/* USER CODE BEGIN 4 */
//g f e d c b a => PB6 PB5 PB4 PB3 PB2 PB1 PB0
int nums[10] = {
		0x40,				//0
		0x79, 				//1
		0x24,				//2
		0x30,				//3
		0x19,				//4
		0x12,				//5
		0x02,				//6
		0x70,				//7
		0x00,				//8
		0x10};				//9
//Hiển thị số trên LED 7 đoạn bằng bằng truyền vào số ở dãy nums
//Sau đó lấy từng bit rồi viết vào trong PIN
//Bằng cách dịch từng bit và and với 1;
void display7SEG(int count){
	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_0, (count>>0 & 0x1));
	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_1, (count>>1 & 0x1));
	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_2, (count>>2 & 0x1));
	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_3, (count>>3 & 0x1));
	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_4, (count>>4 & 0x1));
	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_5, (count>>5 & 0x1));
	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_6, (count>>6 & 0x1));
}
//Mảng để chọn led nào hiển thị
int enable[] = {0xE, 0xD, 0xB, 0x7};
//Hàm để chọn LED 7 đoạn nào được hiển thị
//
void setEnable(int num){
	HAL_GPIO_WritePin(GPIOA, GPIO_PIN_6, (num>>0 & 0x1));
	HAL_GPIO_WritePin(GPIOA, GPIO_PIN_7, (num>>1 & 0x1));
	HAL_GPIO_WritePin(GPIOA, GPIO_PIN_8, (num>>2 & 0x1));
	HAL_GPIO_WritePin(GPIOA, GPIO_PIN_9, (num>>3 & 0x1));
}
//Số LED 7SEG tối đa
const int MAX_LED = 4;
//Mảng chứa số sẽ hiện trên các LED 7 SEG
int led_buffer[4] = {5, 2, 8, 9};
void update7SEG(int index){
//	Hiển thị 7 SEG với giá trị tương ứng trong nums
//	Set enable cho biết 7 SEG nào sẽ sáng
	switch(index){
	case 0:
		display7SEG(nums[led_buffer[index]]);
		setEnable(enable[0]);
		break;
	case 1:
		display7SEG(nums[led_buffer[index]]);
		setEnable(enable[1]);
		break;
	case 2:
		display7SEG(nums[led_buffer[index]]);
		setEnable(enable[2]);
		break;
	case 3:
		display7SEG(nums[led_buffer[index]]);
		setEnable(enable[3]);
		break;
	default:
		break;
	}
}
//Exercise 2
////Counter = đếm số lần interupt, flag = xác định led nào sáng, dot = dấu chấm 2 chấm (2 led đơn)
//int counter = 50, flag = 0, dot = 0;
//void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim){
//	counter--;
//	if(counter <= 0){
//		counter = 50;
//		HAL_GPIO_TogglePin(GPIOA, GPIO_PIN_5); //LED đơn PA5 chớp tắt mỗi 0.5s
//		flag++;
//		dot++;
//		if(dot == 2){
//			dot = 0;
//			HAL_GPIO_TogglePin(GPIOA, GPIO_PIN_4); //Dấu 2 chấm chớt tắt mỗi 1s
//		}
//		if(flag > 3) flag = 0;
//	}
////	7 SEG thứ nhất sáng hiển thị 1
//	if(flag == 0) {
//		display7SEG(nums[1]);
//		setEnable(enable[0]);
//	}
////	7 SEG thứ hai sáng hiển thị 2
//	else if(flag == 1){
//		display7SEG(nums[2]);
//		setEnable(enable[1]);
//	}
////	7 SEG thứ ba sáng hiển thị 3
//	else if(flag == 2){
//		display7SEG(nums[3]);
//		setEnable(enable[2]);
//	}
////	7 SEG thứ tư sáng hiển thị 0
//	else if(flag == 3){
//		display7SEG(nums[0]);
//		setEnable(enable[3]);
//	}
//}
//End exercise2

//Exercise 3
//Counter = đếm số lần interupt, flag = xác định led nào sáng, dot = dấu chấm 2 chấm (2 led đơn)
int counter = 25, index_led = 0, dot = 0;
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim){
	counter--;
	if(counter <= 0) {
		counter = 25;
		HAL_GPIO_TogglePin(GPIOA, GPIO_PIN_5); //LED đơn PA5 chớp tắt mỗi 0.5s
		dot++;
		//Dấu 2 chấm chớt tắt mỗi 1s
		if(dot == 2){
			dot = 0;
			HAL_GPIO_TogglePin(GPIOA, GPIO_PIN_4);
		}
//		Gọi hàm để update 7 seg với giá trị tương ứng
		update7SEG(index_led++);
//		Reset giá trị index_led do index_led từ 0->3
		if(index_led > 3) index_led = 0;
	}
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

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
