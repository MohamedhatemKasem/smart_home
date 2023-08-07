/*
 * APP.c
 *
 * Created: 8/7/2023 12:00:30 PM
 *  Author: mohamed hatem
 */ 
#include "utils.h"
#include "MemMap.h"
#include "stdtypes.h"
#include "DIO_INTERFACE.h"
#include "motor_interface.h"
#include "ADC_INTERFAC.h"
#include "sensors_interfaces.h"
#include "Timer.h"
#include "uart.h"
#include "uart_service.h"
#define  Globale_enable sei
#define  Globale_disable cli
#include "RGB.h"
#include "spi_interface.h"
#include "app_cfg.h"
#include "standard massege.h"
void option_request(void)
{
	u8 request = DEFAULT_ACK;//the value that is received from the master
	u8 response = DEFAULT_ACK;//the values that is sent back to the master
	SPI_receive_no_block(&request);//wait for the master to start the transmitting
	//ALL Messages are defined in STD_messages.h
	switch (request)
	{
		/*********************************   STATUS COMMANDS ********************************/
		//commands related to send the current status back to the master
		case ROOM1_STATUS:
		if (DIO_readPin(ROOM1_PIN)==LOW)//if the led is turned off
		{
			response = OFF_STATUS;//set the response as off status
		}
		else if (DIO_readPin(ROOM1_PIN)==HIGH)//if the led is turned on
		{
			response = ON_STATUS;//set the response as on status
		}
		SPI_SendNoBlock(response);//response to the transmitter with the status
		break;//break the switch case
		case ROOM2_STATUS:
		if (DIO_readPin(ROOM2_PIN)==LOW)//if the led is turned off
		{
			response = OFF_STATUS;//set the response as off status
		}
		else if (DIO_readPin(ROOM2_PIN)==HIGH)//if the led is turned on
		{
			response = ON_STATUS;//set the response as on status
		}
		SPI_SendNoBlock(response);//response to the transmitter with the status
		break;//break the switch case
		case ROOM3_STATUS:
		if (DIO_readPin(ROOM3_PIN)==LOW)//if the led is turned off
		{
			response = OFF_STATUS;//set the response as off status
		}
		else if (DIO_readPin(ROOM3_PIN)==HIGH)//if the led is turned on
		{
			response = ON_STATUS;//set the response as on status
		}
		SPI_SendNoBlock(response);//response to the transmitter with the status
		break;//break the switch case
		case ROOM4_STATUS:
		if (DIO_readPin(ROOM4_PIN)==LOW)//if the led is turned off
		{
			response = OFF_STATUS;//set the response as off status
		}
		else if (DIO_readPin(ROOM4_PIN)==HIGH)//if the led is turned on
		{
			response = ON_STATUS;//set the response as on status
		}
		SPI_SendNoBlock(response);//response to the transmitter with the status
		break;//break the switch case
		case AIR_COND_STATUS:
		if (DIO_readPin(AIR_COND_PIN)==LOW)//if the led is turned off
		{
			response = OFF_STATUS;//set the response as off status
		}
		else if (DIO_readPin(AIR_COND_PIN)==HIGH)//if the led is turned on
		{
			response = ON_STATUS;//set the response as on status
		}

		SPI_SendNoBlock(response);//response to the transmitter with the status
		break;
		case RGB_STATUS:
		if (DIO_readPin(RGB_PIN)==LOW)//if the led is turned off
		{
			response = OFF_STATUS;//set the response as off status
		}
		else if (DIO_readPin(RGB_PIN)==HIGH)//if the led is turned on
		{
			response = ON_STATUS;//set the response as on status
		}
		SPI_SendNoBlock(response);//response to the transmitter with the status
		break;//break the switch case
		/*********************************   TURN ON COMMANDS ********************************/
		case ROOM1_TURN_ON:
		DIO_WritePin(ROOM1_PIN,HIGH);
		break;//break the switch case
		case ROOM2_TURN_ON:
		DIO_WritePin(ROOM2_PIN,HIGH);
		break;//break the switch case
		case ROOM3_TURN_ON:
		DIO_WritePin(ROOM3_PIN,HIGH);
		break;//break the switch case
		case ROOM4_TURN_ON:
		DIO_WritePin(ROOM4_PIN,HIGH);
		break;//break the switch case
		case AIR_COND_TURN_ON:
		DIO_WritePin(AIR_COND_PIN,HIGH);//turn on the led of air conditioning
		break;//break the switch case
		case rgb_on_red:
		DIO_WritePin(RGB_PIN,HIGH);//turn on the led of the TV
		select_color3(rgb_on_red-rgb_on_red);
		break;//break the switch case
		case rgb_on_orange:
		DIO_WritePin(RGB_PIN,HIGH);//turn on the led of the TV
		select_color3(rgb_on_orange-rgb_on_red);
		break;//break the switch case
		case rgb_on_yellow:
		DIO_WritePin(RGB_PIN,HIGH);//turn on the led of the TV
		select_color3(rgb_on_yellow-rgb_on_red);
		break;//break the switch case
		case rgb_on_green:
		DIO_WritePin(RGB_PIN,HIGH);//turn on the led of the TV
		select_color3(rgb_on_green-rgb_on_red);
		break;//break the switch case
		case rgb_on_blue:
		DIO_WritePin(RGB_PIN,HIGH);//turn on the led of the TV
		select_color3(rgb_on_blue-rgb_on_red);
		break;//break the switch case
		case rgb_on_white:
		DIO_WritePin(RGB_PIN,HIGH);//turn on the led of the TV
		select_color3(rgb_on_white-rgb_on_red);
		break;//break the switch case
		case rgb_on_pink:
		DIO_WritePin(RGB_PIN,HIGH);//turn on the led of the TV
		select_color3(rgb_on_pink-rgb_on_red);
		break;//break the switch case
		case all_turn_on:
		DIO_WritePin(RGB_PIN,HIGH);//turn on the led of the TV
		DIO_WritePin(ROOM1_PIN,HIGH);//turn on the led of the TV
		DIO_WritePin(ROOM2_PIN,HIGH);//turn on the led of the TV
		DIO_WritePin(ROOM3_PIN,HIGH);//turn on the led of the TV
		DIO_WritePin(ROOM4_PIN,HIGH);//turn on the led of the TV
		select_color3(rgb_on_red-rgb_on_red);
		break;//break the switch case
		/*********************************   TURN OFF COMMANDS ********************************/
		case ROOM1_TURN_OFF:
		DIO_WritePin(ROOM1_PIN,LOW);//turn off the led of room 1
		break;//break the switch case
		case ROOM2_TURN_OFF:
		DIO_WritePin(ROOM2_PIN,LOW);//turn off the led of room 2
		break;//break the switch case
		case ROOM3_TURN_OFF:
		DIO_WritePin(ROOM3_PIN,LOW);//turn off the led of room 3
		break;//break the switch case
		case ROOM4_TURN_OFF:
		DIO_WritePin(ROOM4_PIN,LOW);//turn off the led of room 4
		break;//break the switch case
		case AIR_COND_TURN_OFF:
		DIO_WritePin(AIR_COND_PIN,LOW);//turn off the led of air conditioning
		TIMER0_OC0Mode(OC0_DISCONNECTED);
		break;//break the switch case
		case Rgb_off:
		DIO_WritePin(RGB_PIN,LOW);//turn off the led of the TV
		select_color3(7);
		break;//break the switch case
		case all_turn_off:
		DIO_WritePin(RGB_PIN,LOW);//turn on the led of the TV
		DIO_WritePin(AIR_COND_PIN,LOW);//turn on the led of the TV
		DIO_WritePin(ROOM1_PIN,LOW);//turn on the led of the TV
		DIO_WritePin(ROOM2_PIN,LOW);//turn on the led of the TV
		DIO_WritePin(ROOM3_PIN,LOW);//turn on the led of the TV
		DIO_WritePin(ROOM4_PIN,LOW);//turn on the led of the TV
		select_color3(7);
		select_color3(8);
		TIMER0_OC0Mode(OC0_DISCONNECTED);
		break;//break the switch case
		/*********************************   TURN OFF COMMANDS ********************************/
		case cond_speed1:
		TIMER0_OC0Mode(OC0_NON_INVERTING);
		OCR0=100;
		break;//break the switch case
		case cond_speed2:
		TIMER0_OC0Mode(OC0_NON_INVERTING);
		OCR0=150;
		break;//break the switch case
		case cond_speed3:
		TIMER0_OC0Mode(OC0_NON_INVERTING);
		OCR0=200;
		break;//break the switch case
		case cond_speed4:
		TIMER0_OC0Mode(OC0_NON_INVERTING);
		OCR0=255;
		break;//break the switch case
	}
}
void app_start(void)
{
	u8 data1,data2,data3,data4;
	DIO_Init();
	uart_init();
	SPI_Init(SLAVE);
	SPI_interrupt_enable();
	SPI_set_callback(option_request);
	ADC_Init(VREF_AVCC,ADC_SCALER_64);
	TIMER0_Init(TIMER0_FASTPWM_MODE,TIMER0_SCALER_8);
	Timer1_Init(TIMER1_FASTPWM_ICR_TOP_MODE,TIMER1_SCALER_8);
	Timer1_OCRA1Mode(OCRA_NON_INVERTING);
	Timer1_OCRB1Mode(OCRB_NON_INVERTING);
	TIMER0_OC0Mode(OC0_DISCONNECTED);
	TIMER2_Init(TIMER2_FASTPWM_MODE,TIMER2_SCALER_8);
	TIMER2_OC0Mode(OC2_NON_INVERTING);
	Globale_enable();	
	while(1)
	{
		
		data1=TEMP_Read(s1);
		data2=TEMP_Read(s2);
		data3=TEMP_Read(s3);
		data4=TEMP_Read(s4);
		if(data1>50)
		{
			UART_SendString("fire on room 1");
			MOTOR_CW(M1);
		}
		if(data2>50)
		{
			UART_SendString("fire on room 2");
			MOTOR_CW(M2);
		}
		if(data3>50)
		{
			UART_SendString("fire on room 3");
			MOTOR_CW(M3);
		}
		if(data4>50)
		{
			UART_SendString("fire on room 4");
			MOTOR_CW(M4);
		}	
	}
}