/*
 * SPI.c
 *
 * Created: 7/16/2023 11:06:52 PM
 *  Author: mohamed hatem
 */ 

#include "stdtypes.h"
#include "MemMap.h"
#include "spi_interface.h"
#include "utils.h"
static void (*SPI_Fptr) (void)=NULLPTR;

void SPI_Init(SPIMode_type mode)
{
	if (mode==MASTER)
	{
		//clock 2MHZ
		SET_BIT(SPCR,MSTR);
		
	}
	else
	{
		
		CLR_BIT(SPCR,MSTR);
	}
	
	// SPI ENABLE
	SET_BIT(SPCR,SPE);
	
}


u8 SPI_SendReceive(u8 data)
{
	SPDR=data;
	while(READ_BIT(SPSR,SPIF)==0);
	return SPDR;
}


u8 SPI_ReceivePerodic(u8*pdata)
{
	if (READ_BIT(SPSR,SPIF))
	{
		*pdata=SPDR;
		return 1;
	}
	return 0;
}

void SPI_SendNoBlock(u8 data)
{
	SPDR=data;
}
void SPI_receive_no_block(u8 *data)
{
	*data=SPDR;
}
void SPI_interrupt_enable(void)
{
	set_bit(SPCR,SPIE);
}
void SPI_interrupt_disable(void)
{
	clear_bit(SPCR,SPIE);
}
void SPI_set_callback(void(*p)(void))
{
	SPI_Fptr=p;
}
ISR(SPI_STC_vect)
{
	if(SPI_Fptr!=NULL_PTR)
	{
		SPI_Fptr();
	}
}
