/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  * @Author 		: George
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2020 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under BSD 3-Clause license,
  * the "Licens.0e"; You may not use this file except in compliance with the
  * License. You may obtain a copy of the License at:
  *                        opensource.org/licenses/BSD-3-Clause
  *
  ******************************************************************************
  */
/* USER CODE END Header */
/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "cmsis_os.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "Delay.h"
#include "Calculate_statistic.h"
#include "arm_const_structs.h"
#include "arm_math.h"
#include "ADS1256.h"
#include "BLE_USART.h"

/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */
#define FFT_LENGTH_SAMPLES 8192
/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */
//IIC EEPROM
#define ADDR_24LCxx_Write 0xA0
#define ADDR_24LCxx_Read 0xA1
#define BufferSize 0x100

/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/

I2C_HandleTypeDef hi2c2;

IWDG_HandleTypeDef hiwdg;

SPI_HandleTypeDef hspi1;
DMA_HandleTypeDef hdma_spi1_rx;
DMA_HandleTypeDef hdma_spi1_tx;

UART_HandleTypeDef huart6;
DMA_HandleTypeDef hdma_usart6_tx;

osThreadId ADC_TaskHandle;
osThreadId FFT_TaskHandle;
osMessageQId adcQueueHandle;
osSemaphoreId adcBinarySemHandle;
osSemaphoreId I2cBinarySemHandle;
/* USER CODE BEGIN PV */
/*
 * I2C private value
 * */
uint8_t aRxBuffer[1];
struct I2cCommunication
{
	uint8_t i2cRecive;
	uint8_t i2cSend;
} I2cC;

/*2021/0203/George
 *TODO: Define STM32 Studio charting value
 *TODO: Parameter:
 *TODO: id is ADS1256 register ID
 *TODO: data is used for STMStudio debug using
 *TODO: read is covert to float data buffer
 * */
uint8_t id=0;
float data;
int32_t read = 0;


/* 2021/0203/George
 * TODO: For FFT_Thread Bluetooth transmit
 * using moving average while variable times is 3
 * Parameter: : averageTimes
 * */
uint8_t averageTimes = 0;


/* 2021/0203/George
 * TODO: Define send to ADC message
 * TODO: ADS1256 command
 * Parameter:
 * TODO: RDATACsend_data is send to ADS1256
 * TODO: Databuffer is retrieve data from ADS1256
 * TODO: RDATACcmdbuffer is send to ADS1256 enable continue mode
 * TODO: SDATACcmduffer is send to ADS1256 disable continue mode
 * */
uint8_t RDATACsend_data[3] = {0xff,0xff,0xff};
uint8_t Databuffer[3] = {0x00,0x00,0x00};
uint8_t RDATACcmdbuffer[1] = {CMD_RDATAC};
uint8_t SDATACcmduffer[1] = {CMD_SDATAC};



/* 2021/0203/George //2021/02/18/George Addpara samplingRate
 * TODO: FFT using
 * Parameter:
 * TODO: samplingRate is ADS1256 sampling rate
 * TODO: fftSize is fft size
 * TODO: ifftFlag is fft forward when ifftFlag is 0, ifftFlag is fft inverse when ifftFlag is 1.
 * TODO: doBitReverse is bitReverseFlag flag that enables (bitReverseFlag=1) or disables (bitReverseFlag=0) bit reversal of output.
 * TODO: FFTMaxValueIndex is fft max value index
 * TODO: FFTmaxValue is calculate fft max value
 * TODO: p* statisticDataSet is point to rawData
 * TODO: maxtestIndex calculate time-domain max index
 * TODO: mintestIndex calculate time-domain min index
 * TODO: dataLength is fft data length
 * */
uint32_t samplingRate = 15000;
uint32_t fftSize = 4096;
uint32_t ifftFlag = 0;
uint32_t doBitReverse = 1;
uint32_t FFTMaxValueIndex = 0;
float32_t FFTmaxValue;
float32_t *statisticDataSet;
uint32_t maxtestIndex = 0;
uint32_t mintestIndex = 0;
uint32_t dataLength = 0;


//2021/0203/George
//TODO: FFT set band
FreqMaxMin * settingValue = 0;



//TODO: IIC EEPROM 2402C
uint8_t WriteBufferEEPROM[BufferSize],ReadBufferEEPROM[BufferSize];
uint8_t WriteIICEEPROM[1];

//TODO: BLE 080i
USART_BLE USARTBLE;
/*
 * TODO:Define Statistic function
 */
extern Sv statistic_value;
/* FreeRTOS private variables;*/
UBaseType_t queueCount;
/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_DMA_Init(void);
static void MX_SPI1_Init(void);
static void MX_USART6_UART_Init(void);
static void MX_I2C2_Init(void);
static void MX_IWDG_Init(void);
void ADC_Thread(void const * argument);
void FFT_Thread(void const * argument);

/* USER CODE BEGIN PFP */


//IIC EEPROM function
void readIICEEPROM_2402C(void);
void writeIICEEPROM_2402C(uint8_t *data);

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */


/*=============================================================================================================
 * TODO: IIC Function
 *
 *
 * */
void readIICEEPROM_2402C(void)
{
	  HAL_I2C_Mem_Read(&hi2c2, ADDR_24LCxx_Read, 0, I2C_MEMADD_SIZE_16BIT,ReadBufferEEPROM,BufferSize, 1000);
}
void writeIICEEPROM_2402C(uint8_t *data)
{
		if(HAL_I2C_Mem_Write(&hi2c2, ADDR_24LCxx_Write, 0, I2C_MEMADD_SIZE_16BIT, data,1, 0xff) == HAL_OK)
		{
			TM_DelayMicros(5000);
		}
		else
		{
			TM_DelayMicros(5000);
		}
}

//2021/02/01

//TODO: extern float32_t testInput_f32_10khz[TEST_LENGTH_SAMPLES];
float32_t FFTRawData[FFT_LENGTH_SAMPLES/2];
float *dataRecive[4096];
float *xdatatoSend = ADS1256.data_buffer;
float FFTdata[8192];


float speedans = 0;



//2021/0201/George
//TODO: FFT Task Flag
uint8_t stattisComputingStatus = 0;

enum statisticComputingFlag
{
	statisticComputingNORMAL = 0,
	statisticComputingBUSY = 1,
}statisticComputingFlag;


//2021/0201/George
//TODO: InitialParameter
void initialBootloaderParameter()
{
	USARTBLE.RxCount=0;
	HAL_UART_Receive_IT(&huart6, (uint8_t *)aRxBuffer, 1);
	__enable_irq();
}

//2021/0201/George
//TODO : Initialize ADS1256 data buffer size
void initialADS1256DataBuffer()
{

	  dataLength = sizeof(dataRecive)/sizeof(float);
	  ADS1256.data_index = 0;
	  ADS1256.data_length = dataLength;
}

//2021/0202/George
//TODO: Set freq band
void InitialSetFreqStatisticBand()
{
	//2021/0204/George
	//TODO:Total 3 setting frequency broadband parameter
	freqSettingValueList.range1.Max = 700;
	freqSettingValueList.range1.Min = 500;
	freqSettingValueList.range2.Max = 1000;
	freqSettingValueList.range2.Min = 10;
	freqSettingValueList.range3.Max = 5000;
	freqSettingValueList.range3.Min = 1000;
}

//2021/0202/George
//TODO: Initialize delay systick
void InitialDelayFunction()
{
	   delay_init(216);
	   TM_Delay_Init();
}

//2021/0202/George
//TODO: Initialize ADS1256 parameter
void InitialADS1256Register()
{
	//TODO: Reset ADS1256
	   writeCMD(CMD_RESET);
	   delay_ms(10);
	   TM_DelayMicros(1);

	   //TODO: Initialize ADS1256 parameter (Buffer, PGA, Sampling rate)
	   setBuffer();
	   setPGA(PGA_GAIN1);
	   setDataRate(DRATE_15000);

	   //TODO: Read chip id
	   id = readChipID();

	   delay_ms(500);// wait for initialization

	   uint8_t  posChannels [4] = {AIN0, AIN2, AIN4, AIN6};
	   uint8_t  negChannels [4] = {AIN1, AIN3, AIN5, AIN7};

	   //TODO: Set differential analog input channel.
	   setDIFFChannel(posChannels[0], negChannels[0]);
	   delay_us(15);
	   writeCMD(CMD_SYNC);    // SYNC command
	   delay_us(10);
	   writeCMD(CMD_WAKEUP);  // WAKEUP command
	   delay_us(15); // min delay: t11 = 4 * 1 / 7,68 Mhz = 0,52 micro sec



	   //TODO: Set continuous mode.

		waitDRDY();
		CS_0();
		HAL_SPI_Transmit(&hspi1, RDATACcmdbuffer ,1,50);
		delay_ms(25); // min delay: t6 = 50 * 1/7.68 MHz = 6.5 microseconds
		ADS1256.data_startFlag = 1;
		delay_us(1);

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
  MX_DMA_Init();
  MX_SPI1_Init();
  MX_USART6_UART_Init();
  MX_I2C2_Init();
  MX_IWDG_Init();
  /* USER CODE BEGIN 2 */
  //2021/0319/George/HTi
  //TODO:PB6 for IEPE output
  HAL_GPIO_WritePin(GPIOB, GPIO_PIN_6, GPIO_PIN_SET);

  //2021/0201/George
  //TODO: InitialParameter
  initialBootloaderParameter();
  initialADS1256DataBuffer();

   //2021/0201/George
   //TODO: Initialize Frequency range to collection to feature
   InitialSetFreqStatisticBand();

   //2021/0202/George
   //TODO: Initialize delay systick
   InitialDelayFunction();

   //2021/0202/George
   //TODO: Testing EEProm
   readIICEEPROM_2402C();

   //2021/0202/George
   //TODO: Initialize ADS1256 parameter
   InitialADS1256Register();
  /* USER CODE END 2 */

  /* USER CODE BEGIN RTOS_MUTEX */
  /* add mutexes, ... */
  /* USER CODE END RTOS_MUTEX */

  /* Create the semaphores(s) */
  /* definition and creation of adcBinarySem */
  osSemaphoreDef(adcBinarySem);
  adcBinarySemHandle = osSemaphoreCreate(osSemaphore(adcBinarySem), 1);

  /* definition and creation of I2cBinarySem */
  osSemaphoreDef(I2cBinarySem);
  I2cBinarySemHandle = osSemaphoreCreate(osSemaphore(I2cBinarySem), 1);

  /* USER CODE BEGIN RTOS_SEMAPHORES */
  /* add semaphores, ... */
  /* USER CODE END RTOS_SEMAPHORES */

  /* USER CODE BEGIN RTOS_TIMERS */
  /* start timers, add new ones, ... */
  /* USER CODE END RTOS_TIMERS */

  /* Create the queue(s) */
  /* definition and creation of adcQueue */
  osMessageQDef(adcQueue, 16, long);
  adcQueueHandle = osMessageCreate(osMessageQ(adcQueue), NULL);

  /* USER CODE BEGIN RTOS_QUEUES */
  /* add queues, ... */
  /* USER CODE END RTOS_QUEUES */

  /* Create the thread(s) */
  /* definition and creation of ADC_Task */
  osThreadDef(ADC_Task, ADC_Thread, osPriorityRealtime, 0, 200);
  ADC_TaskHandle = osThreadCreate(osThread(ADC_Task), NULL);

  /* definition and creation of FFT_Task */
  osThreadDef(FFT_Task, FFT_Thread, osPriorityHigh, 0, 400);
  FFT_TaskHandle = osThreadCreate(osThread(FFT_Task), NULL);

  /* USER CODE BEGIN RTOS_THREADS */
  /* add threads, ... */
  /* USER CODE END RTOS_THREADS */

  /* Start scheduler */
  osKernelStart();

  /* We should never get here as control is now taken by the scheduler */
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
  RCC_PeriphCLKInitTypeDef PeriphClkInitStruct = {0};

  /** Configure the main internal regulator output voltage
  */
  __HAL_RCC_PWR_CLK_ENABLE();
  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE1);
  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI|RCC_OSCILLATORTYPE_LSI;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
  RCC_OscInitStruct.LSIState = RCC_LSI_ON;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSI;
  RCC_OscInitStruct.PLL.PLLM = 8;
  RCC_OscInitStruct.PLL.PLLN = 216;
  RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV2;
  RCC_OscInitStruct.PLL.PLLQ = 2;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }
  /** Activate the Over-Drive mode
  */
  if (HAL_PWREx_EnableOverDrive() != HAL_OK)
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

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_7) != HAL_OK)
  {
    Error_Handler();
  }
  PeriphClkInitStruct.PeriphClockSelection = RCC_PERIPHCLK_USART6|RCC_PERIPHCLK_I2C2;
  PeriphClkInitStruct.Usart6ClockSelection = RCC_USART6CLKSOURCE_PCLK2;
  PeriphClkInitStruct.I2c2ClockSelection = RCC_I2C2CLKSOURCE_PCLK1;
  if (HAL_RCCEx_PeriphCLKConfig(&PeriphClkInitStruct) != HAL_OK)
  {
    Error_Handler();
  }
}

/**
  * @brief I2C2 Initialization Function
  * @param None
  * @retval None
  */
static void MX_I2C2_Init(void)
{

  /* USER CODE BEGIN I2C2_Init 0 */

  /* USER CODE END I2C2_Init 0 */

  /* USER CODE BEGIN I2C2_Init 1 */

  /* USER CODE END I2C2_Init 1 */
  hi2c2.Instance = I2C2;
  hi2c2.Init.Timing = 0x20404768;
  hi2c2.Init.OwnAddress1 = 8;
  hi2c2.Init.AddressingMode = I2C_ADDRESSINGMODE_7BIT;
  hi2c2.Init.DualAddressMode = I2C_DUALADDRESS_DISABLE;
  hi2c2.Init.OwnAddress2 = 0;
  hi2c2.Init.OwnAddress2Masks = I2C_OA2_NOMASK;
  hi2c2.Init.GeneralCallMode = I2C_GENERALCALL_ENABLE;
  hi2c2.Init.NoStretchMode = I2C_NOSTRETCH_DISABLE;
  if (HAL_I2C_Init(&hi2c2) != HAL_OK)
  {
    Error_Handler();
  }
  /** Configure Analogue filter
  */
  if (HAL_I2CEx_ConfigAnalogFilter(&hi2c2, I2C_ANALOGFILTER_ENABLE) != HAL_OK)
  {
    Error_Handler();
  }
  /** Configure Digital filter
  */
  if (HAL_I2CEx_ConfigDigitalFilter(&hi2c2, 0) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN I2C2_Init 2 */

  /* USER CODE END I2C2_Init 2 */

}

/**
  * @brief IWDG Initialization Function
  * @param None
  * @retval None
  */
static void MX_IWDG_Init(void)
{

  /* USER CODE BEGIN IWDG_Init 0 */

  /* USER CODE END IWDG_Init 0 */

  /* USER CODE BEGIN IWDG_Init 1 */

  /* USER CODE END IWDG_Init 1 */
  hiwdg.Instance = IWDG;
  hiwdg.Init.Prescaler = IWDG_PRESCALER_128;
  hiwdg.Init.Window = 4095;
  hiwdg.Init.Reload = 3096;
  if (HAL_IWDG_Init(&hiwdg) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN IWDG_Init 2 */

  /* USER CODE END IWDG_Init 2 */

}

/**
  * @brief SPI1 Initialization Function
  * @param None
  * @retval None
  */
static void MX_SPI1_Init(void)
{

  /* USER CODE BEGIN SPI1_Init 0 */

  /* USER CODE END SPI1_Init 0 */

  /* USER CODE BEGIN SPI1_Init 1 */

  /* USER CODE END SPI1_Init 1 */
  /* SPI1 parameter configuration*/
  hspi1.Instance = SPI1;
  hspi1.Init.Mode = SPI_MODE_MASTER;
  hspi1.Init.Direction = SPI_DIRECTION_2LINES;
  hspi1.Init.DataSize = SPI_DATASIZE_8BIT;
  hspi1.Init.CLKPolarity = SPI_POLARITY_LOW;
  hspi1.Init.CLKPhase = SPI_PHASE_2EDGE;
  hspi1.Init.NSS = SPI_NSS_SOFT;
  hspi1.Init.BaudRatePrescaler = SPI_BAUDRATEPRESCALER_64;
  hspi1.Init.FirstBit = SPI_FIRSTBIT_MSB;
  hspi1.Init.TIMode = SPI_TIMODE_DISABLE;
  hspi1.Init.CRCCalculation = SPI_CRCCALCULATION_DISABLE;
  hspi1.Init.CRCPolynomial = 7;
  hspi1.Init.CRCLength = SPI_CRC_LENGTH_DATASIZE;
  hspi1.Init.NSSPMode = SPI_NSS_PULSE_DISABLE;
  if (HAL_SPI_Init(&hspi1) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN SPI1_Init 2 */

  /* USER CODE END SPI1_Init 2 */

}

/**
  * @brief USART6 Initialization Function
  * @param None
  * @retval None
  */
static void MX_USART6_UART_Init(void)
{

  /* USER CODE BEGIN USART6_Init 0 */

  /* USER CODE END USART6_Init 0 */

  /* USER CODE BEGIN USART6_Init 1 */

  /* USER CODE END USART6_Init 1 */
  huart6.Instance = USART6;
  huart6.Init.BaudRate = 115200;
  huart6.Init.WordLength = UART_WORDLENGTH_8B;
  huart6.Init.StopBits = UART_STOPBITS_1;
  huart6.Init.Parity = UART_PARITY_NONE;
  huart6.Init.Mode = UART_MODE_TX_RX;
  huart6.Init.HwFlowCtl = UART_HWCONTROL_NONE;
  huart6.Init.OverSampling = UART_OVERSAMPLING_16;
  huart6.Init.OneBitSampling = UART_ONE_BIT_SAMPLE_DISABLE;
  huart6.AdvancedInit.AdvFeatureInit = UART_ADVFEATURE_NO_INIT;
  if (HAL_UART_Init(&huart6) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN USART6_Init 2 */

  /* USER CODE END USART6_Init 2 */

}

/**
  * Enable DMA controller clock
  */
static void MX_DMA_Init(void)
{

  /* DMA controller clock enable */
  __HAL_RCC_DMA2_CLK_ENABLE();

  /* DMA interrupt init */
  /* DMA2_Stream0_IRQn interrupt configuration */
  HAL_NVIC_SetPriority(DMA2_Stream0_IRQn, 5, 0);
  HAL_NVIC_EnableIRQ(DMA2_Stream0_IRQn);
  /* DMA2_Stream3_IRQn interrupt configuration */
  HAL_NVIC_SetPriority(DMA2_Stream3_IRQn, 5, 0);
  HAL_NVIC_EnableIRQ(DMA2_Stream3_IRQn);
  /* DMA2_Stream6_IRQn interrupt configuration */
  HAL_NVIC_SetPriority(DMA2_Stream6_IRQn, 5, 0);
  HAL_NVIC_EnableIRQ(DMA2_Stream6_IRQn);

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
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();
  __HAL_RCC_GPIOD_CLK_ENABLE();
  __HAL_RCC_GPIOC_CLK_ENABLE();

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOA, GPIO_PIN_4, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOD, GPIO_PIN_12|GPIO_PIN_13, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOB, GPIO_PIN_6, GPIO_PIN_RESET);

  /*Configure GPIO pin : PA3 */
  GPIO_InitStruct.Pin = GPIO_PIN_3;
  GPIO_InitStruct.Mode = GPIO_MODE_IT_FALLING;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

  /*Configure GPIO pin : PA4 */
  GPIO_InitStruct.Pin = GPIO_PIN_4;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_PULLUP;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

  /*Configure GPIO pins : PD12 PD13 */
  GPIO_InitStruct.Pin = GPIO_PIN_12|GPIO_PIN_13;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOD, &GPIO_InitStruct);

  /*Configure GPIO pin : PB6 */
  GPIO_InitStruct.Pin = GPIO_PIN_6;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

  /* EXTI interrupt init*/
  HAL_NVIC_SetPriority(EXTI3_IRQn, 5, 0);
  HAL_NVIC_EnableIRQ(EXTI3_IRQn);

}

/* USER CODE BEGIN 4 */
void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)
{

	if(GPIO_Pin == GPIO_PIN_3 && id == 3 && ADS1256.data_startFlag == 1 && I2cC.i2cRecive == 0 && stattisComputingStatus == statisticComputingNORMAL)
	{

		//2021/0201/George code from ADC Task.
		//TODO:SPI handshake from ADS1256 24 bit, 8bit(High), 8bit(Medium), 8bit(Low)
		HAL_SPI_TransmitReceive_DMA(&hspi1,RDATACsend_data,Databuffer,3);

		// construct 24 bit value
		read  = ((int32_t)Databuffer[0] << 16) & 0x00FF0000; //8bit(High)
		read |= ((int32_t)Databuffer[1] << 8); //8bit(Medium)
		read |= Databuffer[2]; //8bit(Low)
		if (read & 0x800000){ //Determine negative value.
			read |= 0xFF000000;
		}

		data = read;
		//2021/0309/George
		//data = data / 1677721;
		data = data / (1678043 * 0.496);
		ADS1256.data_buffer[ADS1256.data_index] = data; //plus 2 for FFT using
		ADS1256.data_index++;

		if(ADS1256.data_index == ADS1256.data_length) //divide 2 for FFT real data equal 4096
		{
		/* The xHigherPriorityTaskWoken parameter must be initialized to pdFALSE because it will get set to pdTRUE inside the interrupt-safe API function if a context switch is required. */
			BaseType_t xHigherPriorityTaskWoken;
			xHigherPriorityTaskWoken = pdFALSE;
			xSemaphoreGiveFromISR(adcBinarySemHandle,&xHigherPriorityTaskWoken); //Wakeup High Priority Task

				if(xHigherPriorityTaskWoken == pdTRUE)
				{
					portEND_SWITCHING_ISR( xHigherPriorityTaskWoken ); //Switch high priority task from ISR
				}

			ADS1256.data_index = 0;
			HAL_GPIO_TogglePin(GPIOD, GPIO_PIN_13);
		}

	}
}

void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
{
  /* Prevent unused argument(s) compilation warning */
  UNUSED(huart);

  /* NOTE : This function should not be modified, when the callback is needed,
            the HAL_UART_RxCpltCallback can be implemented in the user file
   */
  USARTBLE.iapbuffer[USARTBLE.RxCount++]= aRxBuffer[0];
  if(aRxBuffer[0]==0x0A)//when receive 0x0a("\n" Line feeds string),it is a effective command, Send a receive flag.
  	{
	  USARTBLE.RxCount=0;
	  _Bool command = checkBLECommandFromBLEGateway(USARTBLE.iapbuffer ,"request",7);
	  if(command)
	  {
		  USARTBLE.IAPflag =1;
		  USARTBLE.sendflag = 0;
		  BLE_USART(huart, &statistic_value);
	  }
	  else
	  {
		  memset( USARTBLE.iapbuffer, 0, strlen(USARTBLE.iapbuffer) );
	  }

  	}
  	if(USARTBLE.RxCount>=15)//no  "\n" Line feeds string full over to 24 byte, clear data
  	{
  		USARTBLE.RxCount=0;
  		memset( USARTBLE.iapbuffer, 0, strlen(USARTBLE.iapbuffer) ); //clear Receive data
  	}

  while(HAL_UART_Receive_IT(huart, (uint8_t *)aRxBuffer, 1)==HAL_OK);
}




/* USER CODE END 4 */

/* USER CODE BEGIN Header_ADC_Thread */
/**
  * @brief  Function implementing the ADC_Task thread.
  * @param  argument: Not used 
  * @retval None
  */
/* USER CODE END Header_ADC_Thread */
void ADC_Thread(void const * argument)
{
  /* USER CODE BEGIN 5 */

  const TickType_t xMaxExpectedBlockTime = pdMS_TO_TICKS( 500 );
  /* Infinite loop */
  for(;;)
  {
		 if( xSemaphoreTake( adcBinarySemHandle, xMaxExpectedBlockTime ) == pdPASS && I2cC.i2cRecive == 0){

			/*TODO: send data buffer to FFT data buffer*/
			BaseType_t xStatus;
			xStatus = xQueueSendToBack(adcQueueHandle, &xdatatoSend , 0);
			queueCount = uxQueueMessagesWaiting(adcQueueHandle);

			//TODO: wakeup FFT Task
			if(xStatus == pdPASS)
			{
				vTaskResume(FFT_TaskHandle);
			};
		}
  }
  /* USER CODE END 5 */
}

/* USER CODE BEGIN Header_FFT_Thread */
/**
* @brief Function implementing the FFT_Task thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_FFT_Thread */
void FFT_Thread(void const * argument)
{
  /* USER CODE BEGIN FFT_Thread */
  /* Infinite loop */
  for(;;)
  {
	  BaseType_t xStatus;
	 	  queueCount = uxQueueMessagesWaiting(adcQueueHandle);
	 	  if(queueCount!=0){
	 			  xStatus = xQueueReceive(adcQueueHandle, &dataRecive, 100);
	 			  queueCount = uxQueueMessagesWaiting(adcQueueHandle);

	 			HAL_IWDG_Refresh(&hiwdg);

	 			float32_t * rawdataBuffer;
	 			rawdataBuffer = pvPortMalloc(4096 * sizeof(float32_t));

	 			//TODO : disable collect data flag
	 			stattisComputingStatus = statisticComputingBUSY;

	 			for(uint32_t i = 0; i<dataLength; i++)
	 			{
	 				//recivedata5 = *(dataRecive[0]+i);
	 				rawdataBuffer[i]=*(dataRecive[0]+i);
	 				FFTdata[i*2] = *(dataRecive[0]+i);
	 				FFTdata[i*2+1] = 0; // data format like
	 			}

	 			if(xStatus == pdPASS)
	 			{

	 				/*TODO: Process the data through the CFFT/CIFFT module */
	 				arm_cfft_f32(&arm_cfft_sR_f32_len4096, FFTdata, ifftFlag, doBitReverse);

	 				/*TODO: Process the data through the Complex Magnitude Module for
	 				calculating the magnitude at each bin */
	 				arm_cmplx_mag_f32(FFTdata, FFTRawData, fftSize);

	 				/*TODO: Calculates maxValue and returns corresponding BIN value */
	 				arm_max_f32(FFTRawData, 2048, &FFTmaxValue, &FFTMaxValueIndex);

	 			     /*
	 				 * TODO: the FFTRawData in python  ==> FFTRawData = yf = abs(fft(signal = testInput_f32_10khz))
	 				 * so we can make a new array like yf2 = 2/N * np.abs(yf[0:N//2]); in python
	 				 * It kindly would be
	 				 *  FFTRawData[] = 2/N * FFTRawData[0:N/2]
	 				 *
	 				 * */

	 				//2021/0218/George
	 				//TODO: Calculate displacement the max value condition is small than 20Hz
	 				FFTMaxValueIndex = ( FFTMaxValueIndex == 0 ) ? FFTMaxValueIndex+1 : FFTMaxValueIndex;

	 				//2021/0222/George
	 				//TODO: frequency equal samplingRate / datalength
	 				float frequencyResolution = (float)samplingRate/(float)fftSize;
	 				float integral = 2 * 3.1415926 * FFTMaxValueIndex * frequencyResolution;

	 				//TODO: max acceleration value (peak) is frequency domain *2/datalength
	 				float AccelerationFFTmaxValue = FFTmaxValue * 2 / dataLength;

	 				//TODO: turn acceleration to velocity (peak), should acceleration * g / (2 * pi * f) unit is mm/s
	 				float VelocityFFTmaxValue = AccelerationFFTmaxValue * 9807 /(2 * 3.1415926 * FFTMaxValueIndex * frequencyResolution);

	 				//TODO: turn velocity to displacement (peak), should / (2 * pi *f) unit mm
	 				float DisplacementFFTmaxValue = VelocityFFTmaxValue /(2 * 3.1415926 * FFTMaxValueIndex * frequencyResolution);

	 				//TODO: turn displacement peak to (peak to peak)
	 				float DisplacementP2pFFTmaxValue = DisplacementFFTmaxValue * 2;
	 				//FFTmaxValue = FFTmaxValue*2 / dataLength;



	 				/*TODO: Remove DC component*/
	 				FFTRawData[1] = 0;
	 				FFTRawData[2] = 0;
	 				FFTRawData[3] = 0;
	 				FFTRawData[4] = 0;
	 				FFTRawData[5] = 0;
	 				FFTRawData[6] = 0;
	 				FFTRawData[7] = 0;
	 				FFTRawData[8] = 0;
	 				//FFT symmetry data 2021/0203/George
	 				//TODO:introduce FFT symmetry principle
	 				/*     |                                                                   |
	 				 *     |                  |                             |                  |
	 				 *     |        |         |                             |         |        |
	 				 *  FFT[10] FFT[1000] FFT[1500] FFT[2047] FFT[2048] FFT[2596] FFT[3096] FFT[4086]
	 				 * */
	 				FFTRawData[4088] = 0;
	 				FFTRawData[4089] = 0;
	 				FFTRawData[4090] = 0;
	 				FFTRawData[4091] = 0;
	 				FFTRawData[4092] = 0;
	 				FFTRawData[4093] = 0;
	 				FFTRawData[4094] = 0;
	 				FFTRawData[4095] = 0;


					//2021/0319/George
	 				/*TODO: Calculate time-domain math function*/
	 				arm_max_f32(rawdataBuffer, dataLength, &statistic_value.Statistic_max, &maxtestIndex);
	 				arm_min_f32(rawdataBuffer, dataLength, &statistic_value.Statistic_min, &mintestIndex);
	 				arm_var_f32(rawdataBuffer, dataLength, &statistic_value.Statistic_var);
	 				arm_rms_f32(rawdataBuffer, dataLength, &statistic_value.Statistic_rms);
	 				arm_mean_f32(rawdataBuffer, dataLength, &statistic_value.Statistic_mean);
	 				arm_std_f32(rawdataBuffer, dataLength, &statistic_value.Statistic_std);
	 				statistic_value.Statistic_crestFactor = statistic_value.Statistic_max/statistic_value.Statistic_rms;
	 				statistic_value.Statistic_p2p = statistic_value.Statistic_max - statistic_value.Statistic_min;

	 				//2021/03/22/George
	 				//TODO: calculate Statistic_Displacementp2p using time-domain p2p
	 				//formula : speedp2p = p2p / (2*pi*f), displacement = displacementp2p = speedp2p / (2*pi*f)
	 				statistic_value.Statistic_Displacementp2p = statistic_value.Statistic_p2p*9807 / (integral * integral);
	 				//2021/02/01/George start compute
	 				/*TODO: Calculate skewness and kurtosis will cause delay*/
	 				statistic_value.Statistic_kurtosis = Calculate_kurtosis(rawdataBuffer, dataLength);
	 				statistic_value.Statistic_skewness = Calculate_skewness(rawdataBuffer, dataLength);

	 				//2021/0319/George
	 				//TODO:free rawdataBuffer memory
	 				vPortFree(rawdataBuffer);

					//2021/0319/George
	 				/*TODO: Calculate frequency-domain math function*/

	 				/* focus broad band functionality */
					for(int i =0; i<sizeof(FreqSettingValueList)/sizeof(FreqMaxMin); i++)
					{
						settingValue = (&freqSettingValueList.range1+i);
						Calculate_FreqBandRMS(FFTRawData, settingValue, i);
					}
					/* focus broad band functionality */

					//2021/0319/George
	 				/*TODO: Calculate acceleration, velocity, displacement RMS*/
	 				Calculate_FreqOverAll(FFTRawData, dataLength);



	 				/*TODO: to calculate 3 times moving average*/
	 				averageTimes++;

	 				//2021/0203/George
	 				//TODO:new parameter p2p
	 				if(averageTimes == 1)
	 				{
	 					statistic_value.Statistic_max_Temp = statistic_value.Statistic_max;
	 					statistic_value.Statistic_min_Temp = statistic_value.Statistic_min;
	 					statistic_value.Statistic_p2p_Temp = statistic_value.Statistic_p2p;
	 					statistic_value.Statistic_var_Temp = statistic_value.Statistic_var;
	 					statistic_value.Statistic_rms_Temp = statistic_value.Statistic_rms;
	 					statistic_value.Statistic_mean_Temp = statistic_value.Statistic_mean;
	 					statistic_value.Statistic_std_Temp = statistic_value.Statistic_std;
	 					statistic_value.Statistic_FreqOvall_Temp = statistic_value.Statistic_FreqOvall;
	 					statistic_value.Statistic_crestFactor_Temp = statistic_value.Statistic_crestFactor;
	 					statistic_value.Statistic_SpeedOvall_Temp = statistic_value.Statistic_SpeedOvall;
	 					statistic_value.Statistic_kurtosis_Temp = statistic_value.Statistic_kurtosis;
	 					statistic_value.Statistic_skewness_Temp = statistic_value.Statistic_skewness;
	 				}
	 				if(averageTimes == 2)
	 				{
	 					statistic_value.Statistic_max_Temp += statistic_value.Statistic_max;
	 					statistic_value.Statistic_min_Temp += statistic_value.Statistic_min;
	 					statistic_value.Statistic_p2p_Temp += statistic_value.Statistic_p2p;
	 					statistic_value.Statistic_var_Temp += statistic_value.Statistic_var;
	 					statistic_value.Statistic_rms_Temp += statistic_value.Statistic_rms;
	 					statistic_value.Statistic_mean_Temp += statistic_value.Statistic_mean;
	 					statistic_value.Statistic_std_Temp += statistic_value.Statistic_std;
	 					statistic_value.Statistic_FreqOvall_Temp += statistic_value.Statistic_FreqOvall;
	 					statistic_value.Statistic_crestFactor_Temp += statistic_value.Statistic_crestFactor;
	 					statistic_value.Statistic_SpeedOvall_Temp += statistic_value.Statistic_SpeedOvall;
	 					statistic_value.Statistic_kurtosis_Temp += statistic_value.Statistic_kurtosis;
	 					statistic_value.Statistic_skewness_Temp += statistic_value.Statistic_skewness;
	 				}
	 				if(averageTimes == 3)
	 				{
	 					statistic_value.Statistic_max = (statistic_value.Statistic_max_Temp +
	 							statistic_value.Statistic_max) / 3;
	 					statistic_value.Statistic_min = (statistic_value.Statistic_min_Temp +
	 							statistic_value.Statistic_min) / 3;
	 					statistic_value.Statistic_p2p = (statistic_value.Statistic_p2p_Temp +
								statistic_value.Statistic_p2p) / 3;
	 					statistic_value.Statistic_var = (statistic_value.Statistic_var_Temp +
	 							statistic_value.Statistic_var) / 3;
	 					statistic_value.Statistic_rms = (statistic_value.Statistic_rms_Temp +
	 							statistic_value.Statistic_rms) / 3;
	 					statistic_value.Statistic_mean = (statistic_value.Statistic_mean_Temp +
	 							statistic_value.Statistic_mean) / 3;
	 					statistic_value.Statistic_std = (statistic_value.Statistic_std_Temp +
	 							statistic_value.Statistic_std) / 3;
	 					statistic_value.Statistic_FreqOvall = (statistic_value.Statistic_FreqOvall_Temp +
	 							statistic_value.Statistic_FreqOvall) / 3;
	 					statistic_value.Statistic_crestFactor = (statistic_value.Statistic_crestFactor_Temp +
	 							statistic_value.Statistic_crestFactor) / 3;
	 					statistic_value.Statistic_SpeedOvall = (statistic_value.Statistic_SpeedOvall_Temp +
	 							statistic_value.Statistic_SpeedOvall) / 3;
	 					statistic_value.Statistic_kurtosis = (statistic_value.Statistic_kurtosis_Temp +
	 							statistic_value.Statistic_kurtosis) / 3;
	 					statistic_value.Statistic_skewness = (statistic_value.Statistic_skewness_Temp +
	 							statistic_value.Statistic_skewness) / 3;


	 					USARTBLE.sendflag = 1;
	 					averageTimes = 0;

	 					/*TODO: BLE send data*/
	 					BLE_USART(&huart6, &statistic_value);

	 					//2021/0201/George
	 					//TODO : Initial statistic value to zero
	 					//Initial_AllStatisticValue();

	 				}

	 				HAL_GPIO_TogglePin(GPIOD, GPIO_PIN_12);

	 				//TODO : enable collect data flag
	 				stattisComputingStatus = statisticComputingNORMAL;
	 			}

	 			/*If there is no data in queue, start ads1256 conversion*/

	 	/*
	 			if(testIndex !=  refIndex)
	 			{
	 			  status = ARM_MATH_TEST_FAILURE;
	 			}
	 */
	 	  }

	 	  else{
	 		 vTaskSuspend(NULL);

	 	  }
  }
  /* USER CODE END FFT_Thread */
}

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
