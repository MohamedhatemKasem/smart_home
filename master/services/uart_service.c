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
void UART_ReceiveString(u8*str)
{
	u8 i=0;
	str[i]=uart_recieve_data();
	for(;str[i]!=0x0d;)
	{
		i++;
		str[i]=uart_recieve_data();
	}
	str[i]=0;
}


