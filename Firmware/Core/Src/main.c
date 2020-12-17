/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2020 STMicroelectronics.
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
#include "dma.h"
#include "i2c.h"
#include "spi.h"
#include "tim.h"
#include "gpio.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include <math.h>
#include <stdbool.h>
#include <stdint.h>
#include "LCD_Nokia5110.h"
#include "menu.h"
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

/* USER CODE BEGIN PV */
extern mode_t mode;
extern bool song_chosen;
extern uint8_t song_index;
uint16_t *song;
uint8_t length;
uint16_t ameno[] = {E5, F5, F5, E5, F5, F5, F5, E5, F5, F5, F5, E5, F5, F5, G5, F5, F5, G5, F5, F5, F5, E5, E5, F5, E5, E5, E5, E5, F5, F5};
uint16_t dango[] = {E5, D5, G5, G5, A5, A5, B5, G5, D5, E5, D5, G5, G5, A5, A5, B5, B5, G5};
const uint16_t jingle[] = {
		E5, E5, E5, E5, E5, E5, E5, G5, C5, D5, E5,
		F5, F5, F5, F5, E5, E5, E5,
		E5, D5, D5, E5, D5, G5,
		E5, E5, E5, E5, E5, E5, E5, G5, C5, D5, E5,
		F5, F5, F5, F5, E5, E5, E5,
		G5, G5, F5, D5, C5
};
const uint16_t mary[] = {
		E5, D5, C5, D5, E5, E5, E5,
		D5, D5, D5, E5, G5, G5,
		E5, D5, C5, D5, E5, E5, E5,
		E5, D5, D5, E5, D5, C5
};
const uint16_t twinkle[] = {
		C5, C5, G5, G5, A5, A5, G5,
		F5, F5, E5, E5, D5, D5, C5,
		G5, G5, F5, F5, E5, E5, D5,
		G5, G5, F5, F5, E5, E5, D5,
		C5, C5, G5, G5, A5, A5, G5,
		F5, F5, E5, E5, D5, D5, C5
};
/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
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
  MX_DMA_Init();
  MX_SPI1_Init();
  MX_I2C1_Init();
  MX_TIM2_Init();
  MX_TIM1_Init();
  MX_TIM3_Init();
  /* USER CODE BEGIN 2 */
  HAL_Delay(500);
  HAL_TIM_PWM_Start(&htim2, TIM_CHANNEL_4);
  LCD_init();
  menu_init();
  uint8_t data;
  Read_From_24LCxx(0x1AAA, &data, 1);
  update_octave(&octave, data);
//  HAL_TIM_PWM_Start_DMA(&htim2, TIM_CHANNEL_4, (uint32_t *)piano, 10);

  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
	  if (mode == PIANO)
	  {
		  HAL_GPIO_WritePin(LED_A_GPIO_Port, LED_A_Pin, 1);
		  HAL_GPIO_WritePin(LED_B_GPIO_Port, LED_B_Pin, 1);
		  HAL_GPIO_WritePin(LED_C_GPIO_Port, LED_C_Pin, 1);
		  HAL_GPIO_WritePin(LED_D_GPIO_Port, LED_D_Pin, 1);
		  HAL_GPIO_WritePin(LED_E_GPIO_Port, LED_E_Pin, 1);
		  HAL_GPIO_WritePin(LED_F_GPIO_Port, LED_F_Pin, 1);
		  HAL_GPIO_WritePin(LED_G_GPIO_Port, LED_G_Pin, 1);

		  if (HAL_GPIO_ReadPin(C_NOTE_GPIO_Port, C_NOTE_Pin) == GPIO_PIN_SET)
		  {
			  __HAL_TIM_SET_AUTORELOAD(&htim2, octave.C);
			  __HAL_TIM_SET_COMPARE(&htim2, TIM_CHANNEL_4, 500);
		  }
		  else if (HAL_GPIO_ReadPin(D_NOTE_GPIO_Port, D_NOTE_Pin) == GPIO_PIN_SET)
		  {
			  __HAL_TIM_SET_AUTORELOAD(&htim2, octave.D);
			  __HAL_TIM_SET_COMPARE(&htim2, TIM_CHANNEL_4, 500);
		  }
		  else if (HAL_GPIO_ReadPin(E_NOTE_GPIO_Port, E_NOTE_Pin) == GPIO_PIN_SET)
		  {
			  __HAL_TIM_SET_AUTORELOAD(&htim2, octave.E);
			  __HAL_TIM_SET_COMPARE(&htim2, TIM_CHANNEL_4, 500);
		  }
		  else if (HAL_GPIO_ReadPin(F_NOTE_GPIO_Port, F_NOTE_Pin) == GPIO_PIN_SET)
		  {
			  __HAL_TIM_SET_AUTORELOAD(&htim2, octave.F);
			  __HAL_TIM_SET_COMPARE(&htim2, TIM_CHANNEL_4, 500);
		  }
		  else if (HAL_GPIO_ReadPin(G_NOTE_GPIO_Port, G_NOTE_Pin) == GPIO_PIN_SET)
		  {
			  __HAL_TIM_SET_AUTORELOAD(&htim2, octave.G);
			  __HAL_TIM_SET_COMPARE(&htim2, TIM_CHANNEL_4, 500);
		  }
		  else if (HAL_GPIO_ReadPin(A_NOTE_GPIO_Port, A_NOTE_Pin) == GPIO_PIN_SET)
		  {
			  __HAL_TIM_SET_AUTORELOAD(&htim2, octave.A);
			  __HAL_TIM_SET_COMPARE(&htim2, TIM_CHANNEL_4, 500);
		  }
		  else if (HAL_GPIO_ReadPin(B_NOTE_GPIO_Port, B_NOTE_Pin) == GPIO_PIN_SET)
		  {
			  __HAL_TIM_SET_AUTORELOAD(&htim2, octave.B);
			  __HAL_TIM_SET_COMPARE(&htim2, TIM_CHANNEL_4, 500);
		  }
		  else
		  {
			  __HAL_TIM_SET_COMPARE(&htim2, TIM_CHANNEL_4, 0);
		  }
	  }
	  if (mode == PRACTICE && song_chosen)
	  {
		  switch (song_index)
		  {
		  case 1:
			  song = jingle;
			  length = sizeof(jingle) / sizeof(uint16_t);
			  break;
		  case 2:
			  song = mary;
			  length = sizeof(mary) / sizeof(uint16_t);
			  break;
		  case 3:
			  song = twinkle;
			  length = sizeof(twinkle) / sizeof(uint16_t);
			  break;
		  }
		  for (int i = 0; i < length && song_chosen; i++)
		  {
			  HAL_GPIO_WritePin(LED_A_GPIO_Port, LED_A_Pin, 1);
			  HAL_GPIO_WritePin(LED_B_GPIO_Port, LED_B_Pin, 1);
			  HAL_GPIO_WritePin(LED_C_GPIO_Port, LED_C_Pin, 1);
			  HAL_GPIO_WritePin(LED_D_GPIO_Port, LED_D_Pin, 1);
			  HAL_GPIO_WritePin(LED_E_GPIO_Port, LED_E_Pin, 1);
			  HAL_GPIO_WritePin(LED_F_GPIO_Port, LED_F_Pin, 1);
			  HAL_GPIO_WritePin(LED_G_GPIO_Port, LED_G_Pin, 1);
			  while (mode == PRACTICE && song_chosen)
			  {
				  switch (song[i])
				  {
				  case C5: case C4:
					  while (mode == PRACTICE && song_chosen)
					  {
						  HAL_GPIO_WritePin(LED_C_GPIO_Port, LED_C_Pin, 0);
						  if (HAL_GPIO_ReadPin(C_NOTE_GPIO_Port, C_NOTE_Pin) == GPIO_PIN_SET)
						  {
							  __HAL_TIM_SET_AUTORELOAD(&htim2, song[i]);
							  __HAL_TIM_SET_COMPARE(&htim2, TIM_CHANNEL_4, 900);
							  HAL_Delay(200);
							  if (HAL_GPIO_ReadPin(C_NOTE_GPIO_Port, C_NOTE_Pin) == GPIO_PIN_RESET)
							  {
								  HAL_GPIO_WritePin(LED_C_GPIO_Port, LED_C_Pin, 1);
								  break;
							  }
						  }
					  }
					  break;
				  case D5: case D4:
					  while (mode == PRACTICE && song_chosen)
					  {
						  HAL_GPIO_WritePin(LED_D_GPIO_Port, LED_D_Pin, 0);
						  if (HAL_GPIO_ReadPin(D_NOTE_GPIO_Port, D_NOTE_Pin) == GPIO_PIN_SET)
						  {
							  __HAL_TIM_SET_AUTORELOAD(&htim2, song[i]);
							  __HAL_TIM_SET_COMPARE(&htim2, TIM_CHANNEL_4, 900);
							  HAL_Delay(200);
							  if (HAL_GPIO_ReadPin(D_NOTE_GPIO_Port, D_NOTE_Pin) == GPIO_PIN_RESET)
							  {
								  HAL_GPIO_WritePin(D_NOTE_GPIO_Port, D_NOTE_Pin, 1);
								  break;
							  }
						  }
					  }
					  break;
				  case E5: case E4:
					  while (mode == PRACTICE && song_chosen)
					  {
						  HAL_GPIO_WritePin(LED_E_GPIO_Port, LED_E_Pin, 0);
						  if (HAL_GPIO_ReadPin(E_NOTE_GPIO_Port, E_NOTE_Pin) == GPIO_PIN_SET)
						  {
							  __HAL_TIM_SET_AUTORELOAD(&htim2, song[i]);
							  __HAL_TIM_SET_COMPARE(&htim2, TIM_CHANNEL_4, 900);
							  HAL_Delay(200);
							  if (HAL_GPIO_ReadPin(E_NOTE_GPIO_Port, E_NOTE_Pin) == GPIO_PIN_RESET)
							  {
								  HAL_GPIO_WritePin(LED_E_GPIO_Port, LED_E_Pin, 1);
								  break;
							  }
						  }
					  }
					  break;
				  case F5: case F4:
					  while (mode == PRACTICE && song_chosen)
					  {
						  HAL_GPIO_WritePin(LED_F_GPIO_Port, LED_F_Pin, 0);
						  if (HAL_GPIO_ReadPin(F_NOTE_GPIO_Port, F_NOTE_Pin) == GPIO_PIN_SET)
						  {
							  __HAL_TIM_SET_AUTORELOAD(&htim2, song[i]);
							  __HAL_TIM_SET_COMPARE(&htim2, TIM_CHANNEL_4, 900);
							  HAL_Delay(200);
							  if (HAL_GPIO_ReadPin(F_NOTE_GPIO_Port, F_NOTE_Pin) == GPIO_PIN_RESET)
							  {
								  HAL_GPIO_WritePin(LED_F_GPIO_Port, LED_F_Pin, 1);
								  break;
							  }
						  }
					  }
					  break;
				  case G5: case G4:
					  while (mode == PRACTICE && song_chosen)
					  {
						  HAL_GPIO_WritePin(LED_G_GPIO_Port, LED_G_Pin, 0);
						  if (HAL_GPIO_ReadPin(G_NOTE_GPIO_Port, G_NOTE_Pin) == GPIO_PIN_SET)
						  {
							  __HAL_TIM_SET_AUTORELOAD(&htim2, song[i]);
							  __HAL_TIM_SET_COMPARE(&htim2, TIM_CHANNEL_4, 900);
							  HAL_Delay(200);
							  if (HAL_GPIO_ReadPin(G_NOTE_GPIO_Port, G_NOTE_Pin) == GPIO_PIN_RESET)
							  {
								  HAL_GPIO_WritePin(LED_G_GPIO_Port, LED_G_Pin, 1);
								  break;
							  }
						  }
					  }
					  break;
				  case A5: case A4:
					  while (mode == PRACTICE && song_chosen)
					  {
						  HAL_GPIO_WritePin(LED_A_GPIO_Port, LED_A_Pin, 0);
						  if (HAL_GPIO_ReadPin(A_NOTE_GPIO_Port, A_NOTE_Pin) == GPIO_PIN_SET)
						  {
							  __HAL_TIM_SET_AUTORELOAD(&htim2, song[i]);
							  __HAL_TIM_SET_COMPARE(&htim2, TIM_CHANNEL_4, 900);
							  HAL_Delay(200);
							  if (HAL_GPIO_ReadPin(A_NOTE_GPIO_Port, A_NOTE_Pin) == GPIO_PIN_RESET)
							  {
								  HAL_GPIO_WritePin(LED_A_GPIO_Port, LED_A_Pin, 1);
								  break;
							  }
						  }
					  }
					  break;
				  case B5: case B4:
					  while (mode == PRACTICE && song_chosen)
					  {
						  HAL_GPIO_WritePin(LED_B_GPIO_Port, LED_B_Pin, 0);
						  if (HAL_GPIO_ReadPin(B_NOTE_GPIO_Port, B_NOTE_Pin) == GPIO_PIN_SET)
						  {
							  __HAL_TIM_SET_AUTORELOAD(&htim2, song[i]);
							  __HAL_TIM_SET_COMPARE(&htim2, TIM_CHANNEL_4, 900);
							  HAL_Delay(200);
							  if (HAL_GPIO_ReadPin(B_NOTE_GPIO_Port, B_NOTE_Pin) == GPIO_PIN_RESET)
							  {
								  HAL_GPIO_WritePin(LED_B_GPIO_Port, LED_B_Pin, 1);
								  break;
							  }
						  }
					  }
					  break;
				  }
			  __HAL_TIM_SET_COMPARE(&htim2, TIM_CHANNEL_4, 0);
			  HAL_Delay(20);
			  break;
			  }
		  }
		  song_chosen = false;
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
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_ON;
  RCC_OscInitStruct.HSEPredivValue = RCC_HSE_PREDIV_DIV1;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
  RCC_OscInitStruct.PLL.PLLMUL = RCC_PLL_MUL8;
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
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV2;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_2) != HAL_OK)
  {
    Error_Handler();
  }
}

/* USER CODE BEGIN 4 */
void update_octave(octave_t *octave, uint8_t n)
{
	switch (n)
	{
	case 4:
		octave->C = C4;
		octave->D = D4;
		octave->E = E4;
		octave->F = F4;
		octave->G = G4;
		octave->A = A4;
		octave->B = B4;
		break;
	case 5:
		octave->C = C5;
		octave->D = D5;
		octave->E = E5;
		octave->F = F5;
		octave->G = G5;
		octave->A = A5;
		octave->B = B5;
		break;
	case 6:
		octave->C = C6;
		octave->D = D6;
		octave->E = E6;
		octave->F = F6;
		octave->G = G6;
		octave->A = A6;
		octave->B = B6;
		break;
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
     tex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
