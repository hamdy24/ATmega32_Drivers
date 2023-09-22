/*
 * main.c
 *
 *  Created on: Oct 30, 2021
 *      Author: Hamdy Aouf
 */
#include "../LIBRARIES/stdTypes.h"
#include "../LIBRARIES/errorstate.h"

#include "../HAL/LCD/LCD_int.h"
#include "../HAL/SWITCH_LINKING/Switch_int.h"

#include "../MCAL/ADC/ADC_interface.h"
#include "../MCAL/TIMER/ICU_HW/ICU_Interface.h"
#include "../MCAL/TIMER/PWM/PWM_interface.h"
#include "../MCAL/TIMER/TIMER0/TIMER0_interface.h"
#include "../MCAL/EXTI/EXTI_int.h"
#include "../MCAL/GIE/GIE_int.h"


#include <util/delay.h>

int main()
{
	DIO_enuSetPinDirection(DIO_u8PORTA,DIO_u8PIN1,DIO_u8INPUT); 
	DIO_enuSetPinDirection(DIO_u8PORTD,DIO_u8PIN7,DIO_u8OUTPUT); 
	
	LCD_enuInit();
	LCD_enuSendString("INIT");

	ADC_enuInit(&ADC_Configs);
	EXTI_enuInit(EXTI_enuAstrEXTI_CONFIG);
	GIE_enuEnable();
	PWM_enuInit(&PWM_strPWM1_Config);
	TIMER0_enuInit(&Timer0_Configs);

	while(1){

	/** Call any interface or parameter by the name of its related module and auto-complete will help you **/
	/** or you can go to the interface and configurations files to know what to use and where **/
		
	}
	return 0;
}
