/*
 * utilityCodes.c
 *
 *  Created on: May 2, 2022
 *      Author: HP
 */
#include "main.h"
#include "tim.h"
#include "usart.h"
/*Moje include'y*/
	#include "globalVars.h"
	#include "string.h"
	#include "stdio.h"
/*Przerwanie po upłynięciu tim6 równego 10000 cykli (po sekundzie)*/
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim){
	dirtHumRead();
	DHT11_allData();
	displayReadings(disp_No);
}

/*Przerwanie na liniach 10-15, w tym przypadku to jest button na płytce Nucleo*/
void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)
{
		disp_No++;
		if (disp_No == 6) disp_No = 1;
		displayReadings(disp_No);
}
/*Milisekundowy delay na timerze, tim2 prescaler 72-1, brak przerwań przez tim2*/
void delay_us(uint32_t time){
	__HAL_TIM_SET_COUNTER(&htim2, 0);
	while ((__HAL_TIM_GET_COUNTER(&htim2))<time);
}

/*Wyślij po UARCIE numer 2 baudrate = 115200B/s*/
void sendString_UART(char*text){
	HAL_UART_Transmit(&huart2,  (uint8_t*)text, strlen(text), 1000);
}

/*Przeskaluj wartość analogową z adcka na procenty*/
float map(uint16_t val, int in_min, int in_max, int out_min, int out_max) {
  return (val - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}
