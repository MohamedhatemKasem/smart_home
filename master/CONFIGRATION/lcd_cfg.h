/*
 * lcd_cfg.h
 *
 * Created: 6/30/2023 1:17:19 AM
 *  Author: mohamed hatem
 */ 


#ifndef LCD_CFG_H_
#define LCD_CFG_H_
#define  _8_BIT  0
#define  _4_BIT  1

/***********_8_BIT or _4_BIT *********************/
#define  LCD_MODE  _4_BIT

#define  RS    PINB1
#define  EN    PINB0
#define D4  PINA4
#define D5  PINA5
#define D6  PINA6
#define D7  PINA7
#define  LCD_PORT  PA


#endif /* LCD_CFG_H_ */