/*
 * uart.h
 *
 * Created: 7/15/2023 5:52:39 PM
 *  Author: mohamed hatem
 */ 


#ifndef UART_H_
#define UART_H_
#include "stdtypes.h"
void uart_init(void);
void uart_send_data(u8 data);
#endif /* UART_H_ */