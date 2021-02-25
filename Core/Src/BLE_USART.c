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

	}
	if(USARTBLE.sendflag ==1)
	{

		//2021/0201/George
		//TODO : BLE transmission parameter number3 from var to min and
		snprintf_(USARTBLE.buffer, 128 , "%.4f,%.4f,%.4f,%.4f,%.4f,%.4f,%.4f,%.4f,%.4f,%.4f,%.4f,%.4f,%.4f", sendpData->Statistic_FreqOvall*1000,sendpData->Statistic_SpeedOvall*1000,
					sendpData->Statistic_DisplacementOvall,sendpData->Statistic_max*1000,sendpData->Statistic_min*1000,sendpData->Statistic_p2p*1000,
					sendpData->Statistic_var*1000,sendpData->Statistic_mean*1000,sendpData->Statistic_crestFactor*1000,
					sendpData->Statistic_kurtosis*1000, sendpData->Statistic_skewness*1000,
					statistic_value.Statistic_FreqPeak[0]*1000,statistic_value.Statistic_FreqPeak[1]*1000,statistic_value.Statistic_FreqPeak[2]*1000);

		USARTBLE.bufferSize = min_(APP_BUFFER_SIZE, strlen(USARTBLE.buffer));

		if(HAL_UART_Transmit_DMA(huart, USARTBLE.buffer, USARTBLE.bufferSize)==HAL_OK)
		{
			__NOP();
		}

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

