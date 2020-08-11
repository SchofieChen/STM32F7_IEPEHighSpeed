/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "string.h"
#include "math.h"
#include "BLE_USART.h"
#include <stdint.h>
#include "printf.h"
#include "Calculate_statistic.h"

/* Private typedef -----------------------------------------------------------*/
extern USART_BLE USARTBLE;	//Wayne0905

/* Private variables ---------------------------------------------------------*/


void BLE_USART(UART_HandleTypeDef *huart, Sv *sendpData )
{
	if( USARTBLE.IAPflag == 1)
	{
		USARTBLE.sendflag =0;
		TM_DelayMillis(1000);
		NVIC_SystemReset();
		/*if(HAL_UART_Transmit_DMA(huart, "RESTART\r\n",9)==HAL_OK)
		{
			TM_DelayMillis(500);
			NVIC_SystemReset();
		}
		else
		{
			HAL_UART_Receive_IT(huart, (uint8_t *)aRxBuffer, 10);
		}
		*/
	}
	if(USARTBLE.sendflag ==1)
	{



		snprintf_(USARTBLE.buffer, 128 , "%.4f,%.4f,%.4f,%.4f,%.4f,%.4f,%.4f,%4f", sendpData->Statistic_FreqOvall,
				sendpData->Statistic_max,sendpData->Statistic_min,sendpData->Statistic_var,sendpData->Statistic_rms,
				sendpData->Statistic_mean, sendpData->Statistic_crestFactor,sendpData->Statistic_SpeedOvall);

		USARTBLE.bufferSize = min_(APP_BUFFER_SIZE, strlen(USARTBLE.buffer));
		USARTBLE.sendTimeout = 100 ;
		if(HAL_UART_Transmit_DMA(huart, USARTBLE.buffer, USARTBLE.bufferSize)==HAL_OK)
		{
			float a = 1;
		}
		/*
		 HAL_UART_Receive(huart , &USARTBLE.Rbuffer, 14, 1000);

		 char C[20];
		 strcpy(C,  USARTBLE.Rbuffer );
		 */
		 //0x1;
	}
}
