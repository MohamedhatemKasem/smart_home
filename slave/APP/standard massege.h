/*
 * standard_massege.h
 *
 * Created: 8/6/2023 1:05:33 AM
 *  Author: mohamed hatem
 */ 


#ifndef STANDARD MASSEGE_H_
#define STANDARD MASSEGE_H_
typedef enum
{
ROOM1_STATUS  ,
ROOM2_STATUS   ,
ROOM3_STATUS    ,
ROOM4_STATUS    ,
RGB_STATUS 		,
AIR_COND_STATUS ,
ROOM1_TURN_ON    ,
ROOM2_TURN_ON   ,
ROOM3_TURN_ON   ,
ROOM4_TURN_ON   ,
AIR_COND_TURN_ON ,
ROOM1_TURN_OFF ,
ROOM2_TURN_OFF ,
ROOM3_TURN_OFF,
ROOM4_TURN_OFF,
AIR_COND_TURN_OFF,
cond_speed1,
cond_speed2,
cond_speed3,
cond_speed4,
rgb_on_red,
rgb_on_orange,
rgb_on_yellow,
rgb_on_green,
rgb_on_blue,
rgb_on_white,
rgb_on_pink,
Rgb_off,
all_turn_on,
all_turn_off,
DEFAULT_ACK,
DEMAND_RESPONSE,
ON_STATUS,
OFF_STATUS,
}STD_message;

#endif /* STANDARD MASSEGE_H_ */