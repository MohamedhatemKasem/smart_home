/*
 * Sensors.c
 *
 * Created: 7/4/2023 4:23:55 AM
 *  Author: mohamed hatem
 */ 
#include "stdtypes.h"
#include "ADC_INTERFAC.h"
#include "MemMap.h"
#include "sensors_interfaces.h"
#include "adc_cfg.h"
s16 TEMP_Read(ADC_Channel_type s)
{
	s16 temp;
	temp=ADC_VoltRead(s);
	temp=(temp+5)/10;
	return temp;
}