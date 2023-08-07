/*
 * Menu.c
 *
 * Created: 8/6/2023 12:09:20 AM
 *  Author: mohamed hatem
 */ 
#include "stdtypes.h"
#include "lcd_interface.h"
#include "keypad_interface.h"
#include "menu.h"
#include "utils.h"
#include "standard massege.h"
#include "spi_interface.h"
en_menu menu_select(void)
{
	u8 k=0;
	en_menu num=0;
	LCD_Clear();
	LCD_WriteString("select the room ");
	_delay_ms(200);
	LCD_Clear();
	LCD_WriteString("1:Room1 2:Room2");
	LCD_GoTo(1,0);
	LCD_WriteString("3:Room3 4:More ");
	while(num<1||num>4)
	{
		k=KEYPAD_GetKey();
		num=k-'0';
	}
	if(num==MORE_MENU)
	{
		LCD_Clear();
		LCD_WriteString("5:Room4 6:RGB");
		LCD_GoTo(1,0);
		LCD_WriteString("7:air_c 8:all");
		k=0,num=0;
		while(num<5||num>8)
		{
			k=KEYPAD_GetKey();
			num=k-'0';
		}
		
	}
	return num;
	
}
void MenuOption(en_menu SelectedRoom)
{
	u8 k=0,num=0;
	STD_message StatusCode  = All_menu;//demand status code
	STD_message TurnOnCode  = 0;//turn on the room or the device code
	STD_message TurnOffCode = 0;//turn off the device or room
	STD_message speed,color;
	STD_message response    = DEFAULT_ACK;//the response of the slave that is sent back based on the command of the master
		LCD_Clear();//remove all previously printed characters on the LCD and move the cursor to the first column of the first row
		
		/*********** ****************Set the commands to be sent to the slave based on  the sent room or device ******************************/
		switch(SelectedRoom)
		{
			case ROOM1_MENU:
			StatusCode = ROOM1_STATUS;
			TurnOnCode = ROOM1_TURN_ON;
			TurnOffCode = ROOM1_TURN_OFF;
			LCD_WriteString("Room1 S:");
			break;
			case ROOM2_MENU:
			StatusCode = ROOM2_STATUS;
			TurnOnCode = ROOM2_TURN_ON;
			TurnOffCode = ROOM2_TURN_OFF;
			LCD_WriteString("Room2 S:");
			break;
			case ROOM3_MENU:
			StatusCode = ROOM3_STATUS;
			TurnOnCode = ROOM3_TURN_ON;
			TurnOffCode = ROOM3_TURN_OFF;
			LCD_WriteString("Room3 S:");
			break;
			case ROOM4_MENU:
			StatusCode = ROOM4_STATUS;
			TurnOnCode = ROOM4_TURN_ON;
			TurnOffCode = ROOM4_TURN_OFF;
			LCD_WriteString("Room4 S:");
			break;
			case RGB_MENU:
			StatusCode = RGB_STATUS;
			TurnOffCode = Rgb_off;
			LCD_WriteString("rgb S:");
			break;
			case AIRCONDITIONING_MENU:
			StatusCode = AIR_COND_STATUS;
			TurnOnCode = AIR_COND_TURN_ON;
			TurnOffCode = AIR_COND_TURN_OFF;
			LCD_WriteString("Air Cond. S:");
			break;
			case All_menu:
			TurnOnCode = all_turn_on;
			TurnOffCode = all_turn_off;
			LCD_WriteString("control all");
			break;
		}
		if(StatusCode==All_menu)
		{
			
		}
		else
		{
		SPI_SendReceive(StatusCode);//demand the status from the slave
		_delay_ms(100);//Halt the system for the given time in (ms)
		response = SPI_SendReceive(DEMAND_RESPONSE);//the master micro controller asks for the status
		if(response == ON_STATUS)//if the response from the slave was on status
		{
			LCD_WriteString("ON");//print the status on
		}
		else//if the response from the slave was off status
		{
			LCD_WriteString("OFF");//print the status off
		}
		}
		LCD_GoTo(1,0);//move the cursor to the start of the second line
		LCD_WriteString("1-On2-Off3-RET");//print the sub menu
		while(num<1||num>3)
		{
			k=KEYPAD_GetKey();
			num=k-'0';
		}
		if (num==1)
		{
			if(StatusCode==AIR_COND_STATUS)
			{
				num=0;
				k=0;
				_delay_ms(100);
				LCD_Clear();
				LCD_WriteString("enter the speed ");
				_delay_ms(200);
				LCD_Clear();
				LCD_WriteString("1:speed1-2:speed2");
				LCD_GoTo(1,0);
				LCD_WriteString("3:speed3-4:speed4");
				while(num<1||num>4)
				{
					k=KEYPAD_GetKey();
					num=k-'0';
				}
				speed=cond_speed1+num-1;
				SPI_SendReceive(TurnOnCode);
				_delay_ms(100);//Halt the system for the given time in (ms)
				SPI_SendReceive(speed);
				LCD_Clear();
				LCD_WriteString("done");
			}
			else if(StatusCode==RGB_STATUS)
			{
				num=0;
				k=0;
				_delay_ms(100);
				LCD_Clear();
				LCD_WriteString("enter the color ");
				_delay_ms(200);
				LCD_Clear();
				LCD_WriteString("1:red-2:orange");
				LCD_GoTo(1,0);
				LCD_WriteString("3:yellow-4:more");
				while(num<1||num>4)
				{
					k=KEYPAD_GetKey();
					num=k-'0';
				}
				color=rgb_on_red+num-1;
				if(num==MORE_MENU)
				{
					LCD_Clear();
					LCD_WriteString("5:green 6:blue");
					LCD_GoTo(1,0);
					LCD_WriteString("7:white 8:pink");
					k=0,num=0;
					while(num<5||num>8)
					{
						k=KEYPAD_GetKey();
						num=k-'0';
					}
					color=rgb_on_red+num-2;
					
				}
				SPI_SendReceive(color);
				LCD_Clear();
				LCD_WriteString("done");
			}
			else
			{
				SPI_SendReceive(TurnOnCode);//Send turn on signal from master to slave
				_delay_ms(100);//Halt the system for the given time in (ms)
				_delay_ms(100);
				LCD_Clear();
			}
			
		}
		else if (num==2)
		{
			SPI_SendReceive(TurnOffCode);//Send turn off signal from master to slave
			LCD_Clear();
			LCD_WriteString("done");
			_delay_ms(100);
		}
		else if (num==3)
		{
			LCD_Clear();
		}
}
