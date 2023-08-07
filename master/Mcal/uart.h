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
u8 uart_recieve_data(void);
u8 uart_recieve_data_peridic(u8 *pdata);
void uart_rx_interrupt_enable(void);
void uart_rx_interrupt_disable(void);
void uart_rx_SetCallBack(void(*LocalPtr)(void));
#endif /* UART_H_ */