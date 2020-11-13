/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "string.h"
#include "math.h"
#include "BLE_USART.h"
#include <stdint.h>
#include "printf.h"
#include "Calculate_statistic.h"
#include "Delay.h"
#include <stdbool.h>
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


		snprintf_(USARTBLE.buffer, 128 , "%.4f,%.4f,%.4f,%.4f,%.4f,%.4f,%.4f", sendpData->Statistic_FreqOvall*1000,
					sendpData->Statistic_max*1000,sendpData->Statistic_var*1000,sendpData->Statistic_crestFactor*1000,
					statistic_value.Statistic_FreqPeak[0]*1000,statistic_value.Statistic_FreqPeak[1]*10000,
					statistic_value.Statistic_FreqPeak[2]*10000);

		USARTBLE.bufferSize = min_(APP_BUFFER_SIZE, strlen(USARTBLE.buffer));
		//USARTBLE.sendTimeout = 100 ;
		if(HAL_UART_Transmit_DMA(huart, USARTBLE.buffer, USARTBLE.bufferSize)==HAL_OK)
		{
			__NOP();
		}
		/*
		 HAL_UART_Receive(huart , &USARTBLE.Rbuffer, 14, 1000);

		 char C[20];
		 strcpy(C,  USARTBLE.Rbuffer );
		 */
		 //0x1;
	}
}

_Bool checkBLECommandFromBLEGateway(char * BLEcommand,char * index, int len)
{
	if(strlen(BLEcommand) > 0)
	{
		   //Test 比對 function
	   char * pch;
	   /* 找尋 simple 字串 */
	   pch = strstr (BLEcommand,index);
	   if(strncmp(pch, index, len) == 0) {
		   return true;
	   }
	   else
	   {
		   return false;
	   }

	}
	else
	{

		return false;
	}

}

