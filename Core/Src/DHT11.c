/*
 * DHT11.c
 *
 *  Created on: Apr 30, 2022
 *      Author: HP
 */


#include "main.h"
#include "adc.h"
#include "tim.h"
#include "usart.h"
#include "gpio.h"

	#include "string.h"
	#include "stdio.h"
	#include "globalVars.h"
	#define PORT_A GPIOA
	#define DHT11_PIN GPIO_PIN_6 //Dla czujnika DHT11 temperatury/wilgotności powietrza (PA6)

	/*Zmienne do obsługi czujnika DTH11 */


	/*=============================Ustaw PA6 jako wyjście=============================*/
	void Set_Pin_Output(GPIO_TypeDef *GPIOx, uint16_t GPIO_Pin){
		GPIO_InitTypeDef GPIO_InitStruct = {0};
		GPIO_InitStruct.Pin = GPIO_Pin;
		GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
		GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
		HAL_GPIO_Init(GPIOx, &GPIO_InitStruct);
	}
	/*=============================Ustaw PA6 jako wejście=============================*/
	void Set_Pin_Input(GPIO_TypeDef *GPIOx, uint16_t GPIO_Pin){
		GPIO_InitTypeDef GPIO_InitStruct = {0};
		GPIO_InitStruct.Pin = GPIO_Pin;
		GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
		GPIO_InitStruct.Pull = GPIO_PULLUP;
		HAL_GPIO_Init(GPIOx, &GPIO_InitStruct);
	}


	/*=============================Inicjalizuj czujnik=============================*/
	void DHT11sensorInit(void){
		Set_Pin_Output (PORT_A, DHT11_PIN);  // set the pin as output
		HAL_GPIO_WritePin (PORT_A, DHT11_PIN, 0);   // pull the pin low
		delay_us (18000);   // wait for 18ms
	    HAL_GPIO_WritePin (PORT_A, DHT11_PIN, 1);   // pull the pin high
		delay_us (20);   // wait for 20us
		Set_Pin_Input(PORT_A, DHT11_PIN);    // set as input
	}


	/*=============================Odpowiedź czujnika=============================*/
	uint8_t sensorResponse(void){
		uint8_t Response = 0;
		delay_us (40);
		if (!(HAL_GPIO_ReadPin (PORT_A, DHT11_PIN))){
			delay_us (80);
			if ((HAL_GPIO_ReadPin (PORT_A, DHT11_PIN))) Response = 1;
			else Response = -1; // 255
		}
		while ((HAL_GPIO_ReadPin (PORT_A, DHT11_PIN)));   // wait for the pin to go low

		return Response;
	}

	/*=============================Odczyt=============================*/
	uint8_t sensorRead(void){
		uint8_t i,j;
		for (j=0;j<8;j++)
		{
			while (!(HAL_GPIO_ReadPin (PORT_A, DHT11_PIN)));   // wait for the pin to go high
			delay_us (40);   // wait for 40 us
			if (!(HAL_GPIO_ReadPin (PORT_A, DHT11_PIN)))   // if the pin is low
			{
				i&= ~(1<<(7-j));   // write 0
			}
			else i|= (1<<(7-j));  // if the pin is high, write 1
			while ((HAL_GPIO_ReadPin (PORT_A, DHT11_PIN)));  // wait for the pin to go low
		}
		return i;
	}

	void DHT11_allData(){
		  DHT11sensorInit();
		  Presence = sensorResponse();
		  Rh_byte1 = sensorRead ();
		  Rh_byte2 = sensorRead ();
		  Temp_byte1 = sensorRead ();
		  Temp_byte2 = sensorRead ();
		  SUM = sensorRead();
		  TEMP = Temp_byte1;
		  RH = Rh_byte1;
		  Temperature = (float) TEMP;
		  Humidity = (float) RH;


		  sprintf(UartOutText, "Temp: %f Humidity %f \n\r ", Temperature, Humidity);
		  sendString_UART(UartOutText);

	}
