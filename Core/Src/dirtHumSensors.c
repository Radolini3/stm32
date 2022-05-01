/*
 * dirtHumSensors.c
 *
 *  Created on: Apr 30, 2022
 *      Author: HP
 */
#include "main.h"
#include "adc.h"
#include "tim.h"
#include "usart.h"
#include "gpio.h"
	#include "globalVars.h"
	#include "string.h"
	#include "stdio.h"



	//extern float moisture_percentage[6];
	float map(uint16_t val, int in_min, int in_max, int out_min, int out_max) {
	  return (val - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
	}



void dirtHumRead(){
		  ADC_Select_CH1();
		  HAL_ADC_Start(&hadc1);
		  HAL_ADC_PollForConversion(&hadc1, 1000);
		  ADC_VAL[0] = HAL_ADC_GetValue(&hadc1);
		  HAL_ADC_Stop(&hadc1);

		  ADC_Select_CH2();
		  HAL_ADC_Start(&hadc1);
		  HAL_ADC_PollForConversion(&hadc1, 1000);
		  ADC_VAL[1] = HAL_ADC_GetValue(&hadc1);
		  HAL_ADC_Stop(&hadc1);

		  ADC_Select_CH6();
		  HAL_ADC_Start(&hadc1);
		  HAL_ADC_PollForConversion(&hadc1, 1000);
		  ADC_VAL[2] = HAL_ADC_GetValue(&hadc1);
		  HAL_ADC_Stop(&hadc1);

		  ADC_Select_CH7();
		  HAL_ADC_Start(&hadc1);
		  HAL_ADC_PollForConversion(&hadc1, 1000);
		  ADC_VAL[3] = HAL_ADC_GetValue(&hadc1);
		  HAL_ADC_Stop(&hadc1);

		  ADC_Select_CH8();
		  HAL_ADC_Start(&hadc1);
		  HAL_ADC_PollForConversion(&hadc1, 1000);
		  ADC_VAL[4] = HAL_ADC_GetValue(&hadc1);
		  HAL_ADC_Stop(&hadc1);

		  ADC_Select_CH9();
		  HAL_ADC_Start(&hadc1);
		  HAL_ADC_PollForConversion(&hadc1, 1000);
		  ADC_VAL[5] = HAL_ADC_GetValue(&hadc1);
		  HAL_ADC_Stop(&hadc1);

		  for(int i = 0; i<6; i++){
			  moisture_percentage[i] = 100-( map(ADC_VAL[i], 1000, 3970, 0, 100));

		  if (moisture_percentage[i]>100){moisture_percentage[i] = 100;}
		  if (moisture_percentage[i]<0){moisture_percentage[i] = 0;}

		  }

					for(int i = 0; i<6; i++){
								  sprintf(UartOutText, "Czujnik nr: %d val %2.f \n\r ", i+1, moisture_percentage[i]);
								  sendString_UART(UartOutText);
							  }
							  sendString_UART("===================================== \n\r");

}


