/*
 * ADC.c
 *
 * Created: 7/3/2023 5:07:56 PM
 *  Author: mohamed hatem
 */ 
#include "stdtypes.h"
#include "MemMap.h"
#include "utils.h"
#include "ADC_INTERFAC.h"
#include "adc_cfg.h"
static  ADC_busy_flag;
static void(*fpt)(void)=NULL_PTR;
void ADC_Init(ADC_VoltRef_type vref,ADC_Prescaler_type scaler)
{
	switch(vref)
	{
		case VREF_AREF:
		clear_bit(ADMUX,REFS0);
		clear_bit(ADMUX,REFS1);
		break;
		case VREF_AVCC:
		set_bit(ADMUX,REFS0);
		clear_bit(ADMUX,REFS1);
		break;
		case VREF_256V:
		set_bit(ADMUX,REFS1);
		clear_bit(ADMUX,REFS0);
		break;
		
	}
	set_bit(ADCSRA,ADEN);
	ADCSRA=ADCSRA&0xf8;
	scaler=scaler&0x07;
	ADCSRA=ADCSRA|scaler;
}
u16 ADC_Read(ADC_Channel_type CH,ADLAR_C AL)
{
	ADMUX&=0XE0;
	ADMUX=ADMUX|CH;
	if(AL==ADLAR1)
	{
		set_bit(ADMUX,ADLAR);
	}
	else
	{
		clear_bit(ADMUX,ADLAR);
	}
	set_bit(ADCSRA,ADSC);
	while(read_bit(ADCSRA,ADSC));
	u16 data =ADCL;
	if(AL==ADLAR0)
	{
		data=data|((u16)ADCH<<8);
	}
	else
	{
			return ADC>>6;	
	}
	
	//return ADC;	
	return data;

}
u16 ADC_VoltRead(ADC_Channel_type CH)
{
	u16 adc_data=ADC_Read(CH,ADLAR0),volt;
	volt=(adc_data*(u32)Volt_ref)/ADC_RESULTION;
	return volt;
}