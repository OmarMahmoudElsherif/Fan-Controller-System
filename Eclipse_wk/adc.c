/******************************************************************************
 *
 * Module: ADC
 *
 * File Name: adc.c
 *
 * Description: Source file for the ATmega16 ADC driver
 *
 *
 *******************************************************************************/

#include "avr/io.h" /* To use the ADC Registers */
#include <avr/interrupt.h> /* For ADC ISR */
#include "adc.h"
#include "common_macros.h" /* To use the macros like SET_BIT */

/*******************************************************************************
 *                          Global Variables                                   *
 *******************************************************************************/
#if TYPE_OF_ADC_DESIGN == 2

volatile uint16 g_adcResult = 0;

/*******************************************************************************
 *                          ISR's Definitions                                  *
 *******************************************************************************/

ISR(ADC_vect)
{
	/* Read ADC Data after conversion complete */
	g_adcResult = ADC;
}

#endif
/*******************************************************************************
 *                          Functions Definitions                              *
 *******************************************************************************/

void ADC_init(const ADC_ConfigType * Config_Ptr)
{
	/* ADMUX Register Bits Description:
	 * REFS1:0 = choose to connect reference voltage
	 * ADLAR   = 0 right adjusted
	 * MUX4:0  = 00000 to choose channel 0 as initialization
	 */
	ADMUX = (ADMUX & 0x3F) | ((Config_Ptr->ref_volt)<<6);

	/* ADCSRA Register Bits Description:
	 * ADEN    = 1 Enable ADC
	 * ADATE   = 0 Disable Auto Trigger
	 * ADPS2:0 = choose ADC_Clock --> ADC must operate in range 50-200Khz
	 */
	ADCSRA = (1<<ADEN);
	ADCSRA = (ADCSRA & 0xF8) | (Config_Ptr->prescaler);


#if TYPE_OF_ADC_DESIGN == 1

	/* ADIE    = 0 Disable ADC Interrupt */
	ADCSRA &= ~(1<<ADIE);


#elif TYPE_OF_ADC_DESIGN == 2

	/* ADIE    = 1 Enable ADC Interrupt */
	ADCSRA |= (1<<ADIE);

#endif

}


#if TYPE_OF_ADC_DESIGN == 1

uint16 ADC_readChannel(uint8 channel_num)
{
	channel_num &= 0x07; /* Input channel number must be from 0 --> 7 */
	ADMUX &= 0xE0; /* Clear first 5 bits in the ADMUX (channel number MUX4:0 bits) before set the required channel */
	ADMUX = ADMUX | channel_num; /* Choose the correct channel by setting the channel number in MUX4:0 bits */
	SET_BIT(ADCSRA,ADSC); /* Start conversion write '1' to ADSC */
	while(BIT_IS_CLEAR(ADCSRA,ADIF)); /* Wait for conversion to complete, ADIF becomes '1' */
	SET_BIT(ADCSRA,ADIF); /* Clear ADIF by write '1' to it :) */
	return ADC; /* Read the digital value from the data register */
}


#elif TYPE_OF_ADC_DESIGN == 2

void ADC_readChannel(uint8 channel_num)
{
	channel_num &= 0x07; /* Input channel number must be from 0 --> 7 */
	ADMUX &= 0xE0; /* Clear first 5 bits in the ADMUX (channel number MUX4:0 bits) before set the required channel */
	ADMUX = ADMUX | channel_num; /* Choose the correct channel by setting the channel number in MUX4:0 bits */
	SET_BIT(ADCSRA,ADSC); /* Start conversion write '1' to ADSC */
}

#endif


