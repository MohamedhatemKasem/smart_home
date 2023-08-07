/*
 * uart.c
 *
 * Created: 7/15/2023 5:53:01 PM
 *  Author: mohamed hatem
 */ 
#include "stdtypes.h"
#include "MemMap.h"
#include "utils.h"
#include "uart.h"
#include "uartcfg.h"

const u16 BaudRateArray[TOTAL_SPEED_MODE][TOTAL_CPU_F][TOTAL_BAUD_RATE]=
{{{103, 51, 25, 16, 12,  8},{207,103, 51, 34, 25, 16},{416,207,103, 68 ,51, 34}},
{{207,103, 51, 34, 25, 16},{416,207,103, 68 ,51, 34},{832,416,207,138,103, 68}}};
static void (*Uart_rx_Fptr) (void)=NULLPTR;
void uart_init(void)
{
	u16 UBRR_var=0;
	/***************************** transmission speed***************************/
	#if (SPEED_MODE==NORMAL_SPEED)
	clear_bit(UCSRA,U2X);
	#elif (SPEED_MODE==DOUBLE_SPEED)
	SET_BIT(UCSRA,U2X);
	#endif
	//******************set URSEL to write data to UCSRC register***************/ 
	set_bit(UCSRC,URSEL);
	
	 #if (SYNCH_MODE==SYNCH)
	 SET_BIT(UCSRC_var,UMSEL)
	 #elif (SYNCH_MODE==ASYNCH)
	 clear_bit(UCSRC,UMSEL);
	 #endif
	#if (PARITY_MODE==NO_PARITY)
	clear_bit(UCSRC,UPM0);
	clear_bit(UCSRC,UPM1);
	#elif (PARITY_MODE==EVEN_PARITY)
	clear_bit(UCSRC,UPM0);
	SET_BIT(UCSRC_var,UPM1);
	#elif (PARITY_MODE==ODD_PARITY)
	SET_BIT(UCSRC,UPM0);
	SET_BIT(UCSRC,UPM1);
	#endif
	//************************Data bits*******************************/
	#if (N_DATA_BITS==_5_DATA_BITS)
	clear_bit(UCSRC,UCSZ0);
	clear_bit(UCSRC,UCSZ1);
	clear_bit(UCSRC,UCSZ2);
	#elif (N_DATA_BITS==_6_DATA_BITS)
	SET_BIT(UCSRC_var,UCSZ0);
	clear_bit(UCSRC,UCSZ1);
	clear_bit(UCSRC,UCSZ2);
	#elif (N_DATA_BITS==_7_DATA_BITS)
	clear_bit(UCSRC,UCSZ0);
	SET_BIT(UCSRC,UCSZ1);
	clear_bit(UCSRB,UCSZ2);
	#elif (N_DATA_BITS==_8_DATA_BITS)
	SET_BIT(UCSRC,UCSZ0);
	SET_BIT(UCSRC,UCSZ1);
	clear_bit(UCSRB,UCSZ2);
	#elif (N_DATA_BITS==_9_DATA_BITS)
	SET_BIT(UCSRC,UCSZ0);
	SET_BIT(UCSRC,UCSZ1);
	SET_BIT(UCSRB,UCSZ2);
	#endif
	//************************Stop bits*******************************/
	#if (N_STOP_BITS==ONE_STOP_BIT)
	clear_bit(UCSRC,USBS);
	#elif (N_STOP_BITS==TWO_STOP_BIT)
	SET_BIT(UCSRC,USBS);
	#endif


UBRR_var=BaudRateArray[SPEED_MODE][CPU_F][BUAD_RATE];
UBRRH = (u8)(UBRR_var>>8);
UBRRL = (u8)UBRR_var;

	//UBRRL=51;//9600 boud rate
	set_bit(UCSRB,TXEN);//
	set_bit(UCSRB,RXEN);
	
}
u8 uart_recieve_data(void)
{
	while(read_bit(UCSRA,RXC)==0);
	return UDR;
}
void uart_rx_interrupt_enable(void)
{
	set_bit(UCSRB,RXCIE);
}
void uart_rx_interrupt_disable(void)
{
	clear_bit(UCSRB,RXCIE);
}

void uart_rx_SetCallBack(void(*LocalPtr)(void))
{
	Uart_rx_Fptr=LocalPtr;
}
ISR(UART_RX_vect)
{
	if(Uart_rx_Fptr!=NULLPTR)
	{
		Uart_rx_Fptr();
	}
}
