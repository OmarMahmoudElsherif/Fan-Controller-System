/*
 * Fan_Controller_system.c
 *
 *  Created on: 4 Oct 2022
 *
 *   FaceBook: Omar Elsherif
 */

#include"util/delay.h"
#include"adc.h"
#include"lcd.h"
#include"lm35_sensor.h"
#include"PWM_Timer0.h"
#include"dc_motor.h"
#include "std_types.h"




int main(void)
{
	uint8 Temp_value;
	ADC_ConfigType config= {Internal_2_56V,Prescaler_8};

	ADC_init(&config);
	LCD_init();
	DcMotor_Init();

	LCD_displayStringRowColumn(1, 2, "Temp =    C");
	_delay_ms(50);


	while(1)
	{
		Temp_value = LM35_getTemperature();

		LCD_moveCursor(1, 9);
		if(Temp_value>=100)
		{
			LCD_intgerToString(Temp_value);
		}
		else
		{
			LCD_intgerToString(Temp_value);
			LCD_displayCharacter(' ');
		}


		LCD_moveCursor(0, 2);
		if(Temp_value>=120)
		{
			/* Turn On fan with 100% speed*/
			LCD_displayString("FAN is ON ");
			DcMotor_Rotate(Clockwise,100);
		}
		else if (Temp_value>=90)
		{
			/* Turn On fan with 75% speed*/
			LCD_displayString("FAN is ON ");
			DcMotor_Rotate(Clockwise,75);
		}
		else if (Temp_value>=60)
		{
			/* Turn On fan with 50% speed*/
			LCD_displayString("FAN is ON ");
			DcMotor_Rotate(Clockwise,50);
		}
		else if ( Temp_value >=30)
		{
			/* Turn On fan with 25% speed*/
			LCD_displayString("FAN is ON ");
			DcMotor_Rotate(Clockwise,25);
		}
		else
		{
			/*  Turn Off Fan , Temperature < 30*/
			LCD_displayString("FAN is OFF ");
			DcMotor_Rotate(Stop,0);
		}




	}
	return 0;
}
