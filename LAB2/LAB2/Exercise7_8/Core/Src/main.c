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
int timer0_counter = 0;
int timer0_flag = 0;
int TIMER_CYCLE = 10;

void setTimer0(int duration){
	timer0_counter = duration/TIMER_CYCLE;
	timer0_flag = 0;
}

void timer_run(){
	if(timer0_counter > 0){
		timer0_counter--;
		if(timer0_counter == 0){
			timer0_flag = 1;
		}
	}
}

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
//Số LED 7SEG tối đa
const int MAX_LED = 4;
//Mảng để biết led nào hiển thị
int enable[4] = {0xE, 0xD, 0xB, 0x7};
//Mảng chứa số sẽ hiện trên các LED 7 SEG
int led_buffer[4] = {5, 2, 8, 9};
int hour = 15, minute = 8, second = 50;
int index_led = 0;
//Hiển thị số trên LED 7 đoạn bằng đưa vào số ở dãy nums
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
//Hàm để chọn LED 7 đoạn nào được hiển thị
void setEnable(int num){
	HAL_GPIO_WritePin(GPIOA, GPIO_PIN_6, (num>>0 & 0x1));
	HAL_GPIO_WritePin(GPIOA, GPIO_PIN_7, (num>>1 & 0x1));
	HAL_GPIO_WritePin(GPIOA, GPIO_PIN_8, (num>>2 & 0x1));
	HAL_GPIO_WritePin(GPIOA, GPIO_PIN_9, (num>>3 & 0x1));
}
//Hàm update lại số hiển thị trên LED 7SEG và LED 7SEG nào được hiển thị
void update7SEG(int index){
		display7SEG(nums[led_buffer[index]]);	//Hiển thị led_buffer[index] trên LED 7 SEG
		setEnable(enable[index]);				//Set enable LED 7 SEG thứ index hoạt động
}

void updateClockBuffer(){
//	Update hour to led_buffer
//	Lấy con số hàng chục của hour
	led_buffer[0] = hour/10;
//	Lấy con số hàng đơn vị của hour
	led_buffer[1] = hour%10;
//	Update minute to led_buffer
//	Lấy con số hàng chục của minute
	led_buffer[2] = minute/10;
// Lấy con số hàng đơn vị của minute
	led_buffer[3] = minute%10;
}

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
//  Delay 1s đầu tiên
  setTimer0(1000);
  while (1)
  {
    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
//	  Kiểm tra thời gian delay đã đủ chưa?
//	  Delay mỗi lần 1s
	  if(timer0_flag == 1){
//		  Cập nhật second thêm 1 đơn vị
		  second++;
//		  Nếu second đến giây 60 thì reset về 0 và tăng minute thêm 1
		  if(second >= 60){
			  second = 0;
			  minute++;
		  }
//		  Nếu minute đến phút 60 thì reset về 0 và tăng hour thêm 1
		  if(minute >= 60){
			  minute = 0;
			  hour++;
		  }
//		  Nếu hour đến 23 giờ thì reset về 0
		  if(hour >= 24){
			  hour = 0;
		  }
//		  Chớp tắt các led
		  HAL_GPIO_TogglePin(GPIOA, GPIO_PIN_5);
		  HAL_GPIO_TogglePin(GPIOA, GPIO_PIN_4);
//		  Update lại hour, minute, second
		  updateClockBuffer();
//		  Hiện LED 7 đoạn tương ứng mỗi giây 1 LED 7 SEG
		  update7SEG(index_led++);
//		  Reset lại index_led
		  if(index_led > 3) index_led = 0;
//		  Set thời gian delay 1s
		  setTimer0(1000);
	  }
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
  htim2.Init.Prescaler = 8000-1;
  htim2.Init.CounterMode = TIM_COUNTERMODE_UP;
  htim2.Init.Period = 10-1;
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
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim){
	timer_run();
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
