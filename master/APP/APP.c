/*
 * APP.c
 *
 * Created: 8/7/2023 10:30:04 AM
 *  Author: mohamed hatem
 */ 
#include "utils.h"
#include "MemMap.h"
#include "stdtypes.h"
#include "DIO_INTERFACE.h"
#include "lcd_interface.h"
#include "keypad_interface.h"
#include "NVM.h"
#include "uart.h"
#include "uart_service.h"
#include "Password.h"
#define  Globale_enable sei
#define  Globale_disable cli
#include "spi_interface.h"
#include "APP.h"
#include "option.h"
u8 flag=0;
void uart_interrupt_func(void)
{
	if(flag==0)
	{
		u8 arr[20];
		UART_ReceiveString(arr);
		LCD_Clear();
		LCD_WriteString(arr);
		_delay_ms(1000);
		while(1)
		{
			
		}
	}
}
void app_start (void)
{
	DIO_Init();
	LCD_Init();
	KEYPAD_Init();
	uart_init();
	uart_rx_interrupt_enable();
	uart_rx_SetCallBack(uart_interrupt_func);
	SPI_Init(MASTER);
	Globale_enable();
	u8 check=0;
	if(nvm_read_bit(block_counter_ADDRESS)==Number_of_trial)
	{
		block_fun();
	}
	LCD_WriteString("Welcome to smart");
	LCD_GoTo(1,0);
	LCD_WriteString("home system");
	_delay_ms(500);//Halt the system for the given time in (ms)
	LCD_Clear();//remove all previously printed characters on the LCD and move the cursor to the first column of the first row
	
	/***************************/
	if (nvm_read_bit(ADMIN_PASS_STATUS_ADDRESS)==PASS_NOT_SET)
	{
		LCD_WriteString("Login for");//printing login menu
		LCD_GoTo(1,0);//move the cursor to the second line
		LCD_WriteString("first time");
		_delay_ms(1000);//Halt the system for the given time in (ms)
		LCD_Clear();//remove all previously printed characters on the LCD and move the cursor to the first column of the first row
		set_pass_first_time();
	}
	while(nvm_read_bit(block_counter_ADDRESS)<Number_of_trial&&check==0)
	{
		write_pass();
		check=Pass_compare(check_arr,pass);
		if(check==1)
		{
			LCD_WriteString("Right pass");
			NVM_write_bit(block_counter_ADDRESS,0);
			_delay_ms(300);
			LCD_Clear();
		}
		else
		{
			LCD_WriteString("wrong pass");
			NVM_write_bit(block_counter_ADDRESS,nvm_read_bit(block_counter_ADDRESS)+1);
			_delay_ms(300);
			LCD_Clear();
			if(nvm_read_bit(block_counter_ADDRESS)==Number_of_trial)
			{
				block_fun();
			}
		}
	}
	pass_change();
	while(1)
	{
		if(flag==0)
		{
			
			en_menu num=menu_select();
			LCD_Clear();
			MenuOption(num);
		}
		
	}
}
