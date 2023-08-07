/*
 * sensors_interfaces.h
 *
 * Created: 7/4/2023 4:24:16 AM
 *  Author: mohamed hatem
 */ 


#ifndef SENSORS_INTERFACES_H_
#define SENSORS_INTERFACES_H_
#include "ADC_INTERFAC.h"
#define  s1 CH_0
#define  s2 CH_1
#define  s3 CH_2
#define  s4 CH_3
s16 TEMP_Read(ADC_Channel_type s);
#endif /* SENSORS_INTERFACES_H_ */