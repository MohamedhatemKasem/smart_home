/*
 * RGB.c
 *
 * Created: 7/13/2023 2:21:22 AM
 *  Author: mohamed hatem
 */ 
#include "stdtypes.h"
#include "utils.h"
#include "MemMap.h"
#include "Timer.h"
#include "RGB.h"
 u8 rgb_arr[8][3]={{255,0,0},//red
	            {255,165,0},//orange
		        {255,255,0},//yellow
		        {0,255,0}, //green
				{0, 0,255},//blue
				{255,255,255},//WHITE
				{158, 4, 79}, //PINK
				{0,0,0}}; //black
void select_color3(u8 x)
{
	ICR1=255;
	if(x<8)
	{
		while(OCR1A!=rgb_arr[x][0]||OCR1B!=rgb_arr[x][1]||OCR2!=rgb_arr[x][2])
		{
			
		if(OCR1A<rgb_arr[x][0])
		{
			OCR1A++;
		}
		if(OCR1B<rgb_arr[x][1])
		{
			OCR1B++;
		}
		if(OCR2<rgb_arr[x][2])
		{
			OCR2++;
		}
		if(OCR1A>rgb_arr[x][0])
		{
			OCR1A--;
		}
		if(OCR1B>rgb_arr[x][1])
		{
			OCR1B--;
		}
		if(OCR2>rgb_arr[x][2])
		{
			OCR2--;
		}
		/*LCD_Clear();
		LCD_WriteNumber(OCR1A);
		LCD_GoTo(0,5);
		LCD_WriteNumber(OCR1B);
		LCD_GoTo(1,0);
		LCD_WriteNumber(OCR0);
		LCD_GoTo(1,5);
		LCD_WriteNumber(x);
		*/
		_delay_ms(5);
	}
	}
	
	
}