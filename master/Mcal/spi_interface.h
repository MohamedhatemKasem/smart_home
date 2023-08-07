/*
 * spi_interface.h
 *
 * Created: 7/16/2023 11:07:17 PM
 *  Author: mohamed hatem
 */ 


#ifndef SPI_INTERFACE_H_
#define SPI_INTERFACE_H_
typedef enum{
	MASTER,
	SLAVE
	
}SPIMode_type;
void SPI_Init(SPIMode_type mode);

u8 SPI_SendReceive(u8 data);
#endif /* SPI_INTERFACE_H_ */