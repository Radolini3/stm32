/*
 * globalVars.c
 *
 *  Created on: 30 kwi 2022
 *      Author: HP
 */
#include "main.h"
#include "adc.h"
#include "tim.h"
#include "usart.h"
#include "gpio.h"
	#include "string.h"
	#include "stdio.h"
	/*Zmienne przechowujące bufor dla przesyłania UART'em*/
	char UartOutText[100], UartInput[5];
	/*ADC zmienna*/

	 uint8_t Rh_byte1, Rh_byte2, Temp_byte1, Temp_byte2;
	 uint16_t SUM, RH, TEMP;
	 uint8_t Presence = 0;

	 uint32_t ADC_VAL[7];
	 float moisture_percentage[6];

	 float Temperature;
	 float Humidity;
	 float lightIntensity;
