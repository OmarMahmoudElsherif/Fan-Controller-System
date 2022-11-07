/******************************************************************************
 *
 * Module: ADC
 *
 * File Name: adc.h
 *
 * Description: header file for the ATmega16 ADC driver
 *
 *******************************************************************************/

#ifndef ADC_H_
#define ADC_H_

#include "std_types.h"


/*******************************************************************************
 *                         Type of Design:									   *
 *                         1.  Polling										   *
 *                         2.  Interrupt									   *
 *******************************************************************************/
#define TYPE_OF_ADC_DESIGN 	1

#if((TYPE_OF_ADC_DESIGN != 1) && (TYPE_OF_ADC_DESIGN != 2))

#error "The design type should be either Polling or Interrupt"

#endif



/*******************************************************************************
 *                       ADC Configurations                                    *
 *******************************************************************************/
typedef enum{
	AREF,AVCC,Reserved,Internal_2_56V
}ADC_ReferenceVolatge;

typedef enum{
	Prescaler_2 = 1,Prescaler_4,Prescaler_8,Prescaler_16,Prescaler_32,Prescaler_64,Prescaler_128
}ADC_Prescaler;

typedef struct{
 ADC_ReferenceVolatge ref_volt;
 ADC_Prescaler prescaler;
}ADC_ConfigType;



/*******************************************************************************
 *                                Definitions                                  *
 *******************************************************************************/
#define ADC_MAXIMUM_VALUE    1023
#define ADC_REF_VOLT_VALUE   2.56

/*******************************************************************************
 *                       External Variables                                    *
 *******************************************************************************/
#if TYPE_OF_ADC_DESIGN == 2

/* Extern Public global variables to be used by other modules */
extern volatile uint16 g_adcResult;

#endif
/*******************************************************************************
 *                      Functions Prototypes                                   *
 *******************************************************************************/

/*
 * Description :
 * Function responsible for initialize the ADC driver.
 */
void ADC_init(const ADC_ConfigType * Config_Ptr);

/*
 * Description :
 * Function responsible for read analog data from a certain ADC channel
 * and convert it to digital using the ADC driver.
 */
#if TYPE_OF_ADC_DESIGN == 1  /*polling*/

uint16 ADC_readChannel(uint8 channel_num);


#elif  TYPE_OF_ADC_DESIGN == 2

void ADC_readChannel(uint8 channel_num);

#endif

#endif /* ADC_H_ */
