/*
 * block.h
 *
 * Created: 8/5/2023 5:58:35 PM
 *  Author: mohamed hatem
 */ 

#ifndef PASSWORD_H_
#define PASSWORD_H_
#define PASS_SIZE       10
#define TRIES_ALLOWED    3
#define PASSWORD_SYMBOL  '*'
#define PASS_NOT_SET    0xFF
#define PASS_SET        0x01

#define ADMIN_PASS_STATUS_ADDRESS 0X02
#define ADMIN_PASS_block_ADDRESS 0X03
#define block_counter_ADDRESS 0X04
#define EEPROM_ADMIN_ADDRESS        0X10

#define  Number_of_trial 3
#define  pan_length 5
extern pass[PASS_SIZE];
u8 check_arr[PASS_SIZE];
u8 Pass_len(u8*x);
u8 Pass_compare (u16*x,u16*y);
u8 Pan_compare (u8*x,u8*y,u8 size);
void block_fun(void);
void set_pass_first_time(void);
void write_pass(void);
void pass_change(void);



#endif /* PASSWORD_H_ */