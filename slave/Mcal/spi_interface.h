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
u8 SPI_ReceivePerodic(u8*pdata);
void SPI_SendNoBlock(u8 data);
void SPI_set_callback(void(*p)(void));
void SPI_receive_no_block(u8 *data);
void SPI_interrupt_enable(void);
void SPI_interrupt_disable(void);
#endif /* SPI_INTERFACE_H_ */