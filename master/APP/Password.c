/*
 * block.c
 *
 * Created: 8/5/2023 5:58:20 PM
 *  Author: mohamed hatem
 */ 
#include "keypad_interface.h"
#include "lcd_interface.h"
#include "MemMap.h"
#include "utils.h"
#include "NVM.h"
#include "main_CFG.h"
#include "stdtypes.h"
const u8 pan[pan_length]={4,5,6,7,8};
u8 pass[PASS_SIZE]={0};
u8 check_arr[PASS_SIZE]={0};
u8 Pass_len(u8*x)
	{
		u16 i;
		for(i=0;x[i]!=0;i++)
		{

		}
		return i;
	}
	
u8 Pass_compare (u8*x,u8*y)
	{
		u16 i,j;
		i=Pass_len(x);
		LCD_WriteNumber(i);
		j=Pass_len(y);
		LCD_WriteNumber(j);
		if(i!=j)
		{
			return 0;
		}
		for(i=0;x[i]!=0&&y[i]!=0;i++)
		{
			if(x[i]!=y[i])
			{
				return 0;
			}

		}
		return 1;

	}
u8 Pan_compare (u8*x,u8*y,u8 size)
	{
		u8 i;;
		for(i=0;i<size;i++)
		{
			if(x[i]!=y[i])
			{
				return 0;
			}

		}
		return 1;

}
void block_fun(void)
{
	LCD_Clear();
	u8 k=0,check=0,i=0;
	u8 pan_arr[pan_length]={0};
		while(check==0)
		{
			i=0;
			k=0;
			LCD_WriteString("System blecked");
			_delay_ms(500);
			LCD_Clear();
			LCD_WriteString("insert the pan ");
			LCD_GoTo(1,0);
			while(k!='=')
			{
				k=KEYPAD_GetKey();
				if (k!='T')
				{
					if(k>='0'&&k<='9')
					{
						pan_arr[i]=k-'0';
						i++;
						LCD_WriteChar(PASSWORD_SYMBOL);
					}
					if(k=='=')
					{
						LCD_Clear();
						check=Pan_compare(pan,pan_arr,pan_length);
						if(check==1)
						{
							LCD_WriteString("Right pan");
							LCD_GoTo(1,0);
							LCD_WriteString("system reset");
							_delay_ms(200);
							LCD_Clear();
							NVM_write_bit(block_counter_ADDRESS,0);
						}
						else
						{
							LCD_WriteString("wrong pan");
							_delay_ms(200);
							LCD_Clear();
						}
						
					}
				}
			}
	}
	
	}
void set_pass_first_time(void)
{
	u8 i=0,k=0;
	NVM_write_bit(block_counter_ADDRESS,0);
	LCD_WriteString("Set Admin pass");//printing the set admin password menu
	LCD_WriteString("Admin pass:");
	_delay_ms(300);
	LCD_Clear();
	LCD_GoTo(0,0);
	LCD_WriteString("max pass is9 num");
	LCD_GoTo(1,0);
	/********************************* setting Admin password **********************************************/
	//the array where it stored the password
	while(k!='=')
	{
		k=KEYPAD_GetKey();
		if (k!='T')
		{
			if(k>='0'&&k<='9')
			{
				pass[i]=k;
				i++;
				LCD_WriteChar(PASSWORD_SYMBOL);
			}
			if(k=='=')
			{
				pass[i]=0;
				NVM_write_block(EEPROM_ADMIN_ADDRESS,pass,PASS_SIZE);
				LCD_WriteString("Pass Saved");
				NVM_write_bit(ADMIN_PASS_STATUS_ADDRESS,PASS_SET);//write the status of pass as it is set
				_delay_ms(500);//Halt the system for the given time in (ms)
				LCD_Clear();//remove all previously printed characters on the LCD and move the cursor to the first column of the first row

			}
		}
	}
}
void write_pass(void)
{
	u8 i=0,k=0;
	LCD_WriteString("insert pass");
	LCD_GoTo(1,0);
	while(k!='=')
	{
		k=KEYPAD_GetKey();
		if (k!='T')
		{
			if(k>='0'&&k<='9')
			{
				pass[i]=k;
				i++;
				LCD_WriteChar(PASSWORD_SYMBOL);
			}
			if(k=='=')
			{
				LCD_Clear();
				pass[i]=0;
				nvm_read_block(EEPROM_ADMIN_ADDRESS,PASS_SIZE,check_arr);
			}
		}
	}
}
void pass_change(void)
{
	u8 i=0,k=0;
	LCD_WriteString("1 change pass");
	LCD_GoTo(1,0);
	LCD_WriteString("2 continue");
	while(k<'1'||k>'2')
	{
		k=KEYPAD_GetKey();
	}
	LCD_Clear();
	if(k=='1')
	{
		write_pass();
		if(Pass_compare(check_arr,pass))
		{
			set_pass_first_time();
		}
		else
		{
			LCD_WriteString("failed to change");
			_delay_ms(100);
		}
	}

}