/*
 * uart_service.c
 *
 * Created: 7/16/2023 1:16:18 AM
 *  Author: mohamed hatem
 */ 
#include "uart_service.h"
#include "uart.h"
#include "stdtypes.h"
#include "utils.h"
#include "stdtypes.h"
void UART_SendString(u8*str)
{
	u8 i=0;
	for(i=0;str[i]!=0;i++)
	{
		uart_send_data(str[i]);
	}
	uart_send_data(0x0d);
	
}
