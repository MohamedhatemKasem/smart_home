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
