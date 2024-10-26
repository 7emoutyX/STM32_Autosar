/*
 * Main code
 * test version for DIO port
 * DaoudiMohammed
 */



#include "main.h"
#include "dio.h"

ADC_HandleTypeDef hadc1;
UART_HandleTypeDef huart1;
PCD_HandleTypeDef hpcd_USB_FS;

void SystemClock_Config(void);
void PeriphCommonClock_Config(void);

static void MX_GPIO_Init(void);
static void MX_USART1_UART_Init(void);
static void MX_USB_PCD_Init(void);
static void MX_ADC1_Init(void);

#define AUTOSAR_MODE
// #define CUBEMX_MODE

#ifdef AUTOSAR_MODE
/* ===================================================================================== */
// Configuration dyal buttons and leds
Dio_ConfigType buttonConfig = {GPIOC, B1_Pin, DIO_PIN_MODE_INPUT}; // Button on GPIOD, B2 pin
Dio_ConfigType buttonConfig2 = {GPIOD, B2_Pin, DIO_PIN_MODE_INPUT}; // Button on GPIOD, B2 pin
Dio_ConfigType buttonConfig3 = {GPIOD, B3_Pin, DIO_PIN_MODE_INPUT}; // Button on GPIOD, B2 pin

Dio_ConfigType ledConfig = {GPIOB, LD1_Pin, DIO_PIN_MODE_OUTPUT};   // LED on GPIOB, LD1 pin
Dio_ConfigType ledConfig2 = {GPIOB, LD2_Pin, DIO_PIN_MODE_OUTPUT};   // LED on GPIOB, LD1 pin
Dio_ConfigType ledConfig3 = {GPIOB, LD3_Pin, DIO_PIN_MODE_OUTPUT};   // LED on GPIOB, LD1 pin
/* ===================================================================================== */
#endif

int main(void) {
    HAL_Init();
    SystemClock_Config();
    PeriphCommonClock_Config();
   // MX_GPIO_Init();
    MX_USART1_UART_Init();
    MX_USB_PCD_Init();
  //  MX_ADC1_Init();

    //initialisation dyal Buttons and leds instead of MX_GPIO_init()
    /* ===================================================================================== */
    Dio_Init(&buttonConfig);
    Dio_Init(&buttonConfig2);
    Dio_Init(&buttonConfig3);
    Dio_Init(&ledConfig);
    Dio_Init(&ledConfig2);
    Dio_Init(&ledConfig3);
    /* ===================================================================================== */


    while (1) {

    	 if (Dio_ReadChannel(&buttonConfig) == STD_LOW) {
    	            HAL_Delay(50);
    	            while (Dio_ReadChannel(&buttonConfig) == STD_LOW);
    	            HAL_Delay(50);

    	            static Dio_LevelType ledState = STD_LOW;
    	            ledState = (ledState == STD_LOW) ? STD_HIGH : STD_LOW;
    	            Dio_WriteChannel(&ledConfig, ledState);
    	        }
    	 if (Dio_ReadChannel(&buttonConfig2) == STD_LOW) {
    	    	            HAL_Delay(50);
    	    	            while (Dio_ReadChannel(&buttonConfig2) == STD_LOW);
    	    	            HAL_Delay(50);

    	    	            static Dio_LevelType ledState2 = STD_LOW;
    	    	            ledState2 = (ledState2 == STD_LOW) ? STD_HIGH : STD_LOW;
    	    	            Dio_WriteChannel(&ledConfig2, ledState2);
    	    	        }
    	 if (Dio_ReadChannel(&buttonConfig3) == STD_LOW) {
    	    	            HAL_Delay(50);
    	    	            while (Dio_ReadChannel(&buttonConfig3) == STD_LOW);
    	    	            HAL_Delay(50);

    	    	            static Dio_LevelType ledState3 = STD_LOW;
    	    	            ledState3 = (ledState3 == STD_LOW) ? STD_HIGH : STD_LOW;
    	    	            Dio_WriteChannel(&ledConfig3, ledState3);
    	    	        }

    }
}

void SystemClock_Config(void) {
    RCC_OscInitTypeDef RCC_OscInitStruct = {0};
    RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

    __HAL_RCC_PLL_PLLM_CONFIG(RCC_PLLM_DIV1);
    __HAL_RCC_PLL_PLLSOURCE_CONFIG(RCC_PLLSOURCE_MSI);
    HAL_PWR_EnableBkUpAccess();
    __HAL_RCC_LSEDRIVE_CONFIG(RCC_LSEDRIVE_LOW);
    __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE1);

    RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI | RCC_OSCILLATORTYPE_HSE | RCC_OSCILLATORTYPE_LSE | RCC_OSCILLATORTYPE_MSI;
    RCC_OscInitStruct.HSEState = RCC_HSE_ON;
    RCC_OscInitStruct.LSEState = RCC_LSE_ON;
    RCC_OscInitStruct.HSIState = RCC_HSI_ON;
    RCC_OscInitStruct.MSIState = RCC_MSI_ON;
    RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
    RCC_OscInitStruct.MSICalibrationValue = RCC_MSICALIBRATION_DEFAULT;
    RCC_OscInitStruct.MSIClockRange = RCC_MSIRANGE_6;
    RCC_OscInitStruct.PLL.PLLState = RCC_PLL_NONE;
    if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK) {
        Error_Handler();
    }

    RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK4 | RCC_CLOCKTYPE_HCLK2 | RCC_CLOCKTYPE_HCLK | RCC_CLOCKTYPE_SYSCLK | RCC_CLOCKTYPE_PCLK1 | RCC_CLOCKTYPE_PCLK2;
    RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_HSE;
    RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
    RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;
    RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;
    RCC_ClkInitStruct.AHBCLK2Divider = RCC_SYSCLK_DIV1;
    RCC_ClkInitStruct.AHBCLK4Divider = RCC_SYSCLK_DIV1;

    if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_1) != HAL_OK) {
        Error_Handler();
    }

    HAL_RCCEx_EnableMSIPLLMode();
}

void PeriphCommonClock_Config(void) {
    RCC_PeriphCLKInitTypeDef PeriphClkInitStruct = {0};

    PeriphClkInitStruct.PeriphClockSelection = RCC_PERIPHCLK_SMPS | RCC_PERIPHCLK_USB | RCC_PERIPHCLK_ADC;
    PeriphClkInitStruct.PLLSAI1.PLLN = 24;
    PeriphClkInitStruct.PLLSAI1.PLLP = RCC_PLLP_DIV2;
    PeriphClkInitStruct.PLLSAI1.PLLQ = RCC_PLLQ_DIV2;
    PeriphClkInitStruct.PLLSAI1.PLLR = RCC_PLLR_DIV2;
    PeriphClkInitStruct.PLLSAI1.PLLSAI1ClockOut = RCC_PLLSAI1_USBCLK | RCC_PLLSAI1_ADCCLK;
    PeriphClkInitStruct.UsbClockSelection = RCC_USBCLKSOURCE_PLLSAI1;
    PeriphClkInitStruct.AdcClockSelection = RCC_ADCCLKSOURCE_PLLSAI1;
    PeriphClkInitStruct.SmpsClockSelection = RCC_SMPSCLKSOURCE_HSI;
    PeriphClkInitStruct.SmpsDivSelection = RCC_SMPSCLKDIV_RANGE0;

    if (HAL_RCCEx_PeriphCLKConfig(&PeriphClkInitStruct) != HAL_OK) {
        Error_Handler();
    }
}
#ifdef CUBEMX_MODE

static void MX_ADC1_Init(void) {
    ADC_ChannelConfTypeDef sConfig = {0};

    hadc1.Instance = ADC1;
    hadc1.Init.ClockPrescaler = ADC_CLOCK_ASYNC_DIV1;
    hadc1.Init.Resolution = ADC_RESOLUTION_12B;
    hadc1.Init.DataAlign = ADC_DATAALIGN_RIGHT;
    hadc1.Init.ScanConvMode = ADC_SCAN_DISABLE;
    hadc1.Init.EOCSelection = ADC_EOC_SINGLE_CONV;
    hadc1.Init.LowPowerAutoWait = DISABLE;
    hadc1.Init.ContinuousConvMode = DISABLE;
    hadc1.Init.NbrOfConversion = 1;
    hadc1.Init.DiscontinuousConvMode = DISABLE;
    hadc1.Init.ExternalTrigConv = ADC_SOFTWARE_START;
    hadc1.Init.ExternalTrigConvEdge = ADC_EXTERNALTRIGCONVEDGE_NONE;
    hadc1.Init.DMAContinuousRequests = DISABLE;
    hadc1.Init.Overrun = ADC_OVR_DATA_PRESERVED;
    hadc1.Init.OversamplingMode = DISABLE;
    if (HAL_ADC_Init(&hadc1) != HAL_OK) {
        Error_Handler();
    }

    sConfig.Channel = ADC_CHANNEL_1;
    sConfig.Rank = ADC_REGULAR_RANK_1;
    sConfig.SamplingTime = ADC_SAMPLETIME_2CYCLES_5;
    sConfig.SingleDiff = ADC_DIFFERENTIAL_ENDED;
    sConfig.OffsetNumber = ADC_OFFSET_NONE;
    sConfig.Offset = 0;
    if (HAL_ADC_ConfigChannel(&hadc1, &sConfig) != HAL_OK) {
        Error_Handler();
    }
}
#endif

static void MX_USART1_UART_Init(void) {
    huart1.Instance = USART1;
    huart1.Init.BaudRate = 115200;
    huart1.Init.WordLength = UART_WORDLENGTH_8B; // Set to 8B if 7B is not intentional
    huart1.Init.StopBits = UART_STOPBITS_1;
    huart1.Init.Parity = UART_PARITY_NONE;
    huart1.Init.Mode = UART_MODE_TX_RX;
    huart1.Init.HwFlowCtl = UART_HWCONTROL_NONE;
    huart1.Init.OverSampling = UART_OVERSAMPLING_16;
    huart1.Init.OneBitSampling = UART_ONE_BIT_SAMPLE_DISABLE;
    huart1.Init.ClockPrescaler = UART_PRESCALER_DIV1;
    huart1.AdvancedInit.AdvFeatureInit = UART_ADVFEATURE_NO_INIT;
    if (HAL_UART_Init(&huart1) != HAL_OK) {
        Error_Handler();
    }
}

static void MX_USB_PCD_Init(void) {
    hpcd_USB_FS.Instance = USB;
    hpcd_USB_FS.Init.dev_endpoints = 8;
    hpcd_USB_FS.Init.speed = PCD_SPEED_FULL;
    hpcd_USB_FS.Init.phy_itface = PCD_PHY_EMBEDDED;
    hpcd_USB_FS.Init.Sof_enable = DISABLE;
    hpcd_USB_FS.Init.low_power_enable = DISABLE;
    hpcd_USB_FS.Init.lpm_enable = DISABLE;
    hpcd_USB_FS.Init.battery_charging_enable = DISABLE;
    if (HAL_PCD_Init(&hpcd_USB_FS) != HAL_OK) {
        Error_Handler();
    }
}

#ifdef CUBEMX_MODE
static void MX_GPIO_Init(void) {
	  GPIO_InitTypeDef GPIO_InitStruct = {0};
	  __HAL_RCC_GPIOC_CLK_ENABLE();
	  __HAL_RCC_GPIOB_CLK_ENABLE();
	  __HAL_RCC_GPIOA_CLK_ENABLE();
	  __HAL_RCC_GPIOD_CLK_ENABLE();

	  /*Configure GPIO pin Output Level */
	  HAL_GPIO_WritePin(GPIOB, LD2_Pin|LD3_Pin|LD1_Pin, GPIO_PIN_RESET);

	  /*Configure GPIO pin : B1_Pin */
	  GPIO_InitStruct.Pin = B1_Pin;
	  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
	  GPIO_InitStruct.Pull = GPIO_PULLUP  ;
	  HAL_GPIO_Init(B1_GPIO_Port, &GPIO_InitStruct);

	  /*Configure GPIO pins : LD2_Pin LD3_Pin LD1_Pin */
	  GPIO_InitStruct.Pin = LD2_Pin|LD3_Pin|LD1_Pin;
	  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
	  GPIO_InitStruct.Pull = GPIO_NOPULL;
	  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
	  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

	  /*Configure GPIO pins : B2_Pin B3_Pin */
	  GPIO_InitStruct.Pin = B2_Pin|B3_Pin;
	  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
	  GPIO_InitStruct.Pull = GPIO_PULLUP;
	  HAL_GPIO_Init(GPIOD, &GPIO_InitStruct);

}
#endif


void Error_Handler(void) {
    __disable_irq();
    while (1) {
    }
}
