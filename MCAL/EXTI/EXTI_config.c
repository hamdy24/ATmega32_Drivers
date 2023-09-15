/*
 * EXTI_config.c
 *
 *  Created on: Oct 30, 2021
 *      Author: hamdy
 */
#include "../../LIBRARIES/errorstate.h"
#include "../../LIBRARIES/stdTypes.h"

#include "EXTI_config.h"

/******* Interrupts Configuration *************/

EXTI_T EXTI_enuAstrEXTI_CONFIG[INTERRUPT_NUM] =
{
	{.Interrupt_State = ENABELED  ,  .INT_Sense_Level = RISING},	//INT0
	{.Interrupt_State = DISABELED ,  .INT_Sense_Level = DISABELED},	//INT1
	{.Interrupt_State = DISABELED ,  .INT_Sense_Level = DISABELED}	//INT2
};
