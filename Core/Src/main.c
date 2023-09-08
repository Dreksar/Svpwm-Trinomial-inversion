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
#include "adc.h"
#include "dma.h"
#include "tim.h"
#include "gpio.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "cleck.h"
#include "Svpwm.h"
#include "Ave_Sam.h"
#include "Park.h"
#include "math.h"
#include "PLL.h"
#include "arm_math.h"
#include "Smping.h"
#include "Ave_FL.h"

/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */
CLECK Cleck,Cleck_1;
PARK  Park;
AD_Detc AD_detc;

float U_spwm,V_spwm,W_spwm,A_spwm,B_spwm,C_spwm;
float Sin_A,Sin_B,Sin_C;

float Udetc_f,Vdetc_f,Wdetc_f,U_phase,V_phase,U_phase,V_phase,W_phase,Un=1.f,Vn=1.f,Wn=1.f,U_data,V_data,W_data,U_Sin,V_Sin,W_Sin,UL;
float Theta1,sin_data,cos_data;
float Vdc=12.f;
float Um=8.f;
float Out;
uint16_t time_count;
float sumU,sumV,sumW;
float U_ref,V_ref,W_ref;

float Omega=0.f;
float Uk;
uint16_t Flag=0;

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */
/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/

/* USER CODE BEGIN PV */

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
  MX_ADC1_Init();
  MX_TIM1_Init();
  MX_TIM2_Init();
  MX_TIM3_Init();
  /* USER CODE BEGIN 2 */
	HAL_TIM_Base_Start_IT(&htim2);
	HAL_TIM_Base_Start_IT(&htim3);
	HAL_TIM_Base_Start_IT(&htim1);
	HAL_TIM_PWM_Start(&htim1,TIM_CHANNEL_1);
	HAL_TIM_PWM_Start(&htim1,TIM_CHANNEL_2);
	HAL_TIM_PWM_Start(&htim1,TIM_CHANNEL_3);
	
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

  /** Configure the main internal regulator output voltage
  */
  __HAL_RCC_PWR_CLK_ENABLE();
  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE1);

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_ON;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
  RCC_OscInitStruct.PLL.PLLM = 4;
  RCC_OscInitStruct.PLL.PLLN = 168;
  RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV2;
  RCC_OscInitStruct.PLL.PLLQ = 4;
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
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV4;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV2;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_5) != HAL_OK)
  {
    Error_Handler();
  }
}

/* USER CODE BEGIN 4 */

void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{

	if(htim==&htim3)
	{
		Sin_Start(10000,5,12);


		Get_ADC(&AD_detc);
		Get_Real(&AD_detc);
//		U_ref=Ave_Sam_u(Udetc_f,20);
//		V_ref=Ave_Sam_i(Vdetc_f,20);
//		W_ref=Ave_Sam_w(Wdetc_f,20);

//		///////////////////对AD_Buf取平均
//		U_data=(U_ref-1.654f)/0.0202f;
//    V_data=(V_ref-1.654f)/0.0202f;
//		W_data=(W_ref-1.654f)/0.0202f;
		
		
		
		time_count++;
		sumU+=U_data*U_data;		
		sumV+=V_data*V_data;	
		sumW+=W_data*W_data;	
		if(time_count==200)
			{		
				time_count=0;				
				Un=sqrt(sumU*0.005f);//
				sumU=0.f;//
				Vn=sqrt(sumV*0.005f);//
				sumV=0.f;//
				Wn=sqrt(sumW*0.005f);//
				sumW=0.f;//
			}
		Out=sqrt_3*Um/Vdc;
		
		
		U_phase=Out*U_data/sqrt_2/Un;
		V_phase=Out*V_data/sqrt_2/Vn;
    W_phase=Out*W_data/sqrt_2/Wn;	//在第一次时将Wn定义为1否则inf	

		if(Flag==1)
		{
			HAL_GPIO_WritePin(GPIOE,GPIO_PIN_0,GPIO_PIN_SET);
			HAL_GPIO_WritePin(GPIOE,GPIO_PIN_5,GPIO_PIN_SET);
			HAL_GPIO_WritePin(GPIOE,GPIO_PIN_6,GPIO_PIN_SET);
		}
		if(Flag==0)
		{
			HAL_GPIO_WritePin(GPIOE,GPIO_PIN_0,GPIO_PIN_RESET);
			HAL_GPIO_WritePin(GPIOE,GPIO_PIN_5,GPIO_PIN_RESET);
			HAL_GPIO_WritePin(GPIOE,GPIO_PIN_6,GPIO_PIN_RESET);
		}
		
	}
		if(htim==&htim2)
	{

    cos_data=(U_phase-0.5f*V_phase-0.5f*W_phase)*2.f/3.f;
    sin_data=(0.8660254f*V_phase-0.8660254f*W_phase)*2.f/3.f;
    Uk=sqrt(cos_data*cos_data+sin_data*sin_data);
			if(sin_data>0&&cos_data>0)
		{
			Theta1=atanf(sin_data/cos_data);
		}
		if(sin_data<0&& cos_data>0)
		{
			Theta1=atanf(sin_data/cos_data);
		}
		if(sin_data>0 && cos_data<0)
		{
			Theta1=  PI - atanf((sin_data)/(-cos_data));
		}
		if(sin_data<0 && cos_data<0)
		{
			Theta1=PI + atanf((-sin_data)/(-cos_data));
		}
		


		
		Cleck_1.Valpha=Uk*cosf(Theta1+Omega/360.f*2.f*PI);//0.35
  	Cleck_1.Vbeta=Uk*sinf(Theta1+Omega/360.f*2.f*PI);
//		Svpwm(&Cleck_1,U_phase,V_phase,W_phase);
		TIM1->CCR1=U_spwm-320.f;
		TIM1->CCR2=W_spwm;
		TIM1->CCR3=V_spwm;	

 
////		Cleck.Ialpha=(Sin_A-0.5f*Sin_B-0.5f*Sin_C)*2/3;
////  	Cleck.Ibeta=(0.8660254f*Sin_B-0.8660254f*Sin_C)*2/3;
////		Park.Id=Cleck.Ialpha*Cleck.Valpha+Cleck.Ibeta*Cleck.Vbeta;
////		Park.Iq=-Cleck.Ialpha*Cleck.Vbeta+Cleck.Ibeta*Cleck.Valpha;



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
